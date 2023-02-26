#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h> //just for seeding random

long unsigned int nkexpected(long unsigned int n, long unsigned int k);
long unsigned int factorial(long unsigned int n);
long unsigned int SIZE = 100;
long unsigned int nksolve(long unsigned int n, long unsigned int k, long unsigned int array[SIZE][SIZE]);


int main(){

    long unsigned int n;
    long unsigned int k;
    printf("Please enter in n followed by k");
    scanf("%lu", &n);
    scanf("%lu", &k);
    SIZE = n;
    long unsigned int array[SIZE][SIZE];
    long unsigned int solution = nksolve(n,k,array);
    


    for(long unsigned int i = 0; i < SIZE; ++i){
        printf("\n");
        for(long unsigned int j = 0; j < SIZE; ++j){
            printf("  %lu  ", array[i][j]);
        }
        printf("\n");
    }
    long unsigned int expected = nkexpected(n,k);
    printf("\nThe Expected result is: %lu\n", expected);
    printf("\nThe Actual result is: %lu\n", solution);
    printf("\n");




    return EXIT_SUCCESS;
}


long unsigned int nksolve(long unsigned int n, long unsigned int k, long unsigned int array[SIZE][SIZE]){
  // initialize table t
  for (long unsigned int r = 0 ; r < SIZE; r++) {
    for(long unsigned int c = 0 ; c < SIZE ; c++) {
        array[r][c] = 0;
    }
  }
  array[0][0] = 1 ; // initialize top of table.
  long unsigned int check = 0;

  // tabulate  
  for (long unsigned int r = 0; r < SIZE; r++) {

    for(long unsigned int c = 0; c < SIZE; c++) {

        if(c == 0 || r == 0)
            array[r][c] = 1;
        else
            array[r][c] = array[r-1][c] + array[r][c-1];
    //if(c > check) array[r][c] = 0;
    }
    ++check;
  }

  return array[n-k][k];
}

// Time Complexity: Big_theta(n*k)    [We can actually do better!  Can you find out how?]
// Space Complexity:  Big_theta(n*k)
// Note: Easy creation of the table results in
//      space complexity: Big_theta(n*n)





















//check
long unsigned int nkexpected(long unsigned int n, long unsigned int k){
	return factorial(n)/(factorial(k)*factorial(n-k));
}

long unsigned int factorial(long unsigned int n){
	int result = 1;
	for(long unsigned int i = 1; i <= n; ++i){
		result *= i;
	}
	return result;
}

