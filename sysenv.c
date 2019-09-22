#include <stdio.h>
#include <unistd.h>
#include <gnu/libc-version.h>

/* Some macro magic to get compile time values printed on comile time */
#define XSTR(x) STR(x)
#define STR(x) #x
#pragma message("Compile time c standard (__STDC__): " XSTR(__STDC__))
#pragma message("Compile time c standard (__STDC_VERSION__): " XSTR(__STDC_VERSION__))
#pragma message("Compile time glibc: " XSTR(__GLIBC__) "." XSTR(__GLIBC_MINOR__))

int main()
{
    printf("Compile time c standard (__STDC__): %d\n", __STDC__);
    printf("Compile time c standard (__STDC_VERSION__): %ld\n", __STDC_VERSION__);
    printf("Compile time glibc version: %d.%d\n", __GLIBC__, __GLIBC_MINOR__);
    printf("Runtime glibc version: %s\n", gnu_get_libc_version());
    printf("POSIX version: %ld\n", _POSIX_VERSION);
    return 0;
}
