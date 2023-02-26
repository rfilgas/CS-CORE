#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h> //just for seeding random


//Ryan Filgas
//Hw2: MERGESORT

//HOMEWORK 2 - Implement mergesort. input: int size. Populate an array with random ints between 0 and n.
//              OUTPUT: print array before, print array after


void mergeSortI(int array [],  int size);
void merge(int array[], int left, int middle, int right);
void mergeSort(int array[], int left, int right);
void printInts(int array[], int size);
void initiateRand(int array[], int size);



int main(){

    int length = 0;
    printf("This is a merge sorting program. Please enter the size of an array to randomly generate and sort: ");
    scanf("%d", &length);
    printf("Unsorted: ");

    int array[length];
    initiateRand(array, length);
    printInts(array, length);

    mergeSortI(array, length);

    printf("Sorted:   ");
    printInts(array, length);
    printf("\n");

    return EXIT_SUCCESS;
}



void initiateRand(int array[], int size){
    srandom(time(NULL));
    for(int i = 0; i < size; ++i){
        array[i] = (abs(random())) % size;
    }
}



void printInts(int array[], int size){
    for(int i = 0; i < size; ++i){
        printf("%d ", array[i]);
    }
    printf("\n");
}


// THis is a wrapper to initiate the recursive call.
void mergeSortI(int array [],  int size){
    int left = 0;
    int right = size - 1;
    return mergeSort(array, left, right);
}



void mergeSort(int array[], int left, int right){
    if(right == left)
        return;
    int middle = (left + right) / 2;

    //recursive left sort, inclusive of middle
    mergeSort(array, left, middle);
    //recursive right sort exclusive of middle
    mergeSort(array, middle + 1, right);
    //merge
    merge(array, left, middle, right);
    return;
}



void merge(int array[], int left, int middle, int right){
    //if we get down to two elements, swap as necessary.
    if(right  == left)
        return;
    int size = right - left + 1;
    int temparray[size];
    int current = 0;

    int l = left;
    int r = middle + 1;

    //take care of normal case. Everything finishes at the same time, so copy the smaller
    //values in incrementally until the sort is finished on at least one side.
    while(l <= middle && r <= right){
        if(array[l] <= array[r]){
            temparray[current] = array[l];
            ++l;
        }
        else{
            temparray[current] = array[r];
            ++r;
        }
        ++current;
    }

    //when one side finishes the merge before the other, copy the rest into the temp array.
    while(l <= middle && current < size){
        temparray[current] = array[l];
        ++current;
        ++l;
    }
    while(r <= right && current < size){
        temparray[current] = array[r];
        ++current;
        ++r;
    }


    //Copy the result back to the main array.
    for(int i = 0, j = left; i < size && j <= right; ++i, ++j){
        array[j] = temparray[i];
    }
    return;
}
