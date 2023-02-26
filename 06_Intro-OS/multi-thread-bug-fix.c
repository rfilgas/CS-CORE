/*
 * CS 532: bug4.c - another buggy pthreads program. 
 * this program hangs (sometimes), your job is to produce a bug4_fixed.c 
 * program that works correctly always.
 * compile: gcc -o bug4 bug4.c -Wall -Werror -lpthread
 * example run (desired):

$ ./bug4 5000000
WORKER2: 1000000
WORKER1: 2000000
WORKER1: 3000000
WORKER1: 4000000
WORKER1: 5000000
WORKER2: 6000000
WORKER1: 7000000
WORKER2: 8000000
WORKER1: 9000000
WORKER1: 10000000
FINISHED:  counter == 10000000

 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

volatile unsigned long counter = 0;  
unsigned long numloops;

pthread_mutex_t mutexA = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutexB = PTHREAD_MUTEX_INITIALIZER;

// this is a 
void *dowork1(void *param) 
{

  for (int i = 0; i < numloops; i++) {
    pthread_mutex_lock(&mutexA);
    pthread_mutex_lock(&mutexB);
    counter++;
    if ((counter % 1000000) == 0) {
      printf("WORKER1: %ld\n", counter);
    }
    pthread_mutex_unlock(&mutexB);
    pthread_mutex_unlock(&mutexA);
  }

  return NULL;
}

void *dowork2(void *param) 
{

  for (int i = 0; i < numloops; i++) {
    pthread_mutex_lock(&mutexA);
    pthread_mutex_lock(&mutexB);
    counter++;
    if ((counter % 1000000) == 0) {
      printf("WORKER2: %ld\n", counter);
    }
    pthread_mutex_unlock(&mutexB);
    pthread_mutex_unlock(&mutexA);
  }

  return NULL;
}


int main(int argc, char **argv) {
  if (argc != 2) { 
    fprintf(stderr, "USAGE: %s <size>\n", argv[0]);
    exit(-1); 
  }

  numloops = atol( argv[1] );

  /* create worker threads */
  pthread_t w1, w2;
  pthread_create(&w1, NULL, dowork1, NULL);
  pthread_create(&w2, NULL, dowork2, NULL);

  /* wait for threads to complete */
  pthread_join(w1, NULL);
  pthread_join(w2, NULL);

  printf("FINISHED:  counter == %ld\n", counter);

  return 0;
}
