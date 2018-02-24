
#include <libkeys.a>
#include <studio.h>
// #include "mensaje.h"  ni puta idea de por que

#include <mqueue.h>
void main(void) {
  mqd_t server_queue; /* server message queue */
  mqd_t client_queue; /* client message queue */
  struct request req;
  int res;
  struct mq_attr attr;
  attr.mq_maxmsg = 1;
  attr.mq_msgsize = sizeof(int);
  client_queue = mq_open(“CLIENT_ONE”, O_CREAT|O_RDONLY, 0700, &attr);
  server_queue = mq_open(“ADD_SERVER”, O_WRONLY);
  /* fill in request */
  req.a = 5; req.b = 2; strcpy(req.q_name, “CLIENT_ONE”);
  mq_send(server_queue, &req, sizeof(struct request), 0);
  mq_receive(client_queue, &res, sizeof(int), 0);
  mq_close(server_queue);
  mq_close(client_queue);
  mq_unlink(“CLIENT_ONE”);
}
