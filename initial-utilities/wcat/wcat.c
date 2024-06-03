#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 2048

int main(int argc, char *argv[])
{
    int numFiles = argc - 1;
    for(int i = 0; i < numFiles; i++)
    {
        char buffer[BUFFER_SIZE];
        FILE *fp = fopen(argv[i+1],"r");
        if (fp == NULL)
        {
            printf("wcat: cannot open file\n");
            exit(1);
        }

        while(fgets(buffer, BUFFER_SIZE, fp) != NULL)
        {
            printf("%s", buffer);
        }

    }

    return 0;
}
