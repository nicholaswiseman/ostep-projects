//aaaabbbbbbbb test i amm aaa     commment

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
    int numFiles = argc - 1;
    if(numFiles == 0)
    {
        printf("wzip: file1 [file2 ...]\n");
        exit(1);
    }

    int bytesRead = 0;
    int fileIdx = 1;
    char startChar = 0;
    char nextChar = 0;
    bool done = false;

    FILE *fp = fopen(argv[fileIdx],"r");
    if (fp == NULL)
    {
        printf("wzip: cannot open file\n");
        exit(1);
    }
    bytesRead = fread(&startChar, 1, 1, fp);
    while(!done)
    {
        int repeatingByteCount = 0;
        do
        {
            //read the stream  one byte at a time
            repeatingByteCount++;
            bytesRead = fread(&nextChar, 1, 1, fp);
            //if we reach eof either update the file pointer
            //or just be done if theres no more files
            if(bytesRead == 0)
            {            
                if(fileIdx == numFiles)
                {
                    done = true;
                }
                else
                {
                    fp = fopen(argv[++fileIdx],"r");
                    bytesRead += fread(&nextChar, 1, 1, fp);
                }
            }
        // break out when we finish reading repeating character or if we are done  
        }while((startChar == nextChar) && !done);

        fwrite(&repeatingByteCount, 4, 1, stdout);
        fwrite(&startChar, 1, 1, stdout);
        startChar = nextChar;     
    }

    return 0;
}