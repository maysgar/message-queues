#include <stdio.h>
#include <mqueue.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "keys.h"

int main(void) {

  float fnumber = 5.0;
  int value1 = 3;

  //Initialization of the system
  /* printf("Initializing  the system\n"); */
  int in = init();
  /* printf("Result of the init method: %d\n", in); */
  
  sleep(1);
  //Insertion of an element
  /* printf("Inserting the triplet [5, &value1, 5.0]\n"); */
  set_value(5, (char *) &value1, fnumber);

  //Obtain the value associated to a key
  /* printf("Obtain the value associated to key -> 5\n"); */
  get_value(5, (char *) &value1, &fnumber);


  //Modify the associated values to the given ky by the ones specied in the method
  /* printf("Look for key: 5 and change its associated values by value1 and value2 = 5.0\n"); */
  modify_value(5, (char *) &value1, &fnumber);

  //Delete the elements with the given key
  /* printf("Delete the element who's key is: 5\n"); */
  delete_key(5);

  //Return the number of items stored on the server
  int items = num_items();
  /* printf("There are %d items stored in the server\n", items); */
  
  return 0;
}