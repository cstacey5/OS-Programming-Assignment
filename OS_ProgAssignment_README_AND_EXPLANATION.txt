Connor Stacey
Operating Systems
Programming Assignment
04/18/2021

READ ME
//////////////////////////////////////////

This program compiles by the command:

gcc -pthread producerConsumerProblem.cpp
./a.out

//////////////////////////////////////////

Explanation of code: (I also commented the code up)

Producer:

For the producer, i needed to create a random item to be placed on to the table first. 
After that, i called sem_wait(&emptySemaphore) to unlock the semaphore that keeps track of if there is an empty space on the table for the producer to place an item.
Since the thread is now in use i needed to call pthread_mutex_lock(&mutexP) to lock the thread.
Then i place the item on the table by storing it in the buffer array.
After this i called printf() to print the execution.
Then i set the new bufferInNum for the next item to be placed.
After the item is placed on the table i can unlock the thread by using pthread_mutex_unlock(&mutexP).
Then i can call sem_post(&fullSemaphore) to lock the semaphore that keeps track of if the table is full, this allows the consumer to remove an item.

Consumer:

For the consumer, i needed to get the item being removed from the table first.
After that, i called sem_wait(&fullSemaphore) to unlock the semaphore that keeps track of if there are items on the table to remove.
Since the thread is now in use i needed to call pthread_mutex_lock(&mutexP) to lock the thread.
After this i called printf() to print the execution.
Then i set the new bufferOutNum for the next item to be removed.
After the item is removed from the table i can unlock the thread by using pthread_mutex_unlock(&mutexP).
Then i can call sem_post(&emptySemaphore) to lock the semaphore that keeps track of empty space on the table, this allows the producer to add another item.

Main:

In the main function i started by creating 5 producers and 5 consumers (could have been any amount just used 5 bc simple) and initialized the semaphores and the mutex pthread.
I created an array that keeps track of the number of the producer/consumer. i.e. consumerP[2] is talking about the consumer at numArray[2] which is consumer 3.
After the producers and consumers were created i used for loops to call pthread_create() on each of the producers/consumers.
This is where my producer/consumer functions get called into place (in the 3rd parameter of pthread_create().
After these threads are being put to use, they also need to be stopped before termination of the program.
To do this i used forloops to call pthread_join() on each of the producers/consumers.
Then to end the program i just needed to destroy the mutex pthread and both semaphores.

