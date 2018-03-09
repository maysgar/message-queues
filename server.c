
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> /* For threads */
#include <fcntl.h> /* flags */
#include <sys/stat.h> /* modes */
#include <mqueue.h>
#include <string.h>
#include "doubleLinkedList.c"
#define MAX_BUFFER 1024 /* buffer size */

/* mutex and condition variables for the message copy */
pthread_mutex_t mutex_msg;
int msg_not_copied = 1; /* TRUE = 1 */
pthread_cond_t cond_msg;


struct triplet init(){
	struct triplet auxTriplet{
		int key = 0;
 		char value1[255] = "nothing";
 		float value2 = 5.0;
 		char client_queue_name [MAXSIZE] = "nothing";
 		int method_id = -1;
	};

	 if(head == NULL){
		 return auxTriplet; //error
	 }
	 struct Node* temp = head;
	 while(temp->next != NULL){
		 temp = temp->next;
		 temp = NULL;
	 }
	 auxTriplet.method_id = 0; //success
	 return auxTriplet;
 }

struct triplet set_value(int key, char *value1, float value2){
     struct Node* temp = head;
	 struct Node* newNode = GetNewNode(key, value1, &value2);
	 while(temp->next != NULL){
		 //the key already exists
		 if((newNode->data).key == (temp->data).key){
			(temp->data).method_id = -1; //return -1
			return (temp->data);
		 }
		 temp = temp->next;
		 temp->next = newNode;
	     newNode->prev = temp;
	 }
	 //succesful insertion
	 (newNode->data).method_id = 0; //return 0
	 return (newNode->data);
 }

 struct triplet get_value(int key, char *value1, float *value2){
	struct Node* temp = head;
	 while(temp->next != NULL){
		//element found!
		if(key == (temp->data).key){
			value1 = (temp->data).value1;
			value2 = &(temp->data).value2;
			(temp->data).method_id = 0; //return 0 
			printf("value1: %s\n", value1);
			printf("value2: %f\n", *value2);
			return (temp->data);
		}
		temp = temp->next;
	 }
	 //no element with that key found
	 (temp->data).method_id = -1; //return -1
	 return (temp->data);
 }

struct triplet modify_value(int key, char *value1, float *value2){
	 struct Node* temp = head;
	 //newNode??
	 while(temp->next != NULL){
		//element found!
		if(key == (temp->data).key){
			strcpy((temp->data).value1, value1);
			(temp->data).value2 = *value2;
			(temp->data).method_id = 0; //return 0 
			return (temp->data);
		}
		temp = temp->next;
	 }
	 //no element with that key found
	 (temp->data).method_id = -1; //return -1
	 return (temp->data);
 }

struct triplet delete_key(int key){
	struct Node* temp = head;
	while(temp->next != NULL){
		//element found!
		if(key == (temp->data).key){
			struct triplet aux = (temp->data);
			aux.method_id = 0; //return 0 
			temp = NULL;
			return aux;
		}
		temp = temp->next;
	 }
	 //key does not exist
	 (temp->data).method_id = -1; //return -1
	 return (temp->data);
 }

struct triplet num_items(){
	 int items = 0;
	 struct Node* temp = head;
	 while(temp->next != NULL){
		 temp = temp->next;
		 items++;
	 }
	 (temp->data).method_id = items;
	 return (temp->data);
	 //return -1 donde??
 }


void process_message(struct triplet *msg){
	struct triplet msg_local; /* local message */
	mqd_t client_queue; /* client queue */
	int result;
	/* thread copies message to local message*/
	pthread_mutex_lock(&mutex_msg);
	memcpy((char *) &msg_local, (char *)&msg, sizeof(struct triplet));
	/* wake up server */
	msg_not_copied = 0; /* FALSE = 0 */
	pthread_cond_signal(&cond_msg);
	pthread_mutex_unlock(&mutex_msg);

	/* execute client request and prepare reply */
	switch(msg_local.method_id){  
    	case 1 :  
			result = init(); 
			break;  
    	case 2 :  
			result = set_value(msg_local.key, msg_local.value1, msg_local.value2); 
			break;  
    	case 3 :  
			result = get_value(msg_local.key, msg_local.value1, &msg_local.value2);
			printf("value1: %s\n", msg_local.value1);
			printf("value2: %f\n", msg_local.value2);
			break;  
		case 4 :
			result = modify_value(msg_local.key, msg_local.value1, &msg_local.value2);
			break;
		case 5 :
			result = delete_key(msg_local.key);
			break;
		case 6 :
			result = num_items();
			break;
	}
    
	char *resultString;
	sprintf(resultString, "%d", result);


	/* return result to client by sending it to queue */
	client_queue = mq_open(msg_local.client_queue_name, O_WRONLY);
	if (client_queue == -1){
		perror("Can't open client queue");
  	}
	else {
		mq_send(client_queue, (char *) &resultString, sizeof(int), 0);
		//close the queue
		mq_close(client_queue);
	}
	pthread_exit(0);
}



int main() {

	/*Driver code to test the implementation*/
	head = NULL; // empty list. set head as NULL.

    //creation of the queue
	mqd_t server_queue;
	struct triplet msg; /* message to receive */
	struct mq_attr queue_attr; /* queue atributes */
	pthread_t thid;
	pthread_attr_t thread_attr; /* thread atributes */
	queue_attr.mq_msgsize = sizeof(struct triplet);
    queue_attr.mq_maxmsg = MAX_BUFFER;

  if((server_queue= mq_open("/SERVER", O_CREAT|O_RDONLY, 0700, &queue_attr)) == -1){
    perror("error creating the queue");
    return -1;
  }

	pthread_mutex_init(&mutex_msg, NULL);
	pthread_cond_init(&cond_msg, NULL);
	pthread_attr_init(&thread_attr);

	/* thread atributes */
	pthread_attr_setdetachstate(&thread_attr, PTHREAD_CREATE_DETACHED);

	while (1) {
		mq_receive(server_queue, (char *) &msg, sizeof(struct triplet), 0);
		pthread_create(&thid, &thread_attr, (void *) *process_message, &msg);

		/* wait for thread to copy message */ //critical section
		pthread_mutex_lock(&mutex_msg);
		while (msg_not_copied)
		pthread_cond_wait(&cond_msg, &mutex_msg);
		msg_not_copied = 1;
		pthread_mutex_unlock(&mutex_msg);
	}

}

