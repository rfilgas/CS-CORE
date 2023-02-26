#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int f(int n, int table[]);
int minimum(int a, int b, int c);
int change(int n, int table[]);

int main(){
    int n = 9;
    int table[n+1];
    int catch = change(n, table);
    printf("\n");
    printf("%d", catch);
    printf("\n");
    for(int i = 0; i < n+1; ++i){
        printf(" %d", table[i]);

    }
    return EXIT_SUCCESS;

}


int change(int n, int table[n+1]){
    //initiate table
    for(int i = 0; i < n+1; ++i){
        table[i] = -1;
    }
    // tabulate
    for(int i = 0; i < n+1; ++i){
        table[i] = f(i, table);
    }
    return table[n];
}

int f(int n, int table[n+1]){
    if(n < 0)
        return 999999;
    if(n == 0)
        return 0;
    if(n == 1 || n == 3 || n == 5)
        return 1;
    if(n == 2)
        return 2;
    if(n == 4)
        return 2;
    int T1 = table[n-1];
    int T3 = table[n-3];
    int T5 = table[n-5];
    int min = minimum(T1, T3, T5);
    return 1 + min;
}


int minimum(int a, int b, int c){
    int min = a;
    if(b < a)
        min = b;
    if(c < b)
        min = c;
    return min;
}





// 1 1
// 2
// 3
// 4
// 5
// 6
// 7
// 8
// 9
//
