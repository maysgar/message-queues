
#include <stdio.h>
#include <mqueue.h>
#include <string.h>
#include <stdlib.h>
#include "keys.h"

void main(void) {

  //Initialization of the system
  printf("Initializing  the system\n");
  init();

  //Insertion of an element
  printf("Inserting the triplet [5, "esketit", 5.0]\n");
  set_value(5, "esketit", 5.0);

  //Obtain the value associated to a key
  printf("Obtain the value associated to key "5"\n");
  get_value(5, "esketit", 5.0);

  //Modify the associated values to the given ky by the ones specied in the method
  printf("Look for key: '%d' and change its associated values by value1 = %d and value 2 = %f\n", req.key, req.value1, req.value2);
  modify_value(5, "esketit", 5.0);

  //Delete the elements with the given key
  printf("Delete the element who's key is: %d\n", key);
  delete(5);

  //Return the number of items stored on the server
  int items = num_items();
  printf("There are %d items stored in the server\n", items);


}
