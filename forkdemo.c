#include <stdio.h>
#include <unistd.h>

int main()
{
    int i;
    if (fork())
    {
        for (i = 0; i < 10000; ++i)
        {
            printf("** PARENT %d\n",i);
        }
    }
    else
    {
        for (i = 0; i < 10000; ++i)
        {
            printf("  => CHILD %d\n",i);
        }
    }
    return 0;
}
