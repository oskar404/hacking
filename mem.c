#include <stdio.h>
#include <stdlib.h>
#define __USE_GNU   /* for program_invocation_short_name (non standard glibc) */
#include <errno.h>
#define __USE_XOPEN_EXTENDED /* sbrk(), _BSD_SOURCE|_SVID_SOURCE do not work */
#include <unistd.h>
#include <getopt.h>


typedef void (*TestFunction)();
const size_t MAX_MALLOCS = 32768;
size_t block_size = 4096;
unsigned int iterations = 10;

// Declare uninitialized data segment end (glibc sets, get address with &end)
extern char end;


void usage()
{
    printf("usage: %s [-m|-d|-u] [-b size]\n\n", program_invocation_short_name);
    printf("  Run various memory function tests (malloc(), free() ..)\n\n");
    printf("  -m       malloc_test()\n");
    printf("  -M       multiple_mallocs_test()\n");
    printf("  -d       double_free_test()\n");
    printf("  -u       use_after_free_test()\n");
    printf("\nControls for tests:");
    printf("  -b size  Block size for malloc() (default: %zu)\n", block_size);
    printf("  -s size  Num of mallocs/iterations (default: %u)\n", iterations);
    printf("\n");
    exit(EXIT_FAILURE);
}


void check_ptr(void* ptr)
{
    if (ptr == 0)
    {
        printf("malloc(%zu) failed\n", block_size);
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("malloc(%zu): %p\n", block_size, ptr);
    }
}


void malloc_test()
{
    printf("malloc_test()\n");
    printf("sizeof(size_t): %lu\n", sizeof(size_t));
    printf("block_size: %zu\n", block_size);
    printf("&end:     %p\n", &end);
    printf("sbrk(0):  %p\n", sbrk(0L));
    void* ptr = malloc(block_size);
    check_ptr(ptr);
    printf("sbrk(0):  %p\n", sbrk(0L));
    free(ptr);
}


void multiple_mallocs_test()
{
    static void* buffer[MAX_MALLOCS];

    void* sbrk_start = sbrk(0L);
    printf("multiple_mallocs_test()\n");
    printf("block_size: %zu\n", block_size);
    printf("iterations: %u\n", iterations);
    for (unsigned int i = 0; i < iterations; ++i)
    {
        void* ptr = malloc(block_size);
        check_ptr(ptr);
        buffer[i] = ptr;
    }
    printf("sbrk(0):  %p [function start]\n", sbrk_start);
    printf("sbrk(0):  %p [after %u * malloc()]\n", sbrk(0L), iterations);
    for (unsigned int i = 0; i < iterations; ++i)
    {
        free(buffer[i]);
    }
    printf("sbrk(0):  %p [after %u * free()]\n", sbrk(0L), iterations);
}


void double_free_test()
{
    printf("double_free_test()\n");
    void* ptr = malloc(block_size);
    check_ptr(ptr);
    free(NULL);
    free(ptr);
    free(ptr);  /* Crash! */
}


void use_after_free_test()
{
    printf("use_after_free_test()\n");
    char* ptr = (char*)malloc(block_size);
    check_ptr(ptr);
    ptr[0] = 'a';
    printf("ptr[0]: %c\n", ptr[0]);
    free(ptr);
    /* These work with standard c-library implementation.
       Debugging needs Valgrind or some malloc debugging library. */
    printf("after free(ptr)\nread ptr[0]: ");
    char c = ptr[0];
    printf("%c\n", c);
    printf("write ptr[0]: ");
    ptr[0] = 'X';
    printf("%c\n", ptr[0]);
}


int main(int argc, char* argv[])
{
    TestFunction test_ptr = &malloc_test;
    int opt;

    while ((opt = getopt(argc, argv, "hmMdub:s:")) != -1) {
        switch (opt) {
        case 'm':
            test_ptr = &malloc_test;
            break;
        case 'M':
            test_ptr = &multiple_mallocs_test;
            break;
        case 'd':
            test_ptr = &double_free_test;
            break;
        case 'u':
            test_ptr = &use_after_free_test;
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
        case 's':
            {
            long l = strtol(optarg, NULL, 10);
            if (errno == ERANGE || l <= 0 || l > MAX_MALLOCS) {
                printf("invalid iterations size: %s\n\n", optarg);
                usage();
            }
            iterations = (int)l;
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

    /* Run the test */
    (*test_ptr)();

    return 0;
}
