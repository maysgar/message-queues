
#include <stdio.h>
#include <mqueue.h>
#include <string.h>
#include <stdlib.h>
#include "keys.h"

int main(void) {

  //Initialization of the system
  printf("Initializing  the system\n");
  float fnumber = 5.0;
  init();
  
  //Insertion of an element
  printf("Inserting the triplet [5, esketit, 5.0]\n");
  set_value(5, "esketit", fnumber);

  //Obtain the value associated to a key
  printf("Obtain the value associated to key -> 5\n");
  get_value(5, "esketit", &fnumber);

  //Modify the associated values to the given ky by the ones specied in the method
  printf("Look for key: '%d' and change its associated values by value1 = esketit and value2 = 5.0\n");
  modify_value(5, "esketit", &fnumber);

  //Delete the elements with the given key
  printf("Delete the element who's key is: 5\n");
  delete_key(5);

  //Return the number of items stored on the server
  int items = num_items();
  printf("There are %d items stored in the server\n", items);
  
  return 0;
}
