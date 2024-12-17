#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_MAX_LEN 200
 
const char* words[3] = {"flower", "flow", "flight"}; // Maybe read contents from a file
// const char* words[3] = {"dog", "racecar", "car"};

typedef void (*insertCallback)(char** strs, unsigned i); // Insertion logic detached with callback.

void insertWord(char** strs, unsigned i){
    strcpy(strs[i], words[i]);    
}

char** makeStrs(int strSize, insertCallback callback){
    char **strs = (char**) malloc(sizeof(char*) * strSize); // cast pointer array
    for (size_t i = 0; i < strSize; i++){
        strs[i] = (char*) malloc(sizeof(char) * STR_MAX_LEN);
        callback(strs, (unsigned) i); 
    }
    return strs;
}

void printStrs(char **strs, int strSize){
    for (size_t i = 0; i < strSize; i++){
        printf("%s\n", strs[i]);
    }
}

void freeStrs(char **strs, int strSize){
    for (size_t i = 0; i < strSize; i++){
        free(strs[i]);
    }
    free(strs);
}

char* longestCommonPrefix(char** strs, int strsSize) {
    char* prefix = (char*) malloc(sizeof(char) * (STR_MAX_LEN + 1)); // \0
    short flag = 0; 
    int i = 0;

    for (; i < STR_MAX_LEN; i++){
        for (int j = 0; j < strsSize; j++){

            if (!strs[0][i] || strs[j][i] != strs[0][i]){ 
                flag++;
                break;
            } 
        }

        if (!flag) {
            prefix[i] = strs[0][i];
        } else { 
            prefix[i] = '\0';
            break; 
        } 
    }

    prefix = realloc(prefix, i + 1); 
    return prefix;
}


// Test
int main(int argc, char **argv){
    const int strSize = 3;
    char **strings = makeStrs(3, insertWord);
    printStrs(strings, strSize);
    printf("\nLonges prefix: ");
    char *answer = longestCommonPrefix(strings, strSize);
    printf("%s\nlenght: %lu\n", answer, strlen(answer));
    freeStrs(strings, strSize);
    free(answer);
    return 0;
}


