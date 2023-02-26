#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h> //just for seeding random

//Ryan Filgas
//Hw3: HEAPSORT


void initiateRand(int arr[], int size);
void printInts(int arr[], int size);


int heapSortI(int arr [], int size);
void buildHeap(int arr[], int size);
int add(int arr[], int * count, int max, int to_add);
int getParent(int child);

int getRightChild(int parent);
int getLeftChild(int parent);


void sortHeap(int arr[], int size);

void copyInts(int source[], int destination[], int size);
void swap(int arr[], int left, int right);
int greater(int arr[], int a, int b, int max);

int main(){

    int length = 0;
    printf("This is a heap sorting program. Please enter the size of an array to randomly generate and sort: ");
    scanf("%d", &length);
    printf("Unsorted: ");


    int arr[length];
    for(int i = 0; i < length; ++i){
        arr[i] = i;
    }
    //initiateRand(arr, length);
    printInts(arr, length);

    if(!heapSortI(arr, length)){
        printf("There was an unexpected error, the array is empty. Exiting Program...\n");
    }

    printf("Sorted:   ");
    printInts(arr, length);
    printf("\n");

    return EXIT_SUCCESS;
}

// Build and sort were separated so they could be verified for correctness independently.
int heapSortI(int arr [], int size){
    buildHeap(arr, size);
    sortHeap(arr,size);
    return 1;
}


void buildHeap(int arr[], int size){
    int count = 0;
    int tempArray[size];
    for(int i = 0; i < size; ++i){
        add(tempArray, &count, size, arr[i]);
    }
    copyInts(tempArray, arr, size);
}



// 1. Swap first with last.
// 2. Decrement the end. We put the largest where it goes.
// 3. Swap the smaller value with the larger of the left and right children down the chain.
// 4. Rinse and repeat.
// 5. Deal with base case at the end. Indexes 0 and 1 shouldn't assume a swap.
void sortHeap(int arr[], int size){
    int end = size - 1;
    int start = 0;
    int parent = 0;
    int child = 0;//get the index of the greater of two children.
    int temp = 0;
    do{
        swap(arr, start, end);
        parent = 0; // Parent should always be the root starting the swapping process.
        --end; //Decrement end. This works towards our base case.
        child = greater(arr, getRightChild(parent), getLeftChild(parent), size);
        while(child <= end && (arr[parent] < arr[child])){
            swap(arr, child, parent);
            temp = child;
            child = greater(arr, getRightChild(child), getLeftChild(child), size);
            parent = temp;
        }
    }while(end > 1); // Reached base case, there are two nodes left to compare.

    //Fringe/Base case.
    if(arr[0] > arr[1]){
        swap(arr, 0, 1);
    }
    return;
}







//count is the number of items loaded. arr[count] is the index PAST the last item, and also the nbumber of items.
int add(int arr[], int * count, int max, int to_add){
    // the last item is at count -1.
    if(*count == max)
        return 0;
    
    //Beginning of the array.
    if(*count == 0){
        arr[0] = to_add;
        (*count) += 1;
        return 1;
    }

    //count points to the last "node". We need to check its parent for a swap.
    arr[(*count)] = to_add; //set the last node to our int to add.
    int current = (*count); //set count as the current "node".
    (*count) += 1; //increment count for the next run
    int parent = getParent(current); //get the index of the parent
    int exit = 0;
    while(!exit && (arr[current] > arr[parent])){
        if(parent == 0)
            exit = 1; //This is the LAST swap.
        swap(arr, current, parent);
        current = parent;
        parent = getParent(current);
    }
    //We're done.
    return 1;
}



int getParent(int child){
    return ((child - 1)/2);
}

int getRightChild(int parent){
    return((2 * parent) + 2);
}
int getLeftChild(int parent){
    return((2 * parent) + 1);
}

//Helpers
void swap(int arr[], int left, int right){
    int temp = arr[left];
    arr[left] = arr[right];
    arr[right] = temp;
    return;
}

void copyInts(int source[], int destination[], int size){
        for(int i = 0; i < size; ++i){
        destination[i] = source[i];
    }
}

void initiateRand(int arr[], int size){
    srandom(time(NULL));
    for(int i = 0; i < size; ++i){
        arr[i] = (labs(random())) % size;
    }
    return;
}

void printInts(int arr[], int size){
    for(int i = 0; i < size; ++i){
        printf("%d ", arr[i]);
    }
    printf("\n");
    return;
}

int greater(int arr[], int a, int b, int max){
    if(a < max && arr[a] > arr[b])
        return a;
    else return b;
}
