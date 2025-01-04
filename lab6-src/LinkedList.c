
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "LinkedList.h"

// Initialize a linked list
//
void llist_init(LinkedList * list)
{
	list->head = NULL;
}

//
// It prints the elements in the list in the form:
// 4, 6, 2, 3, 8,7
//
void llist_print(LinkedList * list) {
	
	ListNode * e;

	if (list->head == NULL) {
		printf("{EMPTY}\n");
		return;
	}

	printf("{");

	e = list->head;
	while (e != NULL) {
		printf("%d", e->value);
		e = e->next;
		if (e!=NULL) {
			printf(", ");
		}
	}
	printf("}\n");
}

//
// Appends a new node with this value at the beginning of the list
//
void llist_add(LinkedList * list, int value) {
	// Create new node
	ListNode * n = (ListNode *) malloc(sizeof(ListNode));
	n->value = value;
	
	// Add at the beginning of the list
	n->next = list->head;
	list->head = n;
}

//
// Returns true if the value exists in the list.
//
int llist_exists(LinkedList * list, int value) {
	ListNode * n = list->head;
	while (n != NULL) {
		if (n->value == value) {
			return 1;
		}
		n = n->next;
	}
	return 0;
}

//
// It removes the entry with that value in the list.
//
int llist_remove(LinkedList * list, int value) {
	ListNode * n = list->head;
	int counter = 0;
	ListNode * n_1 = NULL;
	while (n!= NULL) {
		if (value == n->value) {
			if (counter == 0) {
				list->head = n->next;
			}
			else {
				n_1->next = n->next;
			}
			return 1;
		}
		n_1 = n;
		n = n->next;
		counter++;
	}
	return 0;
}

//
// It stores in *value the value that correspond to the ith entry.
// It returns 1 if success or 0 if there is no ith entry.
//
int llist_get_ith(LinkedList * list, int ith, int * value) {
	ListNode * n = list->head;
	for (int i = 0; i < ith; i++) {
		if (n->next == NULL) {
			return 0;
		}
		n = n->next;
	} 
	*value = n->value;
	return 1;
}

//
// It removes the ith entry from the list.
// It returns 1 if success or 0 if there is no ith entry.
//
int llist_remove_ith(LinkedList * list, int ith) {
	ListNode * n = list->head;
	ListNode * n_1 = NULL;
        for (int i = 0; i < ith; i++) {
                if (n->next == NULL) {
                        return 0;
                }
		n_1 = n;
                n = n->next;
        }
        n_1->next = n->next;
        return 1;
}

//
// It returns the number of elements in the list.
//
int llist_number_elements(LinkedList * list) {
	int number = 1;
	ListNode * n = list->head;
	while (n->next != NULL) {
		number++;
		n = n->next;
	}

	return number;
}


//
// It saves the list in a file called file_name. The format of the
// file is as follows:
//
// value1\n
// value2\n
// ...
//
int llist_save(LinkedList * list, char * file_name) {
	FILE * fd;
	fd = fopen(file_name, "w+");
	if (fd == NULL) {
		return 0;
	}
	ListNode * n = list->head;
	while (n->next != NULL) {
		fprintf(fd,"%d\n", n->value);
		n = n->next;
	}
	fprintf(fd,"%d\n",n->value);
	fclose(fd);
	return 0;
}

//
// It reads the list from the file_name indicated. If the list already has entries, 
// it will clear the entries.
//
int llist_read(LinkedList * list, char * file_name) {
	FILE * fd;
	fd = fopen(file_name, "r");
	char string[50];
	if(list->head != NULL) {
		llist_clear(list);
	}
	if (fd == NULL){
		return 0;
	}
	while (fgets(string,50,fd)) {
		llist_add(list,atoi(string));	
	}
	fclose(fd);
	return 1;
}


//
// It sorts the list. The parameter ascending determines if the
// order si ascending (1) or descending(0).
//
//
void swap_nodes(ListNode * n_1, ListNode * n_2) {
	int median;
	median = n_1->value;
	n_1->value = n_2->value;
	n_2->value = median;
}
void llist_sort(LinkedList * list, int ascending) {
    	int i, j,k,s;
	int n = 1;
	ListNode * n_1 = list->head; 
	while (n_1->next != NULL) {
		n++;
		n_1 = n_1 -> next;
	}
    	for (i = 0; i < n - 1; i++) {
        	for (j = 0; j < n - i - 1; j++) {
			n_1 = list->head;
			for (s = 0; s < j; s++) {
				n_1 = n_1->next;
			}
            		if (n_1->value < n_1->next->value && ascending == 0) {
                		swap_nodes(n_1, n_1->next);
			}
			if (n_1->value > n_1->next->value && ascending == 1) {
				swap_nodes(n_1, n_1->next);
			}
		}
	}
}

//
// It removes the first entry in the list and puts value in *value.
// It also frees memory allocated for the node
//
int llist_remove_first(LinkedList * list, int * value) {
	if (list->head != NULL) {
		ListNode * n = list->head;
		ListNode * n_1 = n->next;
		list->head = n_1;
		*value = n->value;
		free(n);
		return 1;
	}
	return 0;
}

//
// It removes the last entry in the list and puts value in *value/
// It also frees memory allocated for node.
//
int llist_remove_last(LinkedList * list, int *value) {
  if (list->head != NULL) {
  	ListNode * n = list->head;
	ListNode * n_1;
	while (n->next != NULL) {
		n_1 = n;
		n = n->next;
	}
	*value = n->value;
	free(n);
	n_1->next = NULL;
	return 1;
  }
  return 0;
}

//
// Insert a value at the beginning of the list.
// There is no check if the value exists. The entry is added
// at the beginning of the list.
//
void llist_insert_first(LinkedList * list, int value) {
	ListNode * n = list->head;
	ListNode * n_1 = malloc(sizeof(ListNode));
	n_1->value = value;
	n_1->next = n;
	list->head = n_1;
}

//
// Insert a value at the end of the list.
// There is no check if the name already exists. The entry is added
// at the end of the list.
//
void llist_insert_last(LinkedList * list, int value) {
	ListNode * n = list->head;
	ListNode * n_1 = malloc(sizeof(ListNode));
	n_1->value = value;
	while (n -> next != NULL) {
		n = n->next;
	}
	n->next = n_1;
	n_1->next = NULL;
}

//
// Clear all elements in the list and free the nodes
//
void llist_clear(LinkedList *list)
{	
	if (list -> head != NULL) {
		ListNode * n = list -> head;
		ListNode * n_1;
		while (n->next != NULL) {
			n_1 = n;
			n = n->next;
			free(n_1);
		}
		free(n);
		list->head = NULL;	
	}
}
