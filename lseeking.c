#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>


#define POEM_SIZE 13

int main()
{

    /* poem by: https://hellopoetry.com/u738952/ */
    /* If six were nine and Jimi Hendrix a nun */

    const char* poem[POEM_SIZE] = {
        "If six were nine",
        "And Jimi Hendrix a nun",
        "Would nine be none",
        "Null and nil ?",
        "And if sixth were ninth",
        "And Jimi Hendrix a ninja",
        "Falling like a sun into the sea mountains",
        "on Ninety-null street",
        "The world famous Quatre-vingt-dix-nullième rue",
        "Would you mind ? Would you mind ?",
        "Would you mind if September stopped to exist",
        "And all the dead of September came back from Null None or Nil",
        "And Jimi Hendrix were seventy-six."
    };

    const char* testfile = "testfile";
    int fd = open(
            testfile, O_RDWR|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);

    if (fd == -1)
    {
        perror(testfile);
        exit(EXIT_FAILURE);
    }

    for (int i=0; i < POEM_SIZE; i++)
    {
        if (write(fd, poem[i], strlen(poem[i])) == -1)
        {
            perror(testfile);
            exit(EXIT_FAILURE);
        }
        off_t pos = -1 * (strlen(poem[i]) - (strchr(poem[i], ' ')-poem[i])) + 1;
        if (lseek(fd, pos, SEEK_END) == -1)
        {
            perror(testfile);
            exit(EXIT_FAILURE);
        }
        printf("  [%3ld] %s\n", pos, poem[i]);
    }

    if (close(fd) == -1) {
        perror(testfile);
        exit(EXIT_FAILURE);
    }

    return 0;
}
