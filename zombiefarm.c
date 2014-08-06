#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    int i;
    for (i=0; i<5 ; ++i)
    {
        if (fork() == 0)
        {
            exit(0);
        }
        sleep(1000);
    }
    return 0;
}
