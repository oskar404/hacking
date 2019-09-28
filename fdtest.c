#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>


#define POEM_SIZE 5
#define BUF_SIZE 255

int main()
{

    /* poem from: https://www.poetrysoup.com/poem/my_friend_the_nerd_380981 */
    const char* poem[POEM_SIZE] = {
        "My friend the nerd\n",
        "Embraced by bits and bytes\n",
        "And yet forever lonely\n",
        "I showed him Playboy sites\n",
        "He visits them ’text only'"
    };

    const char* testfile = "testfile";
    char buffer[BUF_SIZE];
    int return_value = 0;
    int wfd = open(
            testfile, O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);

    if (wfd == -1)
    {
        perror(testfile);
        exit(EXIT_FAILURE);
    }

    int rfd = open(
            testfile, O_RDONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);

    if (rfd == -1)
    {
        perror(testfile);
        exit(EXIT_FAILURE);
    }

    printf("# wfd:%d rfd:%d\n\n", wfd, rfd);

    for (int i=0; i < POEM_SIZE; i++)
    {
        size_t len = strlen(poem[i]);
        if (write(wfd, poem[i], len) == -1)
        {
            perror(testfile);
            exit(EXIT_FAILURE);
        }
        ssize_t rlen = read(rfd, buffer, BUF_SIZE);
        if (rlen == -1)
        {
            perror(testfile);
            return_value = EXIT_FAILURE;
        }
        if (rlen != len)
        {
            printf("  rlen:%ld != len:%ld\n", rlen, len);
        }
        printf("  %s", poem[i]);
    }

    printf("\n\n");

    if (close(wfd) == -1) {
        perror(testfile);
        return_value = EXIT_FAILURE;
    }

    if (close(rfd) == -1) {
        perror(testfile);
        return_value = EXIT_FAILURE;
    }

    return return_value;
}
