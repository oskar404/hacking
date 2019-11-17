#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    printf("pid: %d\n",getpid());
    printf("parent pid: %d\n",getppid());
    return 0;
}
