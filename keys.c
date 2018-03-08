#include <stdio.h>
#include <mqueue.h>
#include "keys.h"


int send(int number, int key, char *value1, float value2){

  mqd_t server_queue; /* server message queue */
  mqd_t client_queue; /* client message queue */
  struct tripplet req;
  int res;
  struct mq_attr attr;
  
  attr.mq_maxmsg = 1;
  attr.mq_msgsize = sizeof(int);
  client_queue = mq_open("/CLIENT_ONE", O_CREAT|O_RDONLY, 0700, &attr);
  server_queue = mq_open("/SERVER", O_WRONLY);

  req.key = key;
  req.value1 = &value1;
  req.value2 = value2;  //OJO CUIDADO
  strcpy(req.client_queue_name, "/CLIENT_ONE");
  req.method_id = number;


  mq_send(server_queue, &req, sizeof(struct triplet), 0);
  mq_receive(client_queue, &res, sizeof(int), 0);
  mq_close(server_queue);
  mq_close(client_queue);
  mq_unlink(“/CLIENT_ONE”);
}

int init(){
  send(1, "nothing", 0.0);
}

int set_value(int key, char *value1, float value2){
 send(2, key, &value1, value2); //CUIDADO CON EL FLOAT 
}

int get_value(int key, char *value1, float *value2){
  send(3, key, &value1, &value2);
}

int modify_value(int key, char *value1, float *value2){
  send(4, key, &value1, &value2);
}

int delete_key(int key){
  send(5, "nothing", 0.0);
}

int num_items(){
  send(6, "nothing", 0.0);
}

