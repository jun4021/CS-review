#include <stdio.h>
#include <stdlib.h>

int* saveStairs;
int climbStairs(int n);
int climb(int n);

int CheckStairs(int n){
    if(n==0){
        return 0;
    }
    else if(saveStairs[n]!=0){
        return saveStairs[n];
    }
    else{
        saveStairs[n] = climb(n);
        return saveStairs[n]; 
    }
}

int climb(int n){
    return CheckStairs(n-1)+CheckStairs(n-2);
}

int climbStairs(int n){
    saveStairs = (int*)calloc(46,sizeof(int));
    saveStairs[1]=1;
    saveStairs[2]=2;
    return CheckStairs(n);
}

int main(){
    printf("%d",climbStairs(30));
    return 0;
}