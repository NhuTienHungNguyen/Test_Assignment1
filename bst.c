#include<stdio.h>
#include"bst.h"

StudentBST new_bst() {
	StudentBST temp;                  //create  new binary search tree
	temp.root = NULL;          //allocate the root of the new binary search tree to NULL
	return temp;
}