#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h> // for open
#include <unistd.h> // for close
#include <string.h> //strings
#include <errno.h> //errors
#include <ctype.h> //for toupper
#include <dirent.h> //for directories
#include <pthread.h> //threads
#include <sys/stat.h>// filesize
#include <sys/mman.h> //mmap

//Ryan FIlgas
//CS532
//filechecker.c

// INPUT: D: directory containing unsorted files
//        T: number of threads
// EXIT CONDITIONS: DONE: cannot open directory
//                  DONE: cannot open subdirectory 'sorted'
//                  DONE: wrong number of args
//                  DONE: filenames don't match
// Setup: assign subset to each thread struct, and get filenames for each thread.
// Memory map all files.-----------------------------------------------------------------------------------------------------------------
// Create T Threads to execute
// For each file in range: check that there is a sorted and unsorted version. CHeck that the file is sorted.
// Create a function to read from file. Verify the matching file, and check if sorted.

/*
   create a new C language program called filechecker.c
   That inputs D and T as command line arguments:
   D - directory containing unsorted files. filechecker should check to see that D has a sub-directory called "sorted" 
   that contains a sorted version of each file in D. If it cannot open D or cannot open the sub-directory then it should print a helpful error message and exit.
   T - number of checker threads

   the program should create T threads and then each of those threads independently checks a subset of the files in <D>/sorted to make sure that each file is a 
   correctly sorted version of the corresponding file in D. it should assume that the file D/unsorted_<id>.bin has a sorted version called <D>/sorted/sorted_<id>.bin
   */

//DONE
//  1. choose next file ID to check
//  2. mmap in the unsorted version of the file
//  3. mmap in the sorted version of the file
//  4. check that the sorted version is in fact sorted
//  5. check that every element in the unsorted file appears in the sorted file.
//  6. check that the files are the same size

#define NAME_BUFF 5000
#define FILE_BUFF 99999
//#define DEBUG

const char SUB_DIR[] = "sorted";
const char FILE_SUFF[] = ".bin";
const int BACKSLASH = 1;
const int IS_PARENT = 1;
const int IS_CHILD = 0;
const int NUM_ARGS = 3;
//int MIN_NAME_SIZE = (strlen(SUB_DIR) + strlen(FILE_SUFF));L


// Struct to hold data for each thread
typedef struct {
    int tid;
    int start;
    int end;
    char ** argv;
    int sorted;
    int unsorted;
    char main_dir[NAME_BUFF];
    int main_dir_size;
    char ** s_names;
    char ** u_names;
} thread_i;


void validate_input(int argc, char ** argv, int * unsorted_fd, int * sorted_fd, char sorted_dir[]);
int get_filenames(char * directory, char ** names, int is_parent);
void initiate_threads(char ** argv, thread_i * thread_info, int sorted, int unsorted, char ** u_names, char ** s_names);
void * parse_data(void * thread_info);


//helper functions
void map_data(char * filenames, int start, int end);
int is_sorted(unsigned int array[], int size);
void sort(unsigned int array[], int size);
int is_match(unsigned int left[], unsigned int right[], int size);
int is_bin(char * name, int max);
void extract_directory(char filename[], char * to_extract, int size);
int strip_prefix(char filename[], int max, char * remove);



int main(int argc, char ** argv){

    // Get file descriptors and check input.
    int sorted_fd = 0;
    int unsorted_fd = 0;
    char sorted_dir[NAME_BUFF];
    int tnum = atoi(argv[2]);
    validate_input(argc, argv, &unsorted_fd, &sorted_fd, sorted_dir);

    // Get filenames and number of files
    char * sorted_names[NAME_BUFF];
    char * unsorted_names[NAME_BUFF];

    int num_unsorted = get_filenames(argv[1], unsorted_names, IS_PARENT);
    int num_sorted = get_filenames(sorted_dir, sorted_names, IS_CHILD);

    //allocate and initiate thread data
    thread_i thread_info[tnum];
    initiate_threads(argv, thread_info, num_sorted, num_unsorted, unsorted_names, sorted_names);

    //Contains data for each thread.
    pthread_t mythreads[tnum];


    //---------------------------------------------------------------------------------------------------------

    //call threads
    int rc = 0;
    for (int i = 0; i < tnum; ++i) {
        // Args: actual_thread | NULL | Method | data to pass
        rc = pthread_create(&mythreads[i], NULL, parse_data, (void *) &thread_info[i]);
        if (rc){
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }	

    //join threads
    for (int i = 0; i < tnum; ++i) {
        rc = pthread_join(mythreads[i], NULL);
        if (rc) {
            fprintf(stderr, "ERROR joining with thread %d (error==%d)\n", thread_info[i].tid, rc);
            exit(-1);
        }
    }

    //---------------------------------------------------------------------------------------------------------

    // close files and deallocate memory
    close(sorted_fd);
    close(unsorted_fd);
    for(int i = 0; i < num_sorted; ++i){
        free(sorted_names[i]);
        free(unsorted_names[i]);
    }
    printf("All files have been successfuly checked. Data matches.\n");

    exit(EXIT_SUCCESS);
}




// Looking back this funciton should be broken up. It does all of the work for each thread.
void * parse_data(void * thread_info){
    thread_i * t_info = (thread_i *) (thread_info);

    int start = t_info->start;
    int end = t_info->end;
    char ** u_names = t_info -> u_names;
    char ** s_names = t_info -> s_names;
    int fd_sorted = 0;
    int fd_unsorted = 0;

    int name_length = 0;
    int s_name_length = 0;
    char to_strip[5000];
    char to_strip_2[5000];
    char subdir[5000];
    strcpy(subdir, SUB_DIR);
    unsigned int * s_nums = NULL;
    unsigned int * u_nums = NULL;
    int s_size = 0;
    int u_size = 0;

    for(int i = start; i <= end; ++i){
        //-----Check if names match------------------------------------------------------------------
        char unsorted_name[5000];
        sprintf(unsorted_name, "%s/%s", t_info->argv[1], u_names[i]);
        char sorted_name[5000];
        sprintf(sorted_name, "%s/%s/%s", t_info->argv[1], SUB_DIR, s_names[i]);

        //-----Check if names match------------------------------------------------------------------
        // UNSORTED
        strcpy(to_strip, u_names[i]);
        name_length = strlen(u_names[i]);

        //SORTED
        strcpy(to_strip_2, s_names[i]);
        s_name_length = strlen(s_names[i]);

        //strip main directory name
        int prefix = strip_prefix(to_strip, name_length, t_info->main_dir);
        int prefix2 = strip_prefix(to_strip_2, s_name_length, subdir);
        if(prefix == 0 || prefix2 == 0 || strcmp(to_strip, to_strip_2) != 0){
            fprintf(stderr, "Base directory filename: %s doesn't match sub directory counterpart: %s.\n", to_strip_2, to_strip);
            exit(-1);
        }

        //-----GET FILE DESCRIPTORS------------------------------------------------------------------
        fd_sorted = open(sorted_name, O_RDONLY);
        if(fd_sorted < 0){
            int err = errno;
            fprintf(stderr, "Unable to open file: %s : (%s)\n", sorted_name, strerror(err));
            exit(-1); 
        }

        fd_unsorted = open(unsorted_name, O_RDONLY);
        if(fd_unsorted < 0){
            int err = errno;
            fprintf(stderr, "Unable to open file: %s : (%s)\n", unsorted_name, strerror(err));
            exit(-1); 
        }

#ifdef DEBUG
        printf("OPENING FILE: %d\n, SORTED: %s\n, UNSORTED %s\n", i, to_strip_2, to_strip);
#endif


        //-------GET STATS AND MAP FILES----------------------------------------------------------------------------------
        struct stat u_statbuf;
        struct stat s_statbuf;

        //get stats for unsorted
        //int ustat= fstat(fd_unsorted, &u_statbuf);
        int ustat= stat(unsorted_name, &u_statbuf);
        if(ustat < 0){
            int err = errno;
            fprintf(stderr, "ERROR: Stat assignemnt failed. '%s' (%s)\n", unsorted_name, strerror(err));
            exit(-1);
        }

        //get stats for sorted
        int sstat= stat(sorted_name, &s_statbuf);
        //int sstat= fstat(fd_sorted, &s_statbuf);
        if(sstat < 0){
            int err = errno;
            fprintf(stderr, "ERROR: Stat assignemnt failed. '%s' (%s)\n", sorted_name, strerror(err));
            exit(-1);
        }


        //error if file sizes don't match
        if(s_statbuf.st_size != u_statbuf.st_size){
            int err = errno;
            fprintf(stderr, "ERROR: File Sizes don;t match '%s' :  '%s' (%s)\n", sorted_name,  unsorted_name, strerror(err));
            exit(-1);
        }

        s_size = s_statbuf.st_size / sizeof(unsigned int);
        u_size = u_statbuf.st_size / sizeof(unsigned int);

        s_nums = mmap(NULL,s_statbuf.st_size,PROT_READ | PROT_WRITE, MAP_PRIVATE, fd_sorted, 0);
        if(s_nums == MAP_FAILED){
            int err = errno;
            fprintf(stderr, "ERROR: Failed to map: '%s' (%s)\n", sorted_name, strerror(err));
            exit(-1);
        }

        u_nums = mmap(NULL,u_statbuf.st_size,PROT_READ | PROT_WRITE, MAP_PRIVATE,fd_unsorted, 0);;
        if(u_nums == MAP_FAILED){
            int err = errno;
            fprintf(stderr, "ERROR: Failed to map: '%s' (%s)\n", unsorted_name, strerror(err));
            exit(-1);
        }
        //done with these close them
        close(fd_sorted);
        close(fd_unsorted);

        //s_nums, u_nums, s_size, u_size
        if(!is_sorted(s_nums, s_size))
        {
            printf( "ERROR: File:  %s is not sorted.", sorted_name);
            exit(-1);
        }
        
        sort(u_nums, u_size);

        int match = is_match(u_nums, s_nums, u_size);
        if(!match)
        {
            printf("Files %s and %s don't have matching values", u_names[i], s_names[i]);
            exit(-1);
        }

        //housekeeping
        name_length = 0;
        s_name_length = 0;
        to_strip[0] = '\0';
        to_strip_2[0] = '\0';

        //deallocate mmaps
        int u_unmap = munmap(u_nums, u_statbuf.st_size);
        if(u_unmap < 0){
            int err = errno;
            fprintf(stderr, "ERROR: Failed to unmap: '%s' (%s)\n", unsorted_name, strerror(err));
            exit(-1);
        }

        int s_unmap = munmap(s_nums, u_statbuf.st_size);
        if(s_unmap < 0){
            int err = errno;
            fprintf(stderr, "ERROR: Failed to unmap: '%s' (%s)\n", sorted_name, strerror(err));
            exit(-1);
        }
        s_size = 0;
        u_size = 0;
    }
    return NULL;
}




// check for matching unsigned int arrays. Return 0 if false, true if not.
int is_match(unsigned int left[], unsigned int right[], int size){
    for(int i = 0; i < size; ++i){
        if(left[i] != right[i])
            return 0;
    }
    return 1;
}





void sort(unsigned int array[], int size){
    int key = 0;
    int predecessor = 0;
    for(int i = 1; i < size; ++i){
        // Algorithm calls for a predecessor. The requires starting an element ahead for the key.
        key = array[i];

        // set the current element to compare, starting at 0.
        predecessor = i - 1;

        // Move each element up one in descending order until the place to insert is found.
        while(predecessor >= 0 && array[predecessor] > key){
            array[predecessor + 1] = array[predecessor];
            --predecessor;
        }
        // There's room to insert, copy data
        array[predecessor + 1] = key;
    }
}



int is_sorted(unsigned int array[], int size){
    int j = 0;
    for(int i = 1; i < size; ++i){
        if(array[j] > array[i]){
            return 0;
            ++j;
        }
    }
    return 1;
}







int get_filenames(char * directory, char ** names, int is_parent){
    struct dirent ** filelist;
    int nfiles = scandir(directory, &filelist, NULL, alphasort);
    //names = malloc(sizeof(char *) * nfiles);

    int count = 0;
    int temp_length = 0;
    if(nfiles != -1)
    {
        //start at 2 to skip . and .. directories
        for(int i = 0; i < nfiles; ++i)
        {
            temp_length = strlen(filelist[i] -> d_name);
            if(is_bin(filelist[i]->d_name, temp_length))
            {
                names[count] = (char*) malloc((temp_length) * sizeof(char*));
                strcpy(names[count], filelist[i]->d_name);
                ++count;
            }
        }
    }
    else{
        int err = errno;
        fprintf(stderr, "ERROR: could not open '%s' (%s)\n", directory, strerror(err));
        exit(-1);
    }
    return count;
}








void validate_input(int argc, char ** argv, int * unsorted_fd, int * sorted_fd, char sorted_dir[]){
    if(argc != NUM_ARGS){
        int err = errno;
        fprintf(stderr, "Incorrect number of arguments: Usage: <Directory>, <Number of Threada>: %s (%s)\n", argv[1], strerror(err));
        exit(-1); 
    }
    if(atoi(argv[2]) <= 0){
        int err = errno;
        fprintf(stderr, "Cannot run with a non positive number of threads: Usage: <Directory>, <Number of Threada>: %s (%s)\n", argv[1], strerror(err));
        exit(-1); 
    }

    // Open each directory, and error if invalid
    (*unsorted_fd) = open(argv[1], O_RDONLY |  O_DIRECTORY);
    if((*unsorted_fd) < 0){
        int err = errno;
        fprintf(stderr, "Unable to open directory:  %s (%s)\n", argv[1], strerror(err));
        exit(-1); 
    }

    sprintf(sorted_dir, "%s/%s", argv[1], SUB_DIR);
    int length = strlen(argv[1]) + BACKSLASH + strlen(SUB_DIR);
    sorted_dir[length] = '\0';
    (*sorted_fd) = open(sorted_dir, O_RDONLY |  O_DIRECTORY);
    if((*sorted_fd) < 0){
        int err = errno;
        fprintf(stderr, "Unable to open subdirectory: %s (%s)\n", sorted_dir, strerror(err));
        exit(-1); 
    }
    return;
}








// Assign start and end indexes for each thread.
void initiate_threads(char ** argv, thread_i * thread_info, int sorted, int unsorted, char ** u_names, char ** s_names){
    if(sorted != unsorted){
        fprintf(stderr, "The number of sorted and unsorted files must be equal. Check files for completeness, and remove extra files.Sorted: %d, Unsorted: %d\n", sorted, unsorted);
        exit(-1); 
    }

    int num_files = sorted;
    int num_threads = atol(argv[2]); //num threads
    int step = num_files / num_threads;
    int remainder = 0;
    if((step * num_threads) < num_files){
        remainder = num_files % (step * num_threads);
    }
    int temp_end = 0;
    int next_start = 0;

    void extract_directory(char filename[], char * to_extract, int size);
    char main_dir[NAME_BUFF];
    int dirsize = strlen(argv[1]);
    extract_directory(main_dir, argv[1], dirsize);

    //initiate each thread
    for(int i = 0; i < num_threads; ++i){
        thread_info[i].tid = i; //Set index for TID
        thread_info[i].argv = argv; //Set argv
        thread_info[i].sorted = sorted;
        thread_info[i].unsorted = unsorted;
        thread_info[i].s_names = s_names;
        thread_info[i].u_names = u_names;
        (strcpy(thread_info[i].main_dir, main_dir));
        thread_info[i].main_dir_size = dirsize;

        if(remainder >= 1  && temp_end < num_files){ //adjustment if files aren't divisible by threads.
            ++temp_end; //Add One to this thread.
            --remainder; //Subtract from remainder so it approaches zero.
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




// simple test to see if file contains 'sor' for sorted. #hacky
int is_bin(char * name, int max){
    int MIN_NAME_SIZE = strlen(SUB_DIR) + strlen(FILE_SUFF);
    if(!name || max < MIN_NAME_SIZE)
        return 0;
    for(int i = 2; i < max; ++i){
        if(tolower(name[i - 2]) == 's' && tolower(name[i-1]) == 'o' && tolower(name[i]) == 'r')
            return 1;
    }
    return 0;
}







//shift the filename to letters to erase "un" and cap the end with '\0'
int strip_prefix(char filename[], int max, char * remove){
    int to_strip = strlen(remove);
    if(max <= to_strip)
        return 0;
    // shift num letters and cap
    for(int i = to_strip; i < max; ++i){
        filename[i - to_strip] = filename[i];
    }
    filename[max - to_strip] = '\0';
    return 1;
}






// extract directory name entered by user 
void extract_directory(char filename[], char * to_extract, int size){
    int last_slash = 0;
    for(int i = 0; i < size; ++i){
        if(to_extract[i] == '/')
            last_slash = i;
    }

    int j = 0;
    for(int i = (last_slash + 1); i < size; ++i){
        filename[j]= to_extract[i];
        ++j;
    }
    filename[j] = '\0';
}
