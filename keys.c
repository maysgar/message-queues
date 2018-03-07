#include <studio.h>
#include "keys.h"



int init(){
  //initialize the system
  if(destroy() == -1){
    //failure
    return -1;
  }
  //success
  return 0;
}

int set_value(int key, char *value1, float value2){
  if(insert(key, value1, value2) == -1){
    //insert existing key

    //failure
    return -1;
  }
  //inserted successfully
  return 0;
}

int get_value(int key, char *value1, float *value2){
  // if(){
  //   //failure
  //   return -1;
  // }
  // value1 = ;
  // value2 = ;
  // return 0;
}

int modify_value(int key, char *value1, float *value2){
//   if(){
//     //failure
//     return -1;
//   }
//   //success
//   return 0;
// }

int delete_key(int key){
  //   if(){
  //     //failure
  //     return -1;
  //   }
  //   //success
  //   return 0;
  // }
}

int num_items(){
  // return n_elements;
  // //error
  // return -1;
}