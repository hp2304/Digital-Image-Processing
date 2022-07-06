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