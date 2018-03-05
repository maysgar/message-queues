
#include <libkeys.a>
#include <studio.h>
// #include "mensaje.h"  ni puta idea de por que
#include <mqueue.h>
#include "keys.h"

void main(void) {
  mqd_t server_queue; /* server message queue */
  mqd_t client_queue; /* client message queue */
  struct request req;
  //struct tripplet req;
  int res;
  struct mq_attr attr;
  attr.mq_maxmsg = 1;
  attr.mq_msgsize = sizeof(int);
  client_queue = mq_open(“/CLIENT_ONE”, O_CREAT|O_RDONLY, 0700, &attr);
  server_queue = mq_open(“/SERVER”, O_WRONLY);
  /* fill in request */
  //req.key = 5;
  //req.value1 = "esketit\0";
  //req.value2 = 5.0;

  req.a = 5; 
  req.b = 2; 
  strcpy(req.client_queue_name, “/CLIENT_ONE”);

  //Initialization of the system
  printf("Initializing  the system\n");
  init();

  //Insertion of an element
  printf("Inserting the triplet [5, "esketit", 5.0]\n");
  set_value(req.key, &req.value1, req.value2);

  //Obtain the value associated to a key
  printf("Obtain the value associated to key "5"\n");
  get_value(req.key, &req.value1, &req.value2);

  //Modify the associated values to the given ky by the ones specied in the method
  printf("Loook for key: '%d' and change its associated values by value1 = %d and value 2 = %f\n", req.key, req.value1, req.value2);
  modify_value(req.key, &req.value1, &req.value2);

  //Delete the elements with the given key
  printf("Delete the element who's key is: %d\n", key);
  delete(req.key);

  //Return the number of items stored on the server
  int items = num_items();
  printf("There are %d items stored in the server\n", items);

  //mq_send(server_queue, &req, sizeof(struct triplet), 0);
  mq_send(server_queue, &req, sizeof(struct request), 0);
  mq_receive(client_queue, &res, sizeof(int), 0);
  mq_close(server_queue);
  mq_close(client_queue);
  mq_unlink(“/CLIENT_ONE”);
}