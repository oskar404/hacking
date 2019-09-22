
#include <stdio.h>
#include <unistd.h>

int main(int argc, char** argv)
{
    for (int i = 0; i < argc; ++i)
        printf("%d: %s\n", i, argv[i]);
    for (int i = 0; i >= 0 ; ++i)
    {
        /* Read outside argv seg faults */
        for (int j = 0; '\0' != (char)argv[i][j] ; j++)
            putchar((char) argv[i][j]);
        putchar('\n');
        sleep(3);
    }
    return 0;
}
