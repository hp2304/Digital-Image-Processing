#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <fcntl.h>
#include <malloc.h>
#include <unistd.h>
#include <string.h>
#include "complex_struct.h"

int arr[4] = {1,2,3,4};
int findSize(int h, int w);
void method(comp (*arr)[]);
void transpose(comp *arr, int width);
void main(){
    comp arr[4][4];
    int cnt=0;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            arr[i][j].real = (double)i+j+cnt;
            printf("%lf ", arr[i][j].real);
            cnt++;
        }
        printf("\n");
    }
    printf("\n\n\n");

    for(int i=0; i<4;i++){
        transpose(&arr[i][0], 4);
    }
    
    //method(&s[0][0]);
    //printf("%d", findSize(3,5));
    /*
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            printf("%lf ", arr[i][j].real);
        }
        printf("\n");
    }*/
}

void method(comp (*arr)[]){ 
    //printf("%f", arr[0]->real);
}

int findSize(int h, int w){
        int len;
        len = (h>=w)?h:w;
        len = (int)pow(ceil(log(len)/log(2)), 2);
        return len;
}

void transpose(comp *arr, int width){
        printf("%lf \n", (arr)->real);
        for(int i=2;i<width;i++){
              (arr+i)->real = 10;  
        }
        printf("%lf \n", (arr)->real);
}
//*(*(data + i) + j)