
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> /* For threads */
#include <fcntl.h> /* flags */
#include <sys/stat.h> /* modes */
#include <mqueue.h>
#include "doubleLinkedList.c"
#define MAX_BUFFER 1024 /* buffer size */

/* mutex and condition variables for the message copy */
pthread_mutex_t mutex_msg;
int msg_not_copied = TRUE; /* TRUE = 1 */
pthread_cond_t cond_msg;

int main() {

	/Driver code to test the implementation/
	head = NULL; // empty list. set head as NULL.

  //creation of the queue
	mqd_t server_queue;
	struct triplet msg; /* message to receive */
	struct mq_attr queue_attr; /* queue atributes */
	pthread_attr_t thread_attr; /* thread atributes */
	queue_attr.mq_msgsize = sizeof(struct triplet));
    queue_attr.mq_maxmsg = MAX_BUFFER;

  if(server_queue= mq_open("/SERVER", O_CREAT|O_RDONLY, 0700, &queue_attr)) == -1){
    perror("error creating the queue");
    return -1;
  }

	pthread_mutex_init(&mutex_msg, NULL);
	pthread_cond_init(&cond_msg, NULL);
	pthread_attr_init(&queue_attr);

	/* thread atributes */
	pthread_attr_setdetachstate(&thread_attr, PTHREAD_CREATE_DETACHED);

	while (TRUE) {
		mq_receive(server_queue, &msg, sizeof(struct triplet), 0);
		pthread_create(&thid, &queue_attr, process_message, &msg);

		/* wait for thread to copy message */ //critical section
		pthread_mutex_lock(&mutex_msg);
		while (message_not_copied)
		pthread_cond_wait(&cond_msg, &mutex_msg);
		message_not_copied = TRUE;
		pthread_mutex_unlock(&mutex_msg);
	}

  //close the queue
  int mq_close(mqd);

  // delete the queue
  int mq_unlink(server_queue);

  //creation of threads
  int pthread_create(pthread_t* thread, const pthread_attr_t* attr, void * (*function)(void *), void * arg);

  //getting the thread id
  pthread_t pthread_self(void);

  //finalize thread execution
  int pthread_exit(void *value);

  //join thread
  int pthread_join(pthread_ thid, void **value);

}

void process_message(struct mensaje *msg){
	struct triplet msg_local; /* local message */
	struct mqd_t client_queue; /* client queue */
	int result;
	/* thread copies message to local message*/
	pthread_mutex_lock(&mutex_msg);
	memcpy((char *) &msg_local, (char *)&msg, sizeof(struct triplet));
	/* wake up server */
	message_not_copied = FALSE; /* FALSE = 0 */
	pthread_cond_signal(&cond_msg);
	pthread_mutex_unlock(&mutex_msg);

	/* execute client request and prepare reply */
	switch(msg_local){  
    	case 1 :  
			result = init(); 
			break;  
    	case 2 :  
			result = set_value(msg_local.key, &msg_local.value1, msg_local.value2); 
			break;  
    	case 3 :  
			result = get_value(msg_local.key, &msg_local.value1, msg_local.value2); 
			break;  
		case 4 :
			result = modify_value(msg_local.key, &msg_local.value1, &msg_local.value2);
			break;
		case 5 :
			result = delete_key(msg_local.key);
			break;
		case 6 :
			result = num_items();
			break;
	}
    


	/* return result to client by sending it to queue */
	client_queue = mq_open(msg_local.client_queue_name, O_WRONLY);
	if (client_queue == -1){
		perror("Can't open client queue");
  	}
	else {
		mq_send(client_queue, (char *) &result, sizeof(int), 0);
		mq_close(client_queue);
	}
	pthread_exit(0);
}

 int init(){
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
