#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

// Explicitly declare memory layout variables
// text segment end
extern char etext;
// initialized data segment end
extern char edata;
// uninitialized data segment end
extern char end;


int main()
{
    printf("pid: %d\n",getpid());
    printf("parent pid: %d\n",getppid());
    printf("etext: %#010x\n", (int)&etext);
    printf("edata: %#010x\n", (int)&edata);
    printf("end: %#010x\n", (int)&end);
    return 0;
}
