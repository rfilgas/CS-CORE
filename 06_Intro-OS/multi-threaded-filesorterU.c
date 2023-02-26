#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> //for toupper
#include <fcntl.h> // for open
#include <unistd.h> // for close
//#include <sys/syscall.h>  //for directories
#include <sys/stat.h> //for mkdir
#include <dirent.h> //for directories
//#define _GNU_SOURCE //for directories
#define BUF_SIZE 1024 //for directories
#define MY_BUFF 99999
//#define DEBUG

//Ryan FIlgas
//CS 532
//filesorterU.c


/*
   filesorterU -- sort binary files

   Write a new program, filesorterU.c  that accepts one command line parameter (D = location of directory 
   containing unsorted binary integer files) The program should exit with an error if D does not exist. It 
   should read each unsorted_<id>.bin file in D, sort the integers found in the file and write the sorted 
   integers to a new file <D>/sorted/sorted_<id>.bin The program should not assume that the sub-directory 
   is already created and should create the <D>/sorted sub-directory if needed.
   Use any sorting algorithm you like, but you must code the sort yourself. You are not allowed to use qsort() 
   or any other library function for sorting.HINT: write a simple sort. Sort speed likely will not limit the speed of your program.
   */


// INPUT: D: directory_path  
// OUTPUT: New_directory, change name from unsorted to sorted


// MUST EXIT WHEN:
/*
DONE: No input parameter to program X
DONE: Input a directory that does not exist X
DONE: Input a directory that contains no unsorted_<id>.bin files // get filenames and check all filenames if sorted.x
DONE: Input a directory that contains unsorted_<id>.bin files that cannot be read X
DONE: Input a directory that already has a sorted sub-directory X
DONE: Input a directory that has a sorted sub-directory that is read-onlyi X
DONE: Input a directory that contains a sorted sub-directory that contains read-only sorted_<>.bin files x
*/


//  Check directory -> make_sub_directory -> For each file:  Load file -> sort file -> write file to new filename in sub directory.

//Setup
int get_filenames(char * directory, char * names[], int * num_files);
void setup(int argc, char ** argv, char * filenames[], int * num_files);
void validate(int argc, char ** argv, char * sorted_dir, int num_files, char * filenames[]);


//  Larger Pieces
void load_array_from_file(char * directory, char * filename, unsigned int to_fill[], char ** argv, int * size);
void sort(unsigned int array[], int size);
void load_sort_write_file(char ** argv, char * filename, char * new_directory);

//Helper functions
int is_sorted(char * name);
int is_unsorted(char * name);
int no_unsorted(char * files[], int max);
void strip_filename(char filename[], int max);


int main(int argc, char **argv){

    //char * filenames[BUF_SIZE];
    char * filenames[MY_BUFF];
    int num_files = 0;

    //validate input and get filenames
    setup(argc, argv, filenames, &num_files);

    //create sorted directory filepath
    char sorted_dir[4096];
    sprintf(sorted_dir, "%s/sorted", argv[1]);

    //error check
    validate(argc, argv, sorted_dir, num_files, filenames);

    //Create new sorted directory
    int status;
    status = mkdir(sorted_dir, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    if(status == -1){
        int err = errno;
        fprintf(stderr, "Couldn't create sorted directory in %s (%s)\n", argv[1], strerror(err));
        exit(-1); 
    }

    for(int i = 0; i < num_files - 1; ++i){
        load_sort_write_file(argv, filenames[i], sorted_dir);
    }

    for(int i = 0; i < num_files; ++i)
        free(filenames[i]);

    exit(EXIT_SUCCESS);
}




// Check for input, check directory, load filenames
void setup(int argc, char ** argv, char * filenames[], int * num_files){
    //*****************************************************************
    //NO INPUT
    if (argc != 2){
        int err = errno;
        fprintf(stderr, "USAGE ERROR: %s <d:directory_location>/unsorted (%s)\n", argv[0], strerror(err));
        exit(-1);
    }
    //*****************************************************************
    //DIRECTORY DOESNT EXIST
    int fd = open(argv[1], 0644);
    close(fd);
    if(fd < 0){
        int err = errno;
        fprintf(stderr, "Setup: Directory %s does not exist (%s)\n", argv[1], strerror(err));
        exit(-1);
    }
    //*****************************************************************
    //GET CURRENT DIRECTORIES FILENAMES
    int temp = 0;
    int success = get_filenames(argv[1], filenames, &temp);
    if(!success){
        fprintf(stderr, "Wrong input given to pull names from directory\n");
        exit(-1); 
    }
    *num_files = temp;
}




// Do all checks requested by assignment.
void validate(int argc, char ** argv, char * sorted_dir, int num_files, char * filenames[]){
    //*****************************************************************
    //SORTED SUB_DIRECTORY EXISTS AND IS READ ONLY
    if(access(sorted_dir, R_OK) == 0 && access(sorted_dir, W_OK) == -1) {
        int err = errno;
        fprintf(stderr, "Sorted directory in %s is read only (%s)\n", argv[1], strerror(err));
        exit(-1); 
    }

    //*****************************************************************
    //SUB DIRECTORY WITH READ ONLY SORTED FILES
    char to_open1 [4096];

    for(int i = 0; i < num_files; ++i){
        sprintf(to_open1, "%s/sorted_%d.bin",sorted_dir, i);
        if(access(to_open1, W_OK) == -1 && access(to_open1, R_OK) == 0 && is_sorted(filenames[i])){
            int err = errno;
            fprintf(stderr, "The directory entered contains sorted files that are read only!(%s)\n", strerror(err));
            exit(-1); 
        }
        to_open1[0] = '\0';
    }

    //*****************************************************************
    //THERE ARE NO UNSORTED FILES
    if(no_unsorted(filenames, num_files)){
        fprintf(stderr, "There are no unsorted files!\n");
        exit(-1); 
    }
    //*****************************************************************
    //CONTAINS UNREADABLE UNSORTED FILES

    //Input a directory that contains unsorted_<id>.bin files that cannot be read
    // Iterate through each and attempt to access. If accessable, check if each file is (is_unsorted && read_only)
    char to_open[4096];
    for(int i = 0; i < num_files; ++i){
        sprintf(to_open, "unsorted/%s", filenames[i]);
        if(access(to_open, R_OK) == -1 && is_unsorted(filenames[i])){
            fprintf(stderr, "The directory entered contains unsorted files that cannot be read!\n");
            exit(-1); 
        }
        to_open[0] = '\0';
    }
    //*****************************************************************
    //SORTED SUB_DIRECTORY EXISTS
    if(access(sorted_dir, F_OK) == 0){
        fprintf(stderr, "Sorted directory in %s already exists!\n", argv[1]);
        exit(-1); 
    }
}



int get_filenames(char * directory, char * names[], int * num_files){
    struct dirent ** filelist;
    int nfiles = scandir(directory, &filelist, NULL, alphasort);
    nfiles -= 2;;
    //skip . and .. directories
    int temp_length = 0;
    char * tempstring;
    if(nfiles != -1){
        //start at 2 to skip . and .. directories
        int k = 2;
        for(int i = 0; i < nfiles; ++i){
            tempstring = filelist[k] -> d_name;
            temp_length = strlen((tempstring) + 1);
            names[i] = (char *) malloc((temp_length) * sizeof(char*));
            strcpy(names[i], tempstring);
            ++k;
#ifdef DEBUG
            printf("%d: %s\n", i, tempstring);
#endif
        }
        *num_files = nfiles;
    }
    else{
        int err = errno;
        fprintf(stderr, "ERROR: could not open '%s' (%s)\n", directory, strerror(err));
        exit(-1);
    }
    return 1;
}



// Keeping for reference
/*
// Get filenames using linux directory entry, and store in names.
int get_filenames(char * directory, char * names[], int * num_files){
    DIR * d;
    struct dirent * file;
    int nfiles = 0;//num files
    int temp_length;
    d = opendir(directory);
    if(d != NULL){
        while ((file = readdir(d)) != NULL) {
            temp_length = strlen((file->d_name) + 1);
            names[nfiles] = (char *) malloc((temp_length) * sizeof(char*));
            strcpy(names[nfiles], file->d_name);
            ++nfiles;
#ifdef DEBUG
            printf("%d: %s\n", nfiles, file->d_name);
#endif
        }
    }
    else{
        int err = errno;
        fprintf(stderr, "ERROR: could not open '%s' (%s)\n", directory, strerror(err));
    }
    *num_files = nfiles;
    closedir(d);
    return 1;
}
*/



void load_sort_write_file(char ** argv, char * filename, char * new_directory){
    int fsize = strlen(filename);

    // LOAD ARRAY
    unsigned int to_fill[MY_BUFF];
    int size = 0; //WILL BE MODIFIED BY LOAD
    load_array_from_file(argv[1], filename, to_fill, argv, &size);


#ifdef DEBUG
    for(int i = 0; i< size; ++i){
        printf("LOADED: %u\n", to_fill[i]);
    }
#endif

    //SORT ARRAY
    sort(to_fill, size);
    strip_filename(filename, fsize);

    char new_filename[5000];
    sprintf(new_filename, "%s/%s", new_directory, filename);

    //WRITE ARRAY
    //O_EXCL: terminate if file exists. O_TRUC: Overwrite, O_APPEND: Add to end
    int fd = open(new_filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
    if(fd < 0){
        int err = errno;
        fprintf(stderr, "ERROR: could not create '%s' (%s)\n", new_filename, strerror(err));
        exit(-1); 
    }

    write(fd, &to_fill, (size * sizeof(unsigned int)));
    close(fd);
}




int is_unsorted(char * name){
    if(!name)
        return 0;
    char unsorted[] = "unsorted";
    int size_unsorted = strlen(unsorted);

    for(int i = 0; i < size_unsorted; ++i){
        if(tolower(name[i]) != unsorted[i])
            return 0;
    }
    return 1;
}





int is_sorted(char * name){
    if(!name)
        return 0;
    char sorted[] = "sorted";
    int size_sorted = strlen(sorted);
    for(int i = 0; i < size_sorted; ++i){
        if(tolower(name[i]) != sorted[i])
            return 0;
    }
    return 1;
}




//if there are no unsorted files return 1
int no_unsorted(char * files[], int max){ 
    if(!files)
        return 0;
    for(int i = 0; i < max; ++i){
        if(is_unsorted(files[i]))
            return 0;
    }
    return 1;
}




//shift the filename to letters to erase "un" and cap the end with '\0'
void strip_filename(char filename[], int max){
    // shift 2 letters and cap
    for(int i = 2; i < max; ++i){
        filename[i - 2] = filename[i];
    }
    filename[max - 2] = '\0';
}


/* ORIGINAL
void load_array_from_file(char * directory, char * filename, unsigned int to_fill[], char ** argv, int * size){
    int fd = open(argv[1], 0644);
    if(fd < 0){
        fprintf(stderr, "Cannot open %s", argv[1]);
        exit(-1);
    }

    int new_fd = openat(fd, filename, O_RDONLY);
    if(new_fd < 0){
        fprintf(stderr, "Strip_filenames: File does not exist");
        exit(-1);
    }

    //unsigned int new_val[BUF_SIZE];
    int j = 0;
    if (new_fd) {
        int bytes_read = 1;
        while(bytes_read > 0){
            bytes_read =  read(new_fd, &to_fill[j], sizeof(unsigned int));
#ifdef DEBUG
            printf("Bytes read = %d\n", bytes_read);
#endif
            if(bytes_read != 0)
                ++j;
        }
        close(new_fd);
    }
    else {
        fprintf(stderr, "Couldnt connect to file: %s\n", filename);
        exit(-1); 
    }
    close(new_fd);
    *size = j;
    return;
}
*/


void load_array_from_file(char * directory, char * filename, unsigned int to_fill[], char ** argv, int * size){
    //char bytes[BUFFER];
    char tempfilename[5000];  // big enough to never overflow
    sprintf(tempfilename, "%s/%s", directory, filename);
    int fd = open(tempfilename, O_RDWR);
    
    int bytes_read = read(fd, to_fill, MY_BUFF);
    if (bytes_read < 0) {
        int err = errno;
        fprintf(stderr, "ERROR while reading '%s' (%s)\n", tempfilename, strerror(err));
        exit(-1);
    }
#ifdef DEBUG
            printf("Bytes read = %d\n", bytes_read);
#endif
    if (bytes_read == MY_BUFF) {
    fprintf(stderr, "ERROR: file '%s' is too big for this program (bytes_read = %d)\n", tempfilename, bytes_read);
    exit(-1);
    }
    *size  = bytes_read / sizeof(unsigned int);
    to_fill[(*size) + 1] = '\0';
    close(fd);
}


/* Insert sort algorithm from geeks for geeks
   To sort an array of size n in ascending order: 
1: Iterate from arr[1] to arr[n] over the array. 
2: Compare the current element (key) to its predecessor. 
3: If the key element is smaller than its predecessor, compare it to the elements before. Move the greater elements one position up to make space for the swapped element.
*/

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
