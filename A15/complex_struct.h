#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <fcntl.h>
#include <malloc.h>
#include <unistd.h>


typedef struct  complex_num{
    double real;
    double imag;
}comp;
comp add_comp_nums(comp num1, comp num2);
comp mult_comp_nums(comp num1, comp num2);
comp sub_comp_nums(comp num1, comp num2);
comp div_comp_nums(comp num1, comp num2);

comp add_comp_nums(comp num1, comp num2){
    comp result={0};
    result.real = num1.real + num2.real;
    result.imag = num1.imag + num2.imag;
    return result;
}

comp sub_comp_nums(comp num1, comp num2){
    comp result={0};
    result.real = num1.real - num2.real;
    result.imag = num1.imag - num2.imag;
    return result;
}

comp mult_comp_nums(comp num1, comp num2){
    comp result={0};
    result.real = (num1.real * num2.real) - (num1.imag * num2.imag);
    result.imag = (num1.real * num2.imag) + (num1.imag * num2.real);
    return result;
}

comp div_comp_nums(comp num1, comp num2){
    comp result={0};
    comp mult = {0};
    double mag = (pow(num2.real, 2) + pow(num2.imag, 2));
    num2.imag = (-1)*num2.imag;
    mult = mult_comp_nums(num1, num2);
    result.real = mult.real/mag;
    result.imag = mult.imag/mag;
    return result;
}