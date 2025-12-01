/*
 * Binary tree demo
 *
 * Builds a small static tree with nodes and demonstrates:
 *   - printing the tree with indentation
 *   - counting all nodes in the tree
 *   - searching for a given value
 *   - freeing all dynamically allocated memory
 *
 * Author: Samuel Krajcovic
 * Description: School project for practicing pointers, structs and recursion.
 */

#include <stdio.h>
#include <stdlib.h>


struct item {
    char a;
    struct item *nextRight;
    struct item *nextLeft;
    
};


char space[80];

//! Functions to add and remove indentation spaces

void spaceAdd(){
    int i;
    for(i = 0; space[i] != '\0'; i++); 

    space[i] = ' '; i++;
    space[i] = ' '; i++;
    space[i] = '\0'; 
}

void spaceDel(){
    int i;
    for(i = 0;space[i] != '\0'; i++);
    i -= 2;
    space[i] = '\0';
}

//! Frees all nodes in the tree (post-order traversal)
void freeTree(struct item *node) {
    if(node == NULL) return;
    freeTree(node->nextLeft);
    freeTree(node->nextRight);
    free(node);

}


//! Prints the tree with indentation

void showTree(struct item *currentItem){
    printf("\n%s-%c", space, currentItem->a);

    if(currentItem->nextRight != NULL){
        spaceAdd();
        showTree(currentItem->nextRight);
        spaceDel();
    }
    if(currentItem->nextLeft != NULL){
        spaceAdd();
        showTree(currentItem->nextLeft);
        spaceDel();
    }
}

//! Counts all items in the tree
int countItems(struct item *node) {
    if (node == NULL) return 0; 
    return 1 + countItems(node->nextLeft) + countItems(node->nextRight);
}


//! Searches for a given character in the tree

int findItem(struct item *node, char target) {
    if(node == NULL) return 0;
    if (node->a == target) return 1;

    return findItem(node->nextLeft, target) || findItem(node->nextRight, target);
}


//!Main program
int main() {
    space[0] = ' ';
    space[1] = ' ';
    space[2] = '\0';

    // Pointer to tree root
    struct item * root;

    

    // Create root 'A'
    root = (struct item*) malloc(sizeof(struct item));
    root->a = 'A';
    root->nextLeft = NULL;
    root->nextRight = NULL;



    printf("Tree root: %c\n", root->a);

    // Add right child 'B'
    root->nextRight = (struct item*)malloc(sizeof(struct item));
    root->nextRight->a = 'B';
    root->nextRight->nextLeft = NULL;
    root->nextRight->nextRight = NULL;

   
    // Add left child 'C'
    root->nextLeft = (struct item*)malloc(sizeof(struct item));
    root->nextLeft->a = 'C';
    root->nextLeft->nextLeft = NULL;
    root->nextLeft->nextRight = NULL;

    
    // Pointer to left child of root (node 'C')
    struct item *current = root->nextLeft; //Current ukazuje na C 
    // Right child of 'C' → 'D'
    current->nextRight = (struct item*)malloc(sizeof(struct item));
    current->nextRight->a = 'D';
    current->nextRight->nextLeft = NULL;
    current->nextRight->nextRight = NULL;

    // Left child of 'C' → 'E'
    current->nextLeft = (struct item*)malloc(sizeof(struct item));
    current->nextLeft->a = 'E';
    current->nextLeft->nextLeft = NULL;
    current->nextLeft->nextRight = NULL;

 

    // Children of 'B'
    struct item *nodeB = root->nextRight; // points to 'B'
    nodeB->nextLeft = (struct item*)malloc(sizeof(struct item));
    nodeB->nextLeft->a = 'F';
    nodeB->nextLeft->nextLeft = NULL;
    nodeB->nextLeft->nextRight = NULL;

    nodeB->nextRight = (struct item*)malloc(sizeof(struct item));
    nodeB->nextRight->a = 'G';
    nodeB->nextRight->nextLeft = NULL;
    nodeB->nextRight->nextRight = NULL;

    //Print whole tree
    showTree(root);
    //Search for an item
    char lookFor = 'D';
    if(findItem(root, lookFor)){
        printf("\nItem '%c' was found in the tree.\n",lookFor);
    }else{
        printf("\nItem '%c' was NOT found in the tree.\n", lookFor);
    }


    int total = countItems(root);
    printf("\nTotal number of nodes in the tree: %d\n", total);

    freeTree(root);
    root = NULL;

    return 0;
}
