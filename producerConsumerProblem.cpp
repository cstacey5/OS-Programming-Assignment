// Connor Stacey
// Operating Systems
// Program to demonstrate the Producer-Consumer problem with semaphores and pthreads.
// Due 04/18/2021

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

//GLOBAL VARIABLE DECLARATIONS
//
////////////////////////////////////
const int ITEMS_MAX = 2; //max items to be produced at a time
const int BUFFER_MAX = 2;

sem_t emptySemaphore;
sem_t fullSemaphore;
int buffer[BUFFER_MAX];
int bufferInNum = 0;
int bufferOutNum = 0;
pthread_mutex_t mutexP;
/////////////////////////////////////

// producer function
//
/////////////////////////////////////
void* producer(void* producerNumber){
  int newItem;
  for(int i = 0; i < ITEMS_MAX; ++i){
    newItem = rand() % 20; //create random item to place on the table (0-19 to keep it readable)
    sem_wait(&emptySemaphore); // unlock the empty semaphore (allows producer to run)
    pthread_mutex_lock(&mutexP); //lock the thread
    buffer[bufferInNum] = newItem; //add the random item into the buffer
    printf("Producer %d placed item %d on the table at location %d. \n", *((int*)producerNumber), newItem, bufferInNum);
    bufferInNum = (bufferInNum + 1) % BUFFER_MAX; //get next buffer num
    pthread_mutex_unlock(&mutexP); //unlock the thread
    sem_post(&fullSemaphore); //lock the full semaphore (allows consumer to run)
  }
  
  return nullptr;
}
/////////////////////////////////////////

// consumer function
//
/////////////////////////////////////////
void* consumer(void* consumerNumber){
  int removedItem;
  for(int i = 0; i < ITEMS_MAX; ++i){
    removedItem = buffer[bufferOutNum]; //get the removed item
    sem_wait(&fullSemaphore); //unlock the full semaphore (allows consumer to run)
    pthread_mutex_lock(&mutexP); //lock the thread
    printf("Consumer %d removed item %d from the table at location %d. \n", *((int *)consumerNumber), removedItem, bufferOutNum);
    bufferOutNum = (bufferOutNum + 1) % BUFFER_MAX; //get next buffer num
    pthread_mutex_unlock(&mutexP); //unlock the thread
    sem_post(&emptySemaphore); //lock the empty semaphore (allows producer to run)
  }
  
  return nullptr;
}
///////////////////////////////////////////

// main function
//
///////////////////////////////////////////

int main(){

//initialization
  pthread_t producerP[5];
  pthread_t consumerP[5];
  pthread_mutex_init(&mutexP, nullptr);
  
  sem_init(&emptySemaphore, 0, BUFFER_MAX);
  sem_init(&fullSemaphore, 0, 0);
  
  //array for numbering producer/consumers
  int numArray[5] = {1,2,3,4,5};
  
  printf("Testing Producer/Consumer Problem with 5 producers/5 consumers.\n");
  printf("Location = Location in the Buffer.\n\n");
  
  //putting threads in action
  for(int i = 0; i < 5; ++i){
    pthread_create(&producerP[i], nullptr, producer, &numArray[i]);
  }
  for(int i = 0; i < 5; ++i){
    pthread_create(&consumerP[i], nullptr, consumer, &numArray[i]);
  }
  //stopping threads
  for(int i = 0; i < 5; ++i){
    pthread_join(producerP[i], nullptr);
  }
  for(int i = 0; i < 5; ++i){
    pthread_join(consumerP[i], nullptr);
  }
  
  //destruction
  pthread_mutex_destroy(&mutexP);
  sem_destroy(&emptySemaphore);
  sem_destroy(&fullSemaphore);
  
  return 0;
}
//////////////////////////////////////////////
