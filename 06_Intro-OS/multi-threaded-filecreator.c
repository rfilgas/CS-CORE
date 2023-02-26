#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h> // for open
#include <unistd.h> // for close
#include <time.h> //for seeding random

// Ryan Filgas
// CS 532
// filecreator.c
//
//
// INPUT: directory, number of files, number of ints for each file, number of threads
// Output: A number of binary files named unsorted_<id>,bin, each loaded with 'n' random unsigned ints.


/*
   ASSIGNMENT:
   Your assignment is to write a new program, called filecreator.c. It should accept four command line parameters 
   (d = location of directory, f = number of files to create, r = number of integers to insert into each output file and t = number of threads). 
   it should assume that d exists and give an error if d does not exist or cannot be written to. 
   then it should create f files in the directory d. each output file should be named "unsorted_<id>.bin" where 
   <id> is a unique integer from 0 to (f-1).in each output file the program should write r random 32-bit integers. 
   each integer should be chosen randomly by the rand_r() function. note that the output files must be binary. not ascii. 
   finally, make this program multi-threaded such that each of t threads creates approximately f/t of the files.

   Your source code may NOT use these C language functions: fopen(), fclose(), fread(), fwrite() and related functions. 
   use rand_r() for generating random numbers (do not use rand() or any other method for generating random numbers, use 
   rand_r() only).  use any of the pthread functions. 
*/


//#define DEBUG
#define PI 3.141592654

// Struct to hold data for each thread
typedef struct {
    int tid;
    int start;
    int end;
    int num_to_insert;
    int num_files;
    char ** argv;
    int dir;
} thread_i;


const char FILE_BEGINNING[] = "unsorted_";
const char FILE_END[] = ".bin";
unsigned int global_seed;


//My initiation could be a lot cleaner. I ended up passing arv in as an argument towards then end when I should have started there.
void * write_files(void * thread_info);
void initiate(int * remainder, int step, int t, int r, thread_i * thread_info, char ** argv, int dir, int f);
int make_filename(char * to_fill, const char * beginning, const char * end, int num);
char * int_to_string(int num);



int main(int argc, char **argv) {
    //check num args
    if (argc != 5) { 
        fprintf(stderr, "USAGE: %s <d:directory_location> <f:number_of_files_to_create> <r:number_of_integers_to_insert> <t:number_of_threads>\n", argv[0]);
        exit(-1); 
    }

    //Assign variables for easy access
    int f = atol(argv[2]); //num files
    int r = atol(argv[3]); //num ints to insert
    int t = atol(argv[4]); //num threads
 
    int step = (f/t); //Average num of files per thread
    int remainder = (f % (step * t)); //redistribute to threads
    global_seed = time(NULL);

    //initiate thread ids.
    thread_i thread_info[t];

    //Contains data for each thread.
    pthread_t mythreads[t];



    //Open directory.
    int fd = open(argv[1], 0644);
    //fd = open(argv[1], O_RDWR, 0644);
    
    if(fd < 0){
        fprintf(stderr, "Directory %s does not exist_2\n", argv[1]);
       exit(-1); 
    }

    //initiate thread data
    initiate(&remainder, step, t, r, thread_info, argv, fd, f);

    //call threads
    int rc = 0;
    for (int i = 0; i < t; ++i) {
        // Args: actual_thread | NULL | Method | data to pass
        rc = pthread_create(&mythreads[i], NULL, write_files, (void *) &thread_info[i]);
        if (rc){
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }	

    //join threads
    for (int i = 0; i < t; ++i) {
        rc = pthread_join(mythreads[i], NULL);
        if (rc) {
            fprintf(stderr, "ERROR joining with thread %d (error==%d)\n", thread_info[i].tid, rc);
            exit(-1);
        }
    }

#ifdef DEBUG
// Test read.
    int new_fd = openat(fd, "unsorted_0.bin", O_RDONLY);
    unsigned int new_val;
    if (new_fd) {
        read(new_fd, &new_val, sizeof(new_val));
        printf("File 0 = %u\n", new_val);
        close(new_fd);
    }
    else printf("couldn't connect");
#endif

    //close directory
    close(fd);

    return 0;
}





// Assign start and end indexes for each thread.
void initiate(int * remainder, int step, int t, int r, thread_i * thread_info, char ** argv, int dir, int f){
    int temp_end = 0;
    int next_start = 0;
    for(int i = 0; i < t; ++i){
        thread_info[i].tid = i; //Set index for TID
        thread_info[i].num_to_insert = r;
        thread_info[i].argv = argv; //Set argv
        thread_info[i].dir = dir; //Set directory
        thread_info[i].num_files = f; //Set directory

        if(*remainder >= 1  && temp_end < f){ //adjustment if files aren't divisible by threads.
            ++temp_end; //Add One to this thread.
            --(*remainder); //Subtract from remainder so it approaches zero.
        }

#ifdef DEBUG
        printf("Thread %d: Start: %d\n", i, next_start);
#endif

        thread_info[i].start = next_start; //set start for TID
        temp_end += (step - 1);

        
        thread_info[i].end = temp_end; //set end for TID

#ifdef DEBUG
        printf("Thread %d: End: %d\n", i, temp_end);
#endif

        ++temp_end;
        next_start = temp_end; // set start index
    }
}





// in each file, write 'r' random 32-bit integers chosen by the rand_r() function. File should be binary.
void * write_files(void * thread_info){
    thread_i * temp = (thread_i *) (thread_info);

    int start = temp->start;
    int end = temp->end;
    int fd = 0;
    
    //Make pseudo random number from global seed.
    unsigned int local_seed = global_seed + (10 * temp->tid) + ((temp->tid) * PI);
    int qnums_to_write = temp->num_to_insert;


    // create f # of files in directory 'd'
    char filename[100];
    for(int i =  start; i <= end; ++i){
        make_filename(filename, FILE_BEGINNING, FILE_END, i);
        
        //O_EXCL: terminate if file exists. O_TRUC: Overwrite, O_APPEND: Add to end
        fd = openat(temp->dir, filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
            if(fd < 0){
            fprintf(stderr, "File can't be opened: %s\n", temp->argv[1]);
            exit(-1); 
        }

        //write new random numbers to file
        unsigned int uint_buffer[qnums_to_write];
        for(int k = 0; k < qnums_to_write; ++k){
            uint_buffer[k] = rand_r(&local_seed);
            #ifdef DEBUG
            printf("File %d: Num_assigned: %u\n", i, uint_buffer[k]);
            #endif
        }
        write(fd, &uint_buffer, (sizeof(uint_buffer)));

        close(fd);

    //reset filename
    filename[0] = '\0';
    }
    return NULL;
}






int make_filename(char * to_fill, const char * beginning, const char * end, int num){
    if(!beginning || !end)
        return 0;

    char  my_int[BUFSIZ];
    sprintf(my_int, "%d", num);
    to_fill[0] = '\0';

    int BEGINNING = strlen(beginning);
    int END = strlen(end);
    int NUM = strlen(my_int);
    strncat(to_fill, beginning, BEGINNING);
    strncat(to_fill, my_int, NUM);
    strncat(to_fill, end, END);
    return 1;
}
