/*
 *Ryan Filgas
 *Bruce Irvin
 *CS532 Lab
 *
 *
 *
 * CS 532: helloT.c
 * print Hello World from a thread
 * and calculate the factorial of the input thread ID
 * demonstrates how to create a thread and join with it *
 */

/*
 * Assignment: 
 * 1. read the code and understand it. use "man pthread" to get a listing 
 *    of supported pthread functionality, and use "man <pthread func name>" to
 *    get details of individual pthread functions.
 * 2. build the code as is and run it
 *    use something like "gcc -Wall -Werror helloT.c -lpthread -o helloT" to build
 *    then run with "./helloT <numthreads>" where <numthreads> is an integer between
 *    1 and MAXTHREADS
 *    Note that the program only creates one thread at first.
 *    The output should look like this at first:

 $ ./helloT 20
 User requested 20 threads
 Thread 0 result is 1

 * 3. Update the code to create <numthreads> threads with each thread 
 *    computing factorial and outputting accordingly. Output should resemble this:

 $ ./helloT 20
 User requested 20 threads
 Thread 4 result is 24
 Thread 1 result is 1
 Thread 3 result is 6
 Thread 2 result is 2
 Thread 5 result is 120
 Thread 6 result is 720
 Thread 8 result is 40320
 Thread 7 result is 5040
 Thread 9 result is 362880
 Thread 10 result is 3628800
 Thread 11 result is 39916800
 Thread 12 result is 479001600
 Thread 13 result is 6227020800
 Thread 14 result is 87178291200
 Thread 16 result is 20922789888000
 Thread 17 result is 355687428096000
 Thread 15 result is 1307674368000
 Thread 18 result is 6402373705728000
 Thread 20 result is 2432902008176640000
 Thread 19 result is 121645100408832000


Note: it is NOT necessary for the threads to output in order as shown above. Any order is OK
as long as each factorial is computed correctly. 
Note: the program should run a little longer than SLEEPTIME, if it runs farlonger then you have a problem.
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAXTHREADS 50
#define SLEEPTIME 5

// This method takes the tid and prints out the factorial of the tid.
void *Factorial(void *tidptr)
{

    /* leave this sleep in place, it will help with debugging by varying the orders of the threads */
    sleep(SLEEPTIME);

    // dereference the result of casting tidptr to an int ptr. This should translate the PID passed in back to an int.
    int tid = * ((int*) tidptr);
    if (tid > 20) {
        fprintf(stderr, "ERROR: thread %d exit to avoid long long overflow\n", tid);
        return NULL;
    }

    unsigned long long factorial = 1;
    for (int j = 1; j <= tid; j++) {
        factorial *= j;
    }

    printf("Thread %d result is %llu\n", tid, factorial);

    return NULL;
}




int main(int argc, char *argv[])
{


    // if there is an incorrect number of args, error and exit.
    if (argc != 2) {
        fprintf(stderr, "USAGE: helloT <nthreads>\n");
        exit(-1);
    }

    //set nthreads to the thread arg passed in by the user
    int nthreads = atoi(argv[1]);
    
    //If the user gives invalid input, return
    if (nthreads < 1) {
        fprintf(stderr, "ERROR: numthreads must be >= 1\n");
        exit(-1);
    }

    printf("User requested %d threads\n", nthreads);

    //assuming this is short for return code based on usage
    int rc;
    
    //pthread_t t;
    //int i = 0;
    

    // Array of ints for create function.
    int pid[nthreads];

    pthread_t * t;
    t = (pthread_t *) malloc (nthreads*sizeof(pthread_t));


    for (int i = 0; i< nthreads; ++i){
        //The program is expecting a pointer to an int in the factorial method. i is a temporary
        //variable which is changing, so an array is necessary. I tried this with i initially and all 
        //of the printouts were for the max number, and none of the smaller ones. I'm guessing they 
        //were still pointing to wherever i was in memory when join was called which isn't the
        //desired result.
        pid[i] = i;
        rc = pthread_create(&t[i], NULL, Factorial, (void *) &pid[i]);

        if (rc){
            fprintf(stderr, "ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }


    // join will wait for each thread to terminate before returning. It will return -1 for failure and 0 for success.
    for (int i = 0; i< nthreads; ++i){
        rc = pthread_join(t[i], NULL);
        if (rc){
            fprintf(stderr, "ERROR; return code from pthread_join() is %d\n", rc);
            exit(-1);
        }
    }


    exit(0);
}





