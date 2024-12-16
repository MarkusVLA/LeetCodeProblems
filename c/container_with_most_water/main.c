#include <stdio.h>

#define MIN(a, b) ((a < b) ? a: b)

// Function pointer for our debug funcrion.
typedef void (*debugCallback)(const int, const char*);

int maxArea(int* height, int heightSize) {
    int max = 0;
    int p1 = 0, p2 = heightSize - 1;

    while (p2 > p1){ // until pointers meet in the middle.
        int area = MIN(height[p1], height[p2]) * (p2 - p1);
        if (area > max) max = area;
        // move the smaller poiner inward
        if (height[p1] > height[p2]) {
            p2--;
        } else { p1++; }
    }

    return max;
}

void writeToFile(const int val, const char *fileName){
    // Just write s to file for debug purposes.
    FILE *fp = fopen(fileName, "a");
    fprintf(fp, "%d\n", val);
    fclose(fp);
}

int main(int arvc, char **argv){
    
    int height[9] = {1,8,6,2,5,4,8,3,7};
    // int height[4] = {1, 2, 4, 3};
    int result = maxArea(height, 9);
    printf("Result: %d\n", result);

    return 0;
}
