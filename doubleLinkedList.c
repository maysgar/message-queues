/* Doubly Linked List implementation */
#include<stdio.h>
#include<stdlib.h>
#include "keys.h"

struct Node  {
	struct triplet data;
	struct Node* next;
	struct Node* prev;
};

struct Node* head; // global variable - pointer to head node.

//Creates a new Node and returns pointer to it.
struct Node* GetNewNode(int key, char *value1, float *value2){
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	(newNode->data)->key = key;
	(newNode->data)->value1 = &value1;
	(newNode->data)->value2 = &value2;
	newNode->prev = NULL;
	newNode->next = NULL;
	return newNode;
}

//Inserts a Node at head of doubly linked list
void InsertAtHead(int key, char *value1, float *value2) {
	struct Node* newNode = GetNewNode(int key, char *value1, float *value2);
	if(head == NULL) {
		head = newNode;
		return;
	}
	head->prev = newNode;
	newNode->next = head;
	head = newNode;
}

//Inserts a Node at tail of Doubly linked list
void InsertAtTail(int key, char *value1, float *value2) {
	struct Node* temp = head;
	struct Node* newNode = GetNewNode(int key, char *value1, float *value2);
	if(head == NULL) {
		head = newNode;
		return;
	}
	while(temp->next != NULL) temp = temp->next; // Go To last Node
	temp->next = newNode;
	newNode->prev = temp;
}

//Prints all the elements in linked list in forward traversal order
void Print() {
	struct Node* temp = head;
	printf("Forward: ");
	while(temp != NULL) {
		printf("%d ",(temp->data)->key);
		temp = temp->next;
	}
	printf("\n");
}

//Prints all elements in linked list in reverse traversal order.
void ReversePrint() {
	struct Node* temp = head;
	if(temp == NULL) return; // empty list, exit
	// Going to last Node
	while(temp->next != NULL) {
		temp = temp->next;
	}
	// Traversing backward using prev pointer
	printf("Reverse: ");
	while(temp != NULL) {
		printf("%d ",(temp->data)->key));
		temp = temp->prev;
	}
	printf("\n");
}


/*int main() {

	//Driver code to test the implementation
	head = NULL; // empty list. set head as NULL.

	// Calling an Insert and printing list both in forward as well as reverse direction.
	InsertAtTail(2); Print(); ReversePrint();
	InsertAtTail(4); Print(); ReversePrint();
	InsertAtHead(6); Print(); ReversePrint();
	InsertAtTail(8); Print(); ReversePrint();
*/
}
