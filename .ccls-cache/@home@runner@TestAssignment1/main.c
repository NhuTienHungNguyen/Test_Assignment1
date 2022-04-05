#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "list.h"

bool checkUnit(UnitList* the_List, String code) {
	ListNodePtr current = the_List->head;
	bool check = false;

	while (current != NULL && check == false) {
		if (strcmp(current->unit_code, code) == 0) {
			check = true;
		}

    current = current->next;
	}

	return check;
}

bool checkStudentNode(BSTNodePtr root, long student_ID) {
	bool res1;
	bool res2;

	if (root == NULL) {
		return false;
	}
	else if (root->student_id == student_ID) {
		return true;
	}

	res1 = checkStudentNode(root->left, student_ID);
	res2 = checkStudentNode(root->right, student_ID);

	if (res1 == true) {
		return true;
	}
	else if (res2 == true) {
		return true;
	}
	else {
		return false;
	}
}

bool checkStudent(StudentBST* student_list, long student_ID) {
	return checkStudentNode(student_list->root, student_ID);
}

//sua thanh add in order
void addUnit (UnitList* the_list, String code) {
  if (checkUnit(the_list, code) == false) {
		ListNodePtr new_node = malloc(sizeof * new_node);

		new_node->unit_code = malloc((strlen(code) + 1) * sizeof(char));
    strcpy(new_node->unit_code, code);
		new_node->next = the_list->head;
		the_list->head = new_node;
	}
	else {
		printf("This unit is already exist! \n");
	}
}

void removeUnit(UnitList* the_List, String code) {
	if (checkUnit(the_List, code) == false) {
		printf("This unit is not exist! \n");
	}
	else {
		ListNodePtr current = the_List->head;
		ListNodePtr prev = NULL;

		while (current != NULL) {
			if (strcmp(current->unit_code, code) == 0) {
				if (prev == NULL) {
					the_List->head = current->next;
					free(current);
					current = the_List->head;
				}
				else {
					prev->next = current->next;
					free(current);
					current = prev->next;
				}
			}
			else {
				prev = current;
				current = current->next;
			}
		}
	}
}

BSTNodePtr insert_student_node(BSTNodePtr root, long student_ID) {
	if (root == NULL) {
		BSTNodePtr new_student = malloc(sizeof * new_student);
		new_student->student_id = student_ID;
		new_student->left = new_student->right = NULL;
		root = new_student;
	}
	else if (student_ID < root->student_id) {
		root->left = insert_student_node(root->left, student_ID);
	}
	else if (student_ID > root->student_id) {
		root->right = insert_student_node(root->right, student_ID);
	}

	return root;
}

void insert_student(StudentBST* student_list, long student_ID) {
	student_list->root = insert_student_node(student_list->root, student_ID);
}

BSTNodePtr min_node(BSTNodePtr root) {
	BSTNodePtr current = root;         //new node to be the cursor
	while (current->left != NULL) {
		current = current->left;
	}

	return current;
}

BSTNodePtr delete_student_node(BSTNodePtr root, long student_ID) {

	//searching for the data to be deleted
	if (root != NULL) {
		if (student_ID == root->student_id) {
			if (root->left != NULL && root->right != NULL) {
				BSTNodePtr successor = min_node(root->right);
				root->student_id = successor->student_id;
				root->right = delete_student_node(root->right, root->student_id);
			}
			else {
				BSTNodePtr to_free = root;
				if (root->left) {
					root = root->left;
				}
				else {
					root = root->right;
				}
				free(to_free);
			}
		}
		else if (student_ID < root->student_id) {
			root->left = delete_student_node(root->left, student_ID);
		}
		else {
			root->right = delete_student_node(root->right, student_ID);
		}
	}

	return root;
}

void delete_student(StudentBST* student_list, long student_ID) {
	student_list->root = delete_student_node(student_list->root, student_ID);
}

void enrol_Student(UnitList* the_List, long student_ID, String unit_Code) {
	ListNodePtr current = the_List->head;
	bool check_student;

	while (strcmp(current->unit_code, unit_Code) != 0) {
		current = current->next;
	}

	check_student = checkStudent(&(current->student_list), student_ID);

	if (check_student == false) {
		insert_student(&(current->student_list), student_ID);
	}
	else {
		printf("This student is already exist! \n");
	}
}

void unerol_Student(UnitList* the_List, long student_ID, String unit_Code) {
	ListNodePtr current = the_List->head;
	bool check_student;

	while (strcmp(current->unit_code, unit_Code) != 0) {
		current = current->next;
	}


	check_student = checkStudent(&(current->student_list), student_ID);

	if (check_student == true) {
		delete_student(&(current->student_list), student_ID);
	}
	else {
		printf("This student is not exist! \n");
	}
}

int calculate_student_node(BSTNodePtr root) {
	if (root == NULL) {
		return 0;
	}
	else {
		return 1 + calculate_student_node(root->left) + calculate_student_node(root->right);
	}
}

int calculate_student(StudentBST* student_list) {
	return calculate_student_node(student_list->root);
}

void print_ordered_summary(UnitList* the_list) {
	ListNodePtr current = the_list->head;

	while (current != NULL) {
    StudentBST student_list = current->student_list;
		printf("Unit: %s ", current->unit_code);
    printf("have %d student(s)\n", calculate_student(&student_list));
    current = current->next;
	}
}

void print_unit_students_node(BSTNodePtr root) {
  if (root != NULL) {
    printf("Student ID: %ld \n", root->student_id);
		print_unit_students_node(root->left);
		print_unit_students_node(root->right);
  }
}

void print_unit_students(StudentBST* student_list) {
  print_unit_students_node(student_list->root);
}

void print_unit_information(UnitList* the_list, String code) {
  ListNodePtr current = the_list->head;
  StudentBST student_list;

	while (current != NULL && strcmp(current->unit_code, code) != 0) {
    current = current->next;
	}
  
  student_list = current->student_list;
  print_unit_students(&student_list);
  
}

void print_student_information (UnitList* the_list, long student_id) {
  ListNodePtr current = the_list->head;
	bool check_student;

  while (current != NULL) {
    check_student = checkStudent(&(current->student_list), student_id);

	  if (check_student == true) {
		  printf("Unit: %s \n", current->unit_code);
	  }

    current = current->next;
  }
  
}

int main(void) {
  UnitList unit_list = new_list();
	int quit = 0;

	while (!quit)
	{
		int option;
		printf("Menu list: \n 0. Quit program \n 1. Add an unit \n 2. Remove an unit \n 3. Enrol a student in an unit \n 4. Withdraw a student from an unit \n 5. Print summary \n 6. Print information for an unit \n 7. Print information about a student \n");
		printf("Please enter your option: ");
		scanf("%d", &option);

		if (option == 0)
		{
			quit = 1;
		}
		else if (option == 1)
		{
			char unit_code[100];
			printf("Enter the unit code you want to add: ");
			scanf("%s", unit_code);
			addUnit(&unit_list, unit_code);
		}
		else if (option == 2)
		{
			char unit_code[100];
			printf("Enter the unit code you want to delete: ");
			scanf("%s", unit_code);
			removeUnit(&unit_list, unit_code);
		}
		else if (option == 3)
		{
			char unit_code[100];
			long student_id;
			bool check_unit;
			
			printf("Enter the student ID you want to enrol: ");
			scanf("%ld", &student_id);

			printf("Enter the unit you want to enrol this student: ");
			scanf("%s", unit_code);

			check_unit = checkUnit(&unit_list, unit_code);

			if (check_unit == true) {
				enrol_Student(&unit_list, student_id, unit_code);
			}
			else {
				printf("This unit is not exist! \n");
			}
		}
		else if (option == 4)
		{
			char unit_code[100];
			long student_id;
			bool check_unit;

			printf("Enter the student ID you want to withdraw: ");
			scanf("%ld", &student_id);

			printf("Enter the unit you want to withdraw this student: ");
			scanf("%s", unit_code);

			check_unit = checkUnit(&unit_list, unit_code);

			if (check_unit == true) {
				unerol_Student(&unit_list, student_id, unit_code);
			}
			else {
				printf("This unit is not exist! \n");
			}
		}
		else if (option == 5) {
			print_ordered_summary(&unit_list);
		}
    else if (option == 6) {
      char unit_code[100];
      bool check_unit;

      printf("Enter the unit you want to show information: ");
			scanf("%s", unit_code);
      
      check_unit = checkUnit(&unit_list, unit_code);

      if (check_unit == true) {
				print_unit_information(&unit_list, unit_code);
			}
			else {
				printf("This unit is not exist! \n");
			}
    }
    else if (option == 7) {
      long student_id;
      
      printf("Enter the student ID you want to show: ");
			scanf("%ld", &student_id);

      print_student_information(&unit_list, student_id);
    }
	}
  
  return 0;
}