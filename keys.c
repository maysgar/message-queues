#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <string.h>
#include "keys.h"


int send(int number, int key, char *value1, float value2){

  mqd_t server_queue; /* server message queue */
  mqd_t client_queue; /* client message queue */
  struct triplet req;
  int res;
  struct mq_attr attr;
  
  attr.mq_maxmsg = 1;
  attr.mq_msgsize = sizeof(int);
  client_queue = mq_open("/CLIENT_ONE_PLUS_3T", O_CREAT|O_RDONLY, 0700, &attr);
  server_queue = mq_open("/SERVER_ONE_PLUS_3T", O_WRONLY);

  req.key = key;
  strcpy(req.value1, value1);
  req.value2 = value2;  //OJO CUIDADO
  strcpy(req.client_queue_name, "/CLIENT_ONE_PLUS_3T");
  req.method_id = number;


  mq_send(server_queue, (const char *) &req, sizeof(struct triplet), 0);
  printf("Sending SKEEEEETIT\n");
  mq_receive(client_queue, (char *) &res, sizeof(int), 0);
  printf("Client recevies: %d\n", res); //test what client receives
  mq_close(server_queue);
  mq_unlink("/SERVER_ONE_PLUS_3T");
  mq_close(client_queue);
  mq_unlink("/CLIENT_ONE_PLUS_3T");
  
  return res;
}

int init(){
  return send(1, 0, "nothing", 0.0);
}

int set_value(int key, char *value1, float value2){
 printf("key: %d , value1: %s , value2: %f\n", key, value1, value2);
 return send(2, key, value1, value2); 
}

int get_value(int key, char *value1, float *value2){
  return send(3, key, value1, *value2);
}

int modify_value(int key, char *value1, float *value2){
  return send(4, key, value1, *value2);
}

int delete_key(int key){
  return send(5, 0, "nothing", 0.0);
}

int num_items(){
  return send(6, 0, "nothing", 0.0);
}
