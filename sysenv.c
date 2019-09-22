#include <stdio.h>
#include <unistd.h>
#include <gnu/libc-version.h>
#include <features.h>

/* Some macro magic to get compile time values printed on comile time */
#define XSTR(x) STR(x)
#define STR(x) #x
#pragma message("Compile time c standard (__STDC__): " XSTR(__STDC__))
#pragma message("Compile time c standard (__STDC_VERSION__): " XSTR(__STDC_VERSION__))
#pragma message("Compile time glibc: " XSTR(__GLIBC__) "." XSTR(__GLIBC_MINOR__))

int main()
{
    printf("Compile time glibc version: %d.%d\n", __GLIBC__, __GLIBC_MINOR__);
    printf("Runtime glibc version: %s\n", gnu_get_libc_version());
    printf("__STDC__: %d\n", __STDC__);
    printf("__STDC_VERSION__: %ld\n", __STDC_VERSION__);
    printf("_POSIX_VERSION: %ld\n", _POSIX_VERSION);
    /* gcc provides these/clang does not */
    /* printf("_POSIX_SOURCE: %ld\n", _POSIX_SOURCE); */
    /* printf("_POSIX_C_SOURCE: %ld\n", _POSIX_C_SOURCE); */
    printf("_XOPEN_SOURCE: %d\n", _XOPEN_VERSION);

    #if _BSD_SOURCE
    const char* bsd = "supported";
    #else
    const char* bsd = "";
    #endif
    printf("_BSD_SOURCE: %s\n", bsd);

    #if _SVID_SOURCE
    const char* svid = "supported";
    #else
    const char* svid = "";
    #endif
    printf("_SVID_SOURCE: %s\n", svid);

    #if _GNU_SOURCE
    const char* gnus = "supported";
    #else
    const char* gnus = "";
    #endif
    printf("_GNU_SOURCE: %s\n", gnus);
    return 0;
}
