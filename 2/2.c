#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* args[]) {
    
    // get input from file
    FILE* file = fopen("input", "r");
    // line from file
    char line[128];
    // buffer for strtok
    char buff[128];
    // amount of valid passwords
    int count = 0;
    int count2 = 0;

        if (!file) {
        printf("no file error!");
        exit(-1);
    }

    while (fgets(line, 128, file)) {
        line[ strcspn(line, "\r\n") ]=0;
        strcpy(buff, line);
        //printf("%s\n", line);
        int min, max, charcount;
        char c;
        
        charcount = 0;

        // get and set min
        char* token = strtok(buff, "- :");
        min = atoi(token);
        //printf("%d\n", min);

        // get and set max
        token = strtok(NULL, "- :");
        max = atoi(token);
        //printf("%d\n", max);
        
        // get and set char
        token = strtok(NULL, "- :");
        c = *token;
        //printf("%s\n", c);

        for (int i = 0; i < strlen(line); i++) {
            if(line[i] == c) {
                charcount++;
                
            }
        }
        
        charcount--;
        //printf("%d\n", charcount);

        if ( (charcount >= min) && (charcount <= max))
        {
            count++;
            //printf("current line: %s\n", line);
        } 

        // part two code from here on out.

        // get just the password
        token = strtok(NULL, "- :");

        // if the character exists in only one position, increment the count
        if (token[(min-1)] == c) {
            if(token[(max-1)] != c)
            {
            count2++;
            //printf("yes\n");
            }
        }
        else if (token[(max-1)] == c) {
            if(token[(min-1)] != c)
            {
            count2++;
            //printf("yes\n");
            }
        }
    }

    printf("part 1 password count: %d\n", count);
    printf("part 2 password count: %d\n", count2);

    fclose(file);


}