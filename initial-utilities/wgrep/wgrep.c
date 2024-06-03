#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define BUFFER_SIZE 4096

bool foundKeyInLine(char* buffer, char* keyword)
{
    bool found = false;
    int keyIdx = 0;
    int i = 0;
    while(buffer[i] != '\n')
    {
        if(buffer[i] == keyword[keyIdx])
        {
            keyIdx++;
            if(keyword[keyIdx] == '\0')
            {
                found = true;
                break;
            }
        }
        else
        {
            keyIdx = 0;
        }
        i++;
    }

    return found;
}

int main(int argc, char *argv[])
{
    if(argc <= 1)
    {
        printf("wgrep: searchterm [file ...]\n");
        exit(1);
    }

    char *keyword = argv[1];
    //no search term, just exit
    if(keyword[0] == '\0')
    {
        return 0;
    }

    //check if we were passed any files...
    if(argc > 2)
    {
        //... and if so iterate over all files
        for(int i = 2; i < argc; i++)
        {
            char *buffer = NULL;
            size_t length = 0;
            FILE *fp = fopen(argv[i],"r");
            if (fp == NULL)
            {
                printf("wgrep: cannot open file\n");
                exit(1);
            }
    
            while(getline(&buffer, &length, fp) != -1)
            {
                if(foundKeyInLine(buffer, keyword))
                {
                    printf("%s",buffer);
                }
            }
    
            free(buffer);
    
        }
    }
    else //if no files passed just wait for input from stdin
    {
        char buffer[BUFFER_SIZE];
        while(fgets(buffer, BUFFER_SIZE, stdin) != NULL)
        {
            if(foundKeyInLine(buffer, keyword))
            {
                printf("%s",buffer);
            }
        }
    }
  

    return 0;
}
