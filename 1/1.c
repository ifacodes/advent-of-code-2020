#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>


uint32_t hash( uint32_t a)
{
    a = (a+0x7ed55d16) + (a<<12);
    a = (a^0xc761c23c) ^ (a>>19);
    a = (a+0x165667b1) + (a<<5);
    a = (a+0xd3a2646c) ^ (a<<9);
    a = (a+0xfd7046c5) + (a<<3);
    a = (a^0xb55a4f09) ^ (a>>16);
    return a;
}


int main(int argc, char* args[]) {

    int numbers[199];
    int count = 0;
    // tmp line alllocation
    char line[6];
    // open input file
    FILE *fp = fopen("input", "r");

    if (!fp) {
        printf("no file error!");
        exit(-1);
    }
    
    while(fgets(line, sizeof(line), fp)) {
        // remove carriage return and newline
        line[ strcspn(line, "\r\n") ]=0;
        // convert to integer from string and add to array
        numbers[count] = atoi(line);
        // output number
        printf("%d\n", numbers[count]);
        // output hashed number
        printf("%" PRIo32 "\n", hash((uint32_t)numbers[count]));
        count++;
    }
    fclose(fp);

    //printf("%lu\n", hash("Alicja"));

    return 0;

}




