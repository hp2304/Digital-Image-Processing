#include <stdio.h>

void transpose( comp *array, int, int);
int findSize(int , int);
void initZero2(comp *inp, int);
void conjugate_arr(comp *, int, int);
void hermition_arr(comp *, int, int);


void conjugate_arr(comp *arr, int height, int width){
        comp var;
        for(int i=0;i<height;i++){
                for(int j=0;j<width;j++){
                        var = *((arr + (i*width)) + j);
                        var.imag = (-1)*var.imag;
                        *((arr + i*width) + j) = var;
                }
        }
}

void hermition_arr(comp *arr, int height, int width){
        comp var1, var2, temp;
        for(int i=0;i<height;i++){
                for(int j=0;j<width;j++){
                        if(j>i){
                                var1 = *((arr + i*width) + j);
                                var2 = *((arr + j*width) + i);
                                var1.imag = (-1)*var1.imag;
                                var2.imag = (-1)*var2.imag;
                                *((arr + i*width) + j) = var2;
                                *((arr + j*width) + i) = var1;
                        }
                        if(i==j){
                                temp = *((arr + (i*width)) + j);
                                temp.imag = (-1)*temp.imag;
                                *((arr + i*width) + j) = temp;
                        }
                }
        }
}

void transpose(comp *arr, int height, int width){
        comp var;
        for(int i=0;i<height;i++){
                for(int j=0;j<width;j++){
                        if(j>i){
                                var = *((arr + (i*width)) + j);
                                *((arr + i*width) + j) = *((arr + j*width) + i);
                                *((arr + j*width) + i) = var;
                        }
                }
        }
}

void initZero2(comp *arr, int len){
        comp var={0.,0.};
        for(int i=0;i<len;i++){
                for(int j=0;j<len;j++){  
                        *((arr + i*len) + j) = var;
                }
        }
}

int findSize(int h, int w){
        int len;
        len = (h>=w)?h:w;
        len = (int)pow(2,ceil(log(len)/log(2)));
        return len;
}