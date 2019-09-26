#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>


int main()
{
    const char* testfile = "/dev/random";
    int cntr = 0;
    int fd;

    for (int tfd ; tfd = open(testfile, O_RDONLY), tfd != -1; cntr++, fd = tfd)
        ; /* empty loop */

    {
    int err = errno;
    perror(testfile);
    printf("ERRNO: %d\n", err);
    printf("cntr: %d\n", cntr);
    printf("fd: %d\n", fd);
    }

    if (close(fd) == -1) {
        int err = errno;
        perror(testfile);
        printf("ERRNO: %d\n", err);
        printf("cntr: %d\n", cntr);
        printf("fd: %d\n", fd);
    }

    for (int tfd ; tfd = open(testfile, O_RDONLY), tfd != -1; cntr++, fd = tfd)
        ; /* empty loop */

    {
    int err = errno;
    perror(testfile);
    printf("ERRNO: %d\n", err);
    printf("cntr: %d\n", cntr);
    printf("fd: %d\n", fd);
    }

    return 0;
}
