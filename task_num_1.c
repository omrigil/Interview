//
// Created by omri_gil on 26/03/2021.
// I assumed that the length of an address in the memory is 8 byte (my calculation was: log2(10^6)/8 ~ 20 (19.9) => 8 bytes will suffice)
// list_address is a list, when list_address[i] is the ith block memory unit.
//
//

#include <stdio.h>
#include <stdlib.h>
#define N  124999  //((pow(10,6))/8)-1)
double* list_head_ptr; // double is 8 bytes and its size is equal to the address memory size.
void* myMalloc();
void myFree(void* ptr);

int main(){ //init
    int i;
    double* list_address[N];  // list of address 1MB
    list_head_ptr=list_address[0]; // the first address
    for( i=0;i<(N-1);++i){
       *list_address[i] = list_address[i+1]; // update the value of the first memory block to the address of the next one (the address is 8 bytes)
    }
    return 0;
}
void* myMalloc(){
    void* ptr = (void*)(list_head_ptr);  //casting the pointer to void*
    list_head_ptr= (double*)(*list_head_ptr); // update the value of the head pointer to the value of the memory block (address of the next block)
    return  ptr;
}
void myFree(void* ptr){
    *((double*)ptr)=list_head_ptr; // casting ptr to double and updating its value to the head pointer
    list_head_ptr=(double*)ptr; // update the head
}
