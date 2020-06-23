#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <fcntl.h>
#include <malloc.h>
#include <unistd.h>
#include "complex_struct.h"

comp compute_fft(int idx, int level);
comp omega(int N, int k);
unsigned int reverseBits(unsigned int n, int max_shift);
unsigned char inp[2048] = {0};

void main(){
    unsigned char arr[32]; //= {1,2,3,4};
    size_t length = sizeof(arr)/sizeof(arr[0]);
    comp result[length];
    for(int j=0;j<length;j++){
        inp[j] = reverseBits(j, (int)(log(length)/log(2))-1);
    }
    
    double mag;
    for(int i=0; i<length; i++){
        result[i] = compute_fft(i, length);
        mag = sqrt(pow(result[i].real, 2) + pow(result[i].imag, 2));
        //printf("%f %f \n", result[i].real, result[i].imag);
        printf("%f ", mag);
    }
   
}

comp compute_fft(int idx, int len){
    
    comp result={0};
    if(len == 2){
        if(idx%len==0){
            comp op1 = {(double)inp[idx], 0};
            comp op2 = {(double)inp[(len/2)+idx], 0};
            result = add_comp_nums(op1, mult_comp_nums(omega(len, 0), op2));
        }
        else{
            comp op1 = {(double)inp[idx-(len/2)], 0};
            comp op2 = {(double)inp[idx], 0};
            result = sub_comp_nums(op1, mult_comp_nums(omega(len, 0), op2));
        }
        return result;
    }
    else
    {
        len /= 2;
        if(len>(idx%(len*2))){
            comp op1 = compute_fft(idx,len);
            comp op2 = compute_fft(idx+len,len);
            result = add_comp_nums(op1, mult_comp_nums(omega(len*2, idx), op2));
        }
        else{
            comp op1 = compute_fft(idx-len,len);
            comp op2 = compute_fft(idx,len);
            //printf("\n%f %f \n", mult_comp_nums(omega(len*2, idx), op2).real,mult_comp_nums(omega(len*2, idx), op2).imag);
            result = add_comp_nums(op1, mult_comp_nums(omega(len*2, idx), op2));
        }
        return result;
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