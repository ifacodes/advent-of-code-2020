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
    return a % 1048576;
}

typedef struct bucket {
    uint32_t value;
} set_bucket;

typedef struct set {
    uint32_t set[1048576];
} hashset;

int hashset_add(hashset *set, int item) {
    if (item == NULL) {
        return -1;
    }
    uint32_t value = hash((uint32_t)item);
    if (value >=1048576 )
    {
        return -1;
    }
    set->set[value] = item;
    //printf("%" PRIu32 "\n", value);

    return 1;
}

int hashset_find(hashset *set, int query) {
    uint32_t query_hash = hash((uint32_t)query);
    if (set->set[query_hash] != query)
    {
        return 0;
    }
    return query;
}

int hashset_find_three(hashset *set, int query) {
    uint32_t query_hash = hash((uint32_t) query);
}

int main(int argc, char* args[]) {


    hashset set;

    // number array
    int list[199];
    int count = 0;

    // tmp line alllocation
    char line[6];
    // open input file
    FILE *fp = fopen("input", "r");
    FILE *output = fopen("output", "w+");

    if (!fp || !output) {
        printf("no file error!");
        exit(-1);
    }
    // input into hashset
    while(fgets(line, sizeof(line), fp)) {
        // remove carriage return and newline
        line[ strcspn(line, "\r\n") ]=0;
        // add to number array for later querying
        list[count] = atoi(line);
        // convert to integer from string and add to hashset
        hashset_add(&set, list[count]);
        count++;
    }
    fclose(fp);

    for (int i = 0; i < 199; i++) {
       int result = hashset_find(&set, 2020-list[i]);
       if (result != 0) 
       { printf("%d\n", result);}
    }

    printf("PART TWO \n\n");
    
    for (int j = 0; j < 199; j++) {
        int num1 = 2020-list[j];
        for (int k = 0; k < 199; k++) {
            int result = hashset_find(&set, num1-list[k]);
            if (result != 0) 
            { 
                printf("num1: %d\nnum2: %d\nnum3: %d\nmultiple: %d\n\n", list[j], list[k], result, list[j]*list[k]*result);
                break;
            }
        }
    }

    fclose(output);

    return 0;

}





