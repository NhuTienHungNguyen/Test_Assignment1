#include<stdio.h>
#include<stdlib.h>
#include"bst.h"

typedef char* String;

typedef struct listNode {
  String unit_code;
  StudentBST student_list;
  struct listNode* next;
} *ListNodePtr;

typedef struct list {
  ListNodePtr head;
} UnitList;

/*typedef struct listNode {
  int unit_code;
  StudentBST student_list;
  struct listNode* next;
} *ListNodePtr;

typedef struct list {
  ListNodePtr head;
} UnitList;*/

UnitList new_list();