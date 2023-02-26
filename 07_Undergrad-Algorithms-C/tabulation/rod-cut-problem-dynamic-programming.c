
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int rod_problem(int n, int prices[]);
int cut_rod(int n, int table[], int prices[]);
int main(){


    int n = 5;
	int prices[] ={1,1,1,1,1};
    int catch = rod_problem(n, prices);
    printf("\n%d\n", catch);


    return EXIT_SUCCESS;
}



int rod_problem(int n, int prices[]){
	int table[n];
	for(int i = 0; i < n; ++i){
		table[i] = -1;
	}

    // for eah length, calculate its max and tabulate it
	for(int i = 0; i < n; ++i){
		table[i] = cut_rod(i, table, prices);
	}
	return table[n-1];
}

int cut_rod(int n, int table[], int prices[]){
	if(n < 0)
		return -1;
    if(n == 0)
        return table[0];
    
	int temp = 0;
	int max = 0;
    // starting at the beginning of the table, take the max of the inverses.
	for(int i = 0, record = n-1; i < n; ++i, --record){
		temp = table[i-1] + prices[record]; //start this in terms of the previous table index
		if(temp > max)
			max = temp;
	}
	return max;
}
