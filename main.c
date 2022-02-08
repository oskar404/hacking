#include <stdio.h>

// Explicitly declare environment pointer
extern char **environ;

// Dump process environment
void dump(char* argv[])
{
    for (int i = 0; argv[i] != NULL; i++)
        puts(argv[i]);
}

#if defined(SIG2)
int main(int argc, char* argv[], char **envp)
{
    printf("====================\n");
    printf("argc: %d\n", argc);
    printf("argv: %p\n", argv);
    printf("envp: %p\n", envp);
    printf("environ: %p\n", environ);
    printf("====================\n");
    dump(argv);
    printf("====================\n");
    dump(envp);
    printf("====================\n");
    return 0;
}
#elif defined(SIG1)
int main(int argc, char* argv[])
{
    printf("====================\n");
    printf("argc: %d\n", argc);
    printf("argv: %p\n", argv);
    printf("environ: %p\n", environ);
    printf("====================\n");
    dump(argv);
    printf("====================\n");
    return 0;
}
#else
int main(void)
{
    printf("====================\n");
    printf("environ: %p\n", environ);
    printf("====================\n");
    dump(environ);
    printf("====================\n");
    return 0;
}
#endif