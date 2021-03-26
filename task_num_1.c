//
// Created by omri_gil on 26/03/2021.
// I assumed that the length of an address to the memory is 8b (log2(10^6)/8 ~ 20 (19.9) = length -> 8b
// list_address is a list, when list_address[i] is the i block memory unit, if the memory is continuous,
// The first for loop I will replace with :1.i= first address 2.the value in the i  = the address of the i+8  3.i=i+8;
// in my solution I created a link-list in efficient way.
//

#include <stdio.h>
#include <stdlib.h>
#define N  124999  //((pow(10,6))/8)-1)
double* list_head_ptr; // double is 8b and is size equal to the address memory size.
void* myMalloc();
void myFree(void* ptr);

int main(){ //init
    int i;
    double* list_address[N];  // list of address 1MB
    list_head_ptr=list_address[0]; // the first address
    for( i=0;i<(N-1);++i){
       *list_address[i] = list_address[i+1]; // update the value of the first  memory block to the address of the next one (the address is 8b)
    }
    return 0;
}
void* myMalloc(){
    void* ptr = (void*)(list_head_ptr);  //casting the pointer to void*
    list_head_ptr= (double*)(*list_head_ptr); // update the value of head pointer to the value of block(address of the next block)
    return  ptr;
}
void myFree(void* ptr){
    *((double*)ptr)=list_head_ptr; // casting ptr to double and update is value to the head pointer
    list_head_ptr=(double*)ptr; // update the head
}