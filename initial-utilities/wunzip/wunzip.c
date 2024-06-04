//aaaabbbbbbbb test i amm aaa     commment

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    int numFiles = argc - 1;
    if(numFiles == 0)
    {
        printf("wunzip: file1 [file2 ...]\n");
        exit(1);
    }

    int itemsRead = 0;
    int fileIdx = 1;
    char buffer[5];
    bool done = false;

    FILE *fp = fopen(argv[fileIdx],"r");
    if (fp == NULL)
    {
        printf("wunzip: cannot open file\n");
        exit(1);
    }
    while(!done)
    {
        itemsRead = fread(&buffer, 5, 1, fp);
        uint32_t numRepetitions = *(uint32_t*)(buffer);

        if(itemsRead == 0)
        {
            fileIdx++;
            if(fileIdx > numFiles)
            {
                done = true;    
            }
            else
            {
                fp = fopen(argv[fileIdx],"r");
                if (fp == NULL)
                {
                    printf("wunzip: cannot open file\n");
                    exit(1);
                }                
            }
        }
        else
        {
            char repeatedChar = buffer[4];
            for(int i = 0; i < numRepetitions; i++)
            {
                printf("%c",repeatedChar);
            }
        }   
    }

    return 0;
}