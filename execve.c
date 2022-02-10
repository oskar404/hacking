#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>


// int execve(const char *filename, char *const argv[], char *const envp[]);

void test(const char *cmd, char *const argv[], char *const envp[])
{
    printf(">>>>> %s\n", cmd);
    if (fork() == 0) /* child */
    {
        execve(cmd, argv, envp);
        perror(cmd);
        exit(1);
    }
    else /* parent */
    {
        wait(0);
    }
}

int main()
{
    char *empty[1];
    empty[0] = NULL;

    test("./main0", empty, empty);
    test("./main1", empty, empty);
    test("./main2", empty, empty);
    return 0;
}
