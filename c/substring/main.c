#include <stdio.h>
#include <stdlib.h>

#define N_SYMBOLS 256 // number of letters numbers and symbols


int lengthOfLongestSubstring(char* s) {

    int* seen = (int*) calloc(N_SYMBOLS, sizeof(int)); 
    int start = 0, longest = 0;

    for (int i = 0; s[i] != '\0'; i++) {

        if (seen[(unsigned char)s[i]] > 0 && seen[(unsigned char)s[i]] > start) {
            start = seen[(unsigned char)s[i]]; 
        }

        seen[(unsigned char)s[i]] = i + 1;
        longest = (i - start + 1 > longest) ? (i - start + 1) : longest;
    }

    free(seen);
    return longest;
}



int main(int argc, const char** argv){
    if (argc != 2){
        printf("Usage ./app <string>\n");
        return 1;
    } else {
        int result = lengthOfLongestSubstring((char*) argv[1]); 
        printf("Longest sub-string: %d\n", result);
        return 0;
    }
}
