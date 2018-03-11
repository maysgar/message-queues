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

int init(){
	 if(head == NULL){
		 return 0;
	 }
	 struct Node* temp = head;
	 while(temp->next != NULL){
		 temp = temp->next;
		 temp = NULL;
	 }
	 return 0;
 }

 int set_value(int key, char *value1, float value2){
    printf("Server is executing set_value method inside\n");
	 struct Node* temp = head;
	 struct Node* newNode = GetNewNode(key, value1, &value2);
	 while(temp->next != NULL){
		 //the key already exists
		 if((newNode->data).key == (temp->data).key){
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
		if(key == (temp->data).key){
			value1 = (temp->data).value1;
			value2 = &(temp->data).value2;
			printf("value1: %s\n", value1);
			printf("value2: %f\n", *value2);
			return 0;
		}
		temp = temp->next;
	 }
	 //no element with that key found
	 return -1;
 }

 int modify_value(int key, char *value1, float *value2){
	 struct Node* temp = head;
	 //newNode??
	 while(temp->next != NULL){
		//element found!
		if(key == (temp->data).key){
			strcpy((temp->data).value1, value1);
			(temp->data).value2 = *value2;
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
		if(key == (temp->data).key){
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


void process_message(struct triplet *msg){
	struct triplet msg_local; /* local message */
	mqd_t client_queue; /* client queue */
	int result;
	/* thread copies message to local message*/
	pthread_mutex_lock(&mutex_msg);
	memcpy((char *) &msg_local, (char *)msg, sizeof(struct triplet));
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
		        printf("set_value is being executed\n");	
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

	/* open client queue */
	client_queue = mq_open("/CLIENT_ONE_PLUS_3T", O_WRONLY);
        printf("client queue: %d\n", (int)client_queue);
	/* if there is any error when opening the client queue*/
	if (client_queue == -1){
		perror("Can't open client queue");
		mq_close(client_queue);
		mq_unlink("/CLIENT_ONE_PLUS_3T");
		return;
  	}
	/* if everything goes well, return result to the client */
	else {
		printf("Server will now respond to the client ----->\n");
		mq_send(client_queue, (char *) &result, sizeof(int), 0);
		printf("The server sends the message back to the client\n");
		//close the queue
		mq_close(client_queue);
		mq_unlink("/CLIENT_ONE_PLUS_3T");
	}
	pthread_exit(0);
}



int main() {

	/*Driver code to test the implementation*/
	head = NULL; // empty list. set head as NULL.

    //creation of the server queue
	mqd_t server_queue;
	struct triplet msg; /* message to receive */
	struct mq_attr queue_attr; /* queue atributes */
	pthread_t thid;
	pthread_attr_t thread_attr; /* thread atributes */
	queue_attr.mq_msgsize = sizeof(struct triplet);

    queue_attr.mq_maxmsg = 10; //We set the maximum number of client requests to 10

  //Open server queue when initiating the system
  if((server_queue= mq_open("/SERVER_ONE_PLUS_3T", O_CREAT|O_RDONLY, 0700, &queue_attr)) == -1){
	//if there is an error opening the queue, we end the system by closing and unlinking the queue
    perror("error creating the server queue");
	mq_close(server_queue);
	mq_unlink("/SERVER_ONE_PLUS_3T");
	return -1;
	
  }
  printf("............... server queue created ...................\n");

	pthread_mutex_init(&mutex_msg, NULL);
	pthread_cond_init(&cond_msg, NULL);
	pthread_attr_init(&thread_attr);

	/* thread atributes */
	pthread_attr_setdetachstate(&thread_attr, PTHREAD_CREATE_DETACHED);

	// While the system is working, the server will always be awaiting for client requests
	while (1) {
		printf("Server will now recieve client's message ---->\n");
		/* receiving client's request message */
		mq_receive(server_queue, (char *) &msg, sizeof(struct triplet), 0); 
		printf("Server has received the request from the client\n");
		/* creating thread for the request and call process_message method to satisfy the request and answer back*/
		pthread_create(&thid, &thread_attr, (void *) *process_message, &msg);
		printf("Server creates a thread\n");

		/* wait for thread to copy message */ //critical section
		pthread_mutex_lock(&mutex_msg);
		/* while (msg_not_copied) */
		pthread_cond_wait(&cond_msg, &mutex_msg);
		msg_not_copied = 1;
		pthread_mutex_unlock(&mutex_msg);
	}

}