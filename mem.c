#include <stdio.h>
#include <stdlib.h>
#define __USE_GNU   /* for program_invocation_short_name (non standard glibc) */
#include <errno.h>
#define __USE_XOPEN_EXTENDED /* sbrk(), _BSD_SOURCE|_SVID_SOURCE do not work */
#include <unistd.h>
#include <string.h>
#include <getopt.h>


typedef void (*TestFunction)();
const size_t MAX_MALLOCS = 32768;
size_t block_size = 4096;
unsigned int iterations = 10;

// Declare uninitialized data segment end (glibc sets, get address with &end)
extern char end;


void usage()
{
    printf("usage: %s [-m|-M|-S|-d|-u|-i] [-b size] [-s size]\n\n",
            program_invocation_short_name);
    printf("  Run various memory function tests (malloc(), free() ..)\n\n");
    printf("  -m       malloc_test()\n");
    printf("  -M       multiple_mallocs_test()\n");
    printf("  -S       stack_test()\n");
    printf("  -d       double_free_test()\n");
    printf("  -u       use_after_free_test()\n");
    printf("  -i       inspect_malloc_underpinnings()\n");
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


void stack_recurse(int i)
{
    int number=i;
    if (i > iterations)
        return;
    printf("recurse(%d): &int -> %p\n", i, &number);
    stack_recurse(i+1);
}


void stack_test()
{
    printf("stack_test()\n");
    stack_recurse(1);
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


void hexdump(const char* label, const unsigned char* bytes, const int len)
{
    printf("%s: 0x", label);
    for (int i = 0; i < len; ++i)
    {
        printf("%02x", (int)bytes[0]);
    }
    printf(" ");
}


void* create_ptr()
{
    void* ptr = malloc(block_size);
    check_ptr(ptr);
    memset(ptr, 0xFF, block_size);
    return ptr;
}


void inspect_ptr(const char* label, void* ptr)
{
    printf("%s -> ", label);
    hexdump("before", ptr-sizeof(size_t), (int)sizeof(size_t));
    hexdump("ptr", ptr, (int)sizeof(size_t));
    hexdump("after", ptr+block_size, (int)sizeof(size_t));
    printf("\n");
}

void inspect_malloc_underpinnings()
{
    printf("inspect_malloc_underpinnings()\n");
    /* malloc()/free() store some meta data when reserving bytes.
       There is no standard implementation of malloc()/free() structure.
       Just peek around reserved memory and see what can be found.
    */
    printf("&end:     %p\n", &end);
    printf("sbrk(0):  %p\n", sbrk(0L));
    printf("sizeof(size_t): %lu\n", sizeof(size_t));
    printf("block_size: %zu\n", block_size);
    void* ptr1 = create_ptr();
    void* ptr2 = create_ptr();
    void* ptr3 = create_ptr();
    void* ptr4 = create_ptr();
    printf("extra?: (ptr2-ptr1)-block_size=%lu\n", (ptr2-ptr1)-block_size);
    printf("extra?: (ptr3-ptr2)-block_size=%lu\n", (ptr3-ptr2)-block_size);
    printf("extra?: (ptr4-ptr3)-block_size=%lu\n", (ptr4-ptr3)-block_size);
    inspect_ptr("ptr1", ptr1);
    inspect_ptr("ptr2", ptr2);
    inspect_ptr("ptr3", ptr3);
    inspect_ptr("ptr4", ptr4);
    printf("free(ptr1);\n");
    free(ptr1);
    inspect_ptr("ptr1", ptr1);
    inspect_ptr("ptr2", ptr2);
    inspect_ptr("ptr3", ptr3);
    inspect_ptr("ptr4", ptr4);
    printf("free(ptr3);\n");
    free(ptr3);
    inspect_ptr("ptr1", ptr1);
    inspect_ptr("ptr2", ptr2);
    inspect_ptr("ptr3", ptr3);
    inspect_ptr("ptr4", ptr4);
    printf("free(ptr2);\n");
    free(ptr2);
    inspect_ptr("ptr1", ptr1);
    inspect_ptr("ptr2", ptr2);
    inspect_ptr("ptr3", ptr3);
    inspect_ptr("ptr4", ptr4);
    printf("free(ptr4);\n");
    free(ptr4);
    inspect_ptr("ptr1", ptr1);
    inspect_ptr("ptr2", ptr2);
    inspect_ptr("ptr3", ptr3);
    inspect_ptr("ptr4", ptr4);
    /*
       No idea how this system works .. but still malloc()/free() does some
       magic before and after the allocated memory blocks. Valgrind is not happy
       with this poking.

       NB! The poked implementation was glibc 2.30. Different implementation
           different results
    */
}


int main(int argc, char* argv[])
{
    TestFunction test_ptr = &malloc_test;
    int opt;

    while ((opt = getopt(argc, argv, "hmMSduib:s:")) != -1) {
        switch (opt) {
        case 'm':
            test_ptr = &malloc_test;
            break;
        case 'M':
            test_ptr = &multiple_mallocs_test;
            break;
        case 'S':
            test_ptr = &stack_test;
            break;
        case 'd':
            test_ptr = &double_free_test;
            break;
        case 'u':
            test_ptr = &use_after_free_test;
            break;
        case 'i':
            test_ptr = &inspect_malloc_underpinnings;
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
