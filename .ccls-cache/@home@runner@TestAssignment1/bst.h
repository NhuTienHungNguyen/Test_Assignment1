#include<stdio.h>
#include<stdlib.h>

typedef struct bstNode {
    long student_id;
    struct bstNode *left;
    struct bstNode *right;
} *BSTNodePtr;

typedef struct bst {
    BSTNodePtr root;
} StudentBST;

StudentBST new_bst();