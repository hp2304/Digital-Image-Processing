#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <fcntl.h>
#include <malloc.h>
#include <unistd.h>
#include <string.h>
#include "complex_struct.h"
#define MAX_SIZE 2048

comp omega(int N, int k);
unsigned int reverseBits(unsigned int n, int max_shift);
void change_in_out(int, comp *, comp *);

void find_1d_fft(comp input[], int);

void find_1d_fft(comp *arr, int length){
    
    comp in_arr[length];
    comp out_arr[length];
    memset(in_arr, 0, sizeof(in_arr));
    memset(out_arr, 0, sizeof(out_arr));
    
    
    for(int i=0;i<length;i++){
        in_arr[i] = *(arr + reverseBits(i, (int)(log(length)/log(2))-1));
    }
    for(int i=2;i<=length;i*=2){
        for(int j=0;j<length;j++){
            if(j%i<(i/2)){
                comp op1 = in_arr[j];
                comp op2 = in_arr[(i/2)+j];
                out_arr[j] = add_comp_nums(op1, mult_comp_nums(omega(i, j), op2));
            }
            else{
                comp op1 = in_arr[j-(i/2)];
                comp op2 = in_arr[j];
                out_arr[j] = add_comp_nums(op1, mult_comp_nums(omega(i, j), op2));
            }
        }
        change_in_out(length, &in_arr[0], &out_arr[0]);
    }
    for(int i=0;i<length;i++){
        *(arr+i) = out_arr[i];
    }
}

void change_in_out(int len, comp *in_arr, comp *out_arr){
    for(int j=0; j<len; j++){
        in_arr[j] = out_arr[j];
    }
}

comp omega(int N, int k){
    comp result = {0};
    result.real = cos(-2*M_PI*k*(1/(double)N));
    result.imag = sin(-2*M_PI*k*(1/(double )N));
    return result;
}

unsigned int reverseBits(unsigned int n, int max_shift){ 
    unsigned int sum = 0, temp; 
    for(int i=0; i<=max_shift; i++){ 
        temp = n & 1; 
        sum += (temp << (max_shift-i));
        n >>= 1;
    } 
    return sum; 
} 