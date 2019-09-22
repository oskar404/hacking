#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
    const char* nofile = "this_file_should_not_exist";
    const char* somefile = "/dev/random";
    const char* otherfile = "/dev/null";
    char buf[1];

    int fd0 = open(nofile, O_RDONLY);
    if (fd0 == -1) {
        int err = errno; // Store errno, perror and other calls may change it
        perror(nofile);
        printf("ERRNO: %d\n", err);
    }

    int fd1 = open(somefile, O_RDONLY);
    if (fd1 == -1) {
        int err = errno;
        perror(somefile);
        printf("ERRNO: %d\n", err);
        exit(EXIT_FAILURE);
    }

    int fd2 = open(otherfile, O_WRONLY);
    if (fd1 == -1) {
        int err = errno;
        perror(otherfile);
        printf("ERRNO: %d\n", err);
        exit(EXIT_FAILURE);
    }

    /* This should work */
    ssize_t rbytes = read(fd1, buf, sizeof(buf));
    if (rbytes == -1) {
        int err = errno;
        perror(somefile);
        printf("ERRNO: %d\n", err);
    } else {
        ssize_t wbytes = write(fd2, buf, rbytes);
        if (wbytes == -1) {
            int err = errno;
            perror(otherfile);
            printf("ERRNO: %d\n", err);
        }
    }

    /* Generate some errors */
    ssize_t wbytes = write(fd1, buf, rbytes);
    if (wbytes == -1) {
        int err = errno;
        perror("write()");
        printf("ERRNO: %d\n", err);
    }
    rbytes = read(fd2, buf, sizeof(buf));
    if (wbytes == -1) {
        int err = errno;
        perror("read()");
        printf("ERRNO: %d\n", err);
    }

    if (close(fd1) == -1) {
        int err = errno;
        perror(somefile);
        printf("ERRNO: %d\n", err);
    }
    if (close(fd2) == -1) {
        int err = errno;
        perror(otherfile);
        printf("ERRNO: %d\n", err);
    }

    /* Close a fd which is closed */
    if (close(fd1) == -1) {
        int err = errno;
        perror("close()");
        printf("ERRNO: %d\n", err);
    }

    return 0;
}
