/* Doubly Linked List implementation */
#include<stdio.h>
#include<stdlib.h>

struct Node  {
	int data;
	struct Node* next;
	struct Node* prev;
};

struct Node* head; // global variable - pointer to head node.

//Creates a new Node and returns pointer to it.
struct Node* GetNewNode(int x) {
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	newNode->data = x;
	newNode->prev = NULL;
	newNode->next = NULL;
	return newNode;
}

//Inserts a Node at head of doubly linked list
void InsertAtHead(int x) {
	struct Node* newNode = GetNewNode(x);
	if(head == NULL) {
		head = newNode;
		return;
	}
	head->prev = newNode;
	newNode->next = head;
	head = newNode;
}

//Inserts a Node at tail of Doubly linked list
void InsertAtTail(int x) {
	struct Node* temp = head;
	struct Node* newNode = GetNewNode(x);
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
		printf("%d ",temp->data);
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
		printf("%d ",temp->data);
		temp = temp->prev;
	}
	printf("\n");
}

 int destroy(){
	 if(head == NULL){
		 return -1;
	 }
	 struct Node* temp = head;
	 while(temp->next != NULL){
		 temp = temp->next;
		 temp = NULL;
	 }
	 return 0;
 }

 int set_value(int key, char *value1, float value2){
     struct Node* temp = head;
	 struct Node* newNode = GetNewNode(x);
	 while(temp->next != NULL){
		 //the key already exists
		 if(newNode.key == temp.key){
			 return -1;
		 }
		 temp = temp->next;
		 temp->next = newNode;
	     newNode->prev = temp;
	 }
	 //succesful insertion
	 return 0;
 }

 int get_value(int key, char *value1, float *value2){
	struct Node* temp = head;
	 while(temp->next != NULL){
		//element found!
		if(key == temp.key){
			&value1 = temp.value1;
			&value2 = temp.value2;
			return 0;
		}
		temp = temp->next;
	 }
	 //no element with that key found
	 return -1;
 }

 int modify_value(int key, char *value1, float *value2){
	 struct Node* temp = head;
	 while(temp->next != NULL){
		//element found!
		if(key == temp.key){
			temp.value1 = &value1;
			temp.value2 = &value2;
			return 0;
		}
		temp = temp->next;
	 }
	 //no element with that key found
	 return -1;
 }

 int delete_key(int key){
	struct Node* temp = head;
	while(temp->next != NULL){
		//element found!
		if(key == temp.key){
			temp = NULL;
			return 0;
		}
		temp = temp->next;
	 }
	 //key does not exist
	 return -1; 
 }

 int num_items(){
	 int items = 0;
	 struct Node* temp = head;
	 while(temp->next != NULL){
		 temp = temp->next;
		 items++;
	 }
	 return items;
	 //return -1 donde??
 }


int main() {

	/*Driver code to test the implementation*/
	head = NULL; // empty list. set head as NULL.

	// Calling an Insert and printing list both in forward as well as reverse direction.
	InsertAtTail(2); Print(); ReversePrint();
	InsertAtTail(4); Print(); ReversePrint();
	InsertAtHead(6); Print(); ReversePrint();
	InsertAtTail(8); Print(); ReversePrint();

}
