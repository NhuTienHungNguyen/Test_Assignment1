#include<stdio.h>
#include<stdlib.h>
#include"list.h"

UnitList new_list() {
  UnitList temp;

  temp.head = NULL;

  return temp;
}