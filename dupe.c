/* fileno() and dprintf() require _POSIX_C_SOURCE definition */
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>


#define POEM_SIZE 5

int main()
{

    /* poem from: https://www.poetrysoup.com/poem/null_hypothesis_536101 */
    /*            null hypothesis */
    const char* poem[POEM_SIZE] = {
        "we choose to reject\n",
        "the null hypothesis \n",
        "when it is true,\n",
        "but why I still love you leaves\n",
        "no alternative"
    };

    const char* testfile = "testfile";
    size_t len;
    int outfd, errfd;
    int fd = open(
            testfile, 
            O_RDWR|O_CREAT|O_TRUNC|O_APPEND|O_EXCL, 
            S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);

    if (fd == -1)
    {
        perror(testfile);
        exit(EXIT_FAILURE);
    }

    printf("# directing stdout & stderr to %d\n", fd);

    outfd = fileno(stdout);
    if (outfd == -1)
    {
        perror("fileno(stdout)");
        exit(EXIT_FAILURE);
    }
    
    errfd = fileno(stderr);
    if (errfd == -1)
    {
        perror("fileno(stderr)");
        exit(EXIT_FAILURE);
    }
    
    outfd = dup2(fd, outfd);
    if (outfd == -1)
    {
        perror("dup2(fd, stdout)");
        exit(EXIT_FAILURE);
    }

    errfd = dup2(fd, errfd);
    if (errfd == -1)
    {
        perror("dup2(fd, stderr)");
        exit(EXIT_FAILURE);
    }

    len = strlen(poem[0]);
    if (write(fd, poem[0], len) == -1)
        perror("write(fd)");

    if (printf("%s", poem[1]) < 0)
        perror("prinf()");

    if (fprintf(stderr, "%s", poem[2]) < 0)
        perror("fprinf(stderr)");

    len = strlen(poem[3]);
    if (write(outfd, poem[3], len) == -1)
        perror("write(outfd)");

    if (dprintf(errfd, "%s", poem[2]) < 0)
        perror("dprinf(errfd)");

    if (close(fd) == -1) {
        perror(testfile);
        exit(EXIT_FAILURE);
    }

    return 0;
}
