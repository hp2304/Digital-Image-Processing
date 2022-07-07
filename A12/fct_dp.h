#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <fcntl.h>
#include <malloc.h>
#include <unistd.h>
#include <string.h>
#include "complex_struct.h"
#include <pthread.h>

int len;

comp omega(int N, int k);
unsigned int reverseBits(unsigned int n, int max_shift);
void change_in_out(int, comp *, comp *);

void* find_1d_fct(void *);

void* find_1d_fct(void *arg){
    
    comp *arr = (comp *)arg;
    int fct_len = 2*len;
    comp in_arr[2*len];
    comp out_arr[2*len];
    memset(in_arr, 0, sizeof(in_arr));
    memset(out_arr, 0, sizeof(out_arr));
    
    for(int i=0;i<len;i++){
        out_arr[i] = *(arr+i);
        out_arr[(2*len) - 1 - i] = *(arr+i);
    }
    for(int i=0;i<fct_len;i++){
        int bit_rev = reverseBits(i, (int)(log(2*len)/log(2))-1);
        in_arr[i] = out_arr[bit_rev];
    }
    for(int i=2;i<=fct_len;i*=2){
        for(int j=0;j<fct_len;j++){
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
        change_in_out(fct_len, &in_arr[0], &out_arr[0]);
    }
    for(int i=0;i<len;i++){
        comp temp;
        temp.real = cos(-M_PI*i*(1/(double)fct_len));
        temp.imag = sin(-M_PI*i*(1/(double)fct_len));
        if(i==0){
            *(arr+i) = scalar_mult(mult_comp_nums(out_arr[i], temp), 0.5*pow(1/(double)len, 0.5));
        }
        else{
            *(arr+i) = scalar_mult(mult_comp_nums(out_arr[i], temp), 0.5*pow(2/(double)len, 0.5));
        }
    }
    pthread_exit(0);
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