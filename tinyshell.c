#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
    char line[256];

    while (printf("> "), fgets(line, sizeof(line), stdin) != NULL)
    {
        if (fork() == 0) /* Child */
        {
            execlp(line, line, (char *)0);
            /* Don't come here if execlp() fails */
            /* printf("Unknown command: %s\n", line); */
            perror(line);
            exit(1);
        }
        else /* Parent/shell */
        {
            wait(0);
        }
    }
    return 0;
}
