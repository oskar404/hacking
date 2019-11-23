#include <stdio.h>
#include <setjmp.h>


static jmp_buf jmpenv;


void jumpjump(int label)
{
    goto printer;
    jumper: longjmp(jmpenv, label);
    printer: printf("jumpjump(%d)\n", label);
    goto jumper;
}


int main()
{
    int counter = 0;
    goto begin;

    end: puts("end this madness");
    return 0;

    begin: puts("begin jumping");
    switch(setjmp(jmpenv))
    {
        case 0:     // Initial jump
            puts("patient zero");
            jumpjump(counter++);
            break;
        case 1:     // First return
            jumpjump(counter++);
            break;
        case 2:
            goto begin;
            break;
        case 3:
            goto end;
    }

    goto end;
}
