#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
// Define __USE_GNU before errno inclusion for program_invocation_name and
// program_invocation_short_name visibility
// (The Linux Programming Interface talks about _GNU_SOURCE)
#define __USE_GNU
#include <errno.h>

// Explicitly declare memory layout variables
// text segment end
extern char etext;
// initialized data segment end
extern char edata;
// uninitialized data segment end
extern char end;

// Explicitly declare environment pointer
extern char **environ;

// These are stored to intialized text segment
const unsigned int LABEL = 0xDEADBEEF;
const unsigned int LEBAL = 0xEFBEADDE;


// Dump some memory into output as hex encoded bytes
void hexdump(const char* label, const char* segstart, const char* segend)
{
    printf("%s:\n",label);
    for (char* it = (char *)segstart; it < segend; ++it)
    {
        unsigned char c = (unsigned char)*it;
        printf("%02x", (int)c);
        int bytenum = ((int)it - (int)segstart) + 1;
        if ( bytenum > 0 && bytenum % (8*4) == 0 )
            printf("\n");
        else if ( bytenum > 0 && bytenum % 4 == 0 )
            printf(" ");
    }
    printf("\n");
}


// Dump process environment
void envdump(int argc, char* argv[])
{
    if (argc == 1)
    {
        for (char **ep = environ; *ep != NULL; ep++)
            puts(*ep);
    }
    else
    {
        for (int i = 1; i < argc; ++i)
            printf("%s=%s\n", argv[i], getenv(argv[i]));
    }

}


int main(int argc, char* argv[])
{
    // Based on program name do different things
    if (strcmp(program_invocation_short_name, "piddata") == 0)
        hexdump("Initialized data", &etext, &edata);
    else if (strcmp(program_invocation_short_name, "pidenv") == 0)
        envdump(argc, argv);
    else
    {
        printf("%s\n", program_invocation_short_name);
        printf("pid: %d\n",getpid());
        printf("parent pid: %d\n",getppid());
        printf("etext: %#010x\n", (int)&etext);
        printf("edata: %#010x\n", (int)&edata);
        printf("end: %#010x\n", (int)&end);
    }

    return 0;
}
