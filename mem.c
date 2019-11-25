#include <stdio.h>
#include <stdlib.h>
#define __USE_GNU   /* for program_invocation_short_name (non standard glibc) */
#include <errno.h>
#define __USE_XOPEN_EXTENDED /* sbrk(), _BSD_SOURCE|_SVID_SOURCE do not work */
#include <unistd.h>
#include <getopt.h>


typedef void (*TestFunction)();
size_t block_size = 4096;
// Declare uninitialized data segment end (glibc sets, get address with &end)
extern char end;


void usage()
{
    printf("usage: %s [-m|-d] [-b size]\n\n", program_invocation_short_name);
    printf("  Run various memory function tests (malloc(), free() ..)\n\n");
    printf("  -m       malloc_test()\n");
    printf("  -d       double_free_test()\n");
    printf("  -b size  Block size used when allocating memory (default: %zu)\n",
           block_size);
    exit(EXIT_FAILURE);
}


void check_ptr(void* ptr)
{
    if (ptr == 0)
    {
        printf("malloc(%zu) failed\n", block_size);
        exit(EXIT_FAILURE);
    }
}


void malloc_test()
{
    printf("malloc_test()\n");
    printf("block size: %zu\n", block_size);
    printf("&end:     %p\n", &end);
    printf("sbrk(0):  %p\n", sbrk(0L));
    void* ptr = malloc(block_size);
    check_ptr(ptr);
    printf("malloc(): %p\n", ptr);
    printf("sbrk(0):  %p\n", sbrk(0L));
    free(ptr);
}


void double_free_test()
{
    printf("double_free_test()\n");
    void* ptr = malloc(block_size);
    check_ptr(ptr);
    printf("malloc(): %p\n", ptr);
    free(NULL);
    free(ptr);
    free(ptr);  /* Crash! */
}


int main(int argc, char* argv[])
{
    TestFunction test_ptr = NULL;
    int opt;

    while ((opt = getopt(argc, argv, "hmdb:")) != -1) {
        switch (opt) {
        case 'm':
            test_ptr = &malloc_test;
            break;
        case 'd':
            test_ptr = &double_free_test;
            break;
        case 'b':
            {
            long l = strtol(optarg, NULL, 10);
            if (errno == ERANGE || l <= 0) {
                printf("invalid block size: %s\n\n", optarg);
                usage();
            }
            block_size = (size_t)l;
            }
            break;
        case 'h':
            printf("help\n");
            usage();
            break;
        default: /* '?' */
            usage();
        }
    }

    if (optind < argc)
        usage();

    if (test_ptr)
        (*test_ptr)();
    else
        malloc_test();

    return 0;
}
