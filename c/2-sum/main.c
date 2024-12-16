#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 2048

/**
 * @brief A Hash table implementation with linked list collision handling.
 * 
 */
struct HashTable{
    int key;
    int val;
    struct HashTable *next;
};

int hash(int key) {
    return (key % TABLE_SIZE + TABLE_SIZE) % TABLE_SIZE;
}

void insert(struct HashTable** table, int key, int val){
    int idx = hash(key);
    struct HashTable *new = malloc(sizeof(struct HashTable));
    new->key = key; new->val = val;     // New node crated

    new->next = table[idx];             // Link the standing node to the new node. NULL for an empty slot.
    table[idx] = new;                   // Finally insert the new node to the table index. A linked list is
}                                       // created that holds all the nodes with a conflicting hash.

struct HashTable** createTable() {
    // Allocate memory for an array of pointers HashTables
    struct HashTable** table = (struct HashTable**) malloc(sizeof(struct HashTable*) * TABLE_SIZE);
    for (size_t i = 0; i < TABLE_SIZE; i++) {
        table[i] = NULL;
    }

    return table;
}

struct HashTable* find(struct HashTable **table, int key) {
    int idx = hash(key);

    struct HashTable *node = table[idx];
    while (node != NULL) {
        if (node->key == key) {
            return node;
        }
        node = node->next;
    }
    return NULL;
}

void FreeHashTable(struct HashTable **table) {
    for (size_t i = 0; i < TABLE_SIZE; i++) {
        struct HashTable *node = table[i];      // Get the pointer to the linked list

        while (node != NULL) {                  // Check if the node is not NULL
            struct HashTable *tmp = node;       // Copy the pointer of the node
            node = node->next;                  // Move to the next node
            free(tmp);                          // Free the previous node
        }
    }

    free(table);  // Free the hash table array
}

int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    *returnSize = 2;
    int *ret = (int*) malloc(sizeof(int) * (*returnSize));    
    struct HashTable **table = createTable();

    for (size_t i = 0; i < numsSize; i++){
        int complement = target - nums[i];
        struct HashTable *node = find(table, complement);

        if (node != NULL) {
            ret[0] = node->val;  
            ret[1] = i;          
            FreeHashTable(table); 
            return ret;
        }

        insert(table, nums[i], i);
    }
    FreeHashTable(table);
    return ret;
}

int main(int argc, char **argv){
    
    int target = 9;
    int nums[4] = {2, 7, 11, 15};
    int retsize = 2;

    int *sol = twoSum(nums, 4, 9, &retsize);
    printf("%d, %d\n", sol[0], sol[1]);
    free(sol);
    return 0;
}