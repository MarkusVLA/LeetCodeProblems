#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

void free_list(struct ListNode *node){
    if (node){
        free_list(node->next);
        free(node);
    } else { return; }
}

void print_list(struct ListNode *node){
    if (node) {
        printf("%d", node->val);
        if (node->next) printf("--");
        print_list(node->next);
    } else { 
        printf("\n");
        return;
    }
}

struct ListNode *make_node(int val){
    
    if (val > 9) {
        fprintf(stderr, "Value of node may nor exeed 9\n");
        return NULL;
    }

    struct ListNode *node = (struct ListNode*) malloc(sizeof(struct ListNode));
    if (!node){
        fprintf(stderr, "Failed to allecate node!\n");
        return NULL;
    }

    node->val = val;
    node->next = NULL;
    return node;
}

void insert(struct ListNode *node, int val){
    if (!node) {
        fprintf(stderr, "Error: Trying to insert in NULL node!\n");
        return;
    }

    if (node && !node->next) {
        node->next = make_node(val);
        return;
    } else { insert(node->next, val); }
}


#define NODE_VAL(node) ((node != NULL) ? node->val: 0)

struct ListNode* addTwoNumbers(struct ListNode *l1, 
                               struct ListNode *l2){
    
    struct ListNode *result = make_node(0);
    struct ListNode *tmp = result; // copy results pointer.
    int carry = 0;

    while (l1 != NULL || l2 != NULL || carry) {

        int total = NODE_VAL(l1) + NODE_VAL(l2) + carry; 
        carry = (total / 10) >= 1;
        tmp->val = total % 10;

        if ((l1 && l1->next) || (l2 && l2->next) || carry) insert(tmp, 0);
        tmp = tmp->next;

        if (l1 != NULL) l1 = l1->next;
        if (l2 != NULL) l2 = l2->next;

    }     
    return result;
}

int main(int argc, char **argv){
    struct ListNode *list1 = make_node(9);
    struct ListNode *list2 = make_node(9);

    insert(list1, 9);
    insert(list1, 9);

    insert(list2, 9);
    insert(list2, 9);

    struct ListNode *result = addTwoNumbers(list1, list2); 

    printf("1: ");
    print_list(list1);

    printf("2: ");
    print_list(list2);

    printf("Result: ");
    print_list(result);

    free_list(list1);
    free_list(list2);
    free_list(result);

    printf("\nDone!\n");
    return 0;
}


