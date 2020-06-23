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
comp div_comp_nums(comp num1, comp num2);
comp sub_comp_nums(comp num1, comp num2);

void main()
{
    comp num1={0}, num2={0};
    printf("\nEnter the real part of number 1 : ");
    scanf("%lf", &num1.real);
    printf("\nEnter the imaginary part of number 1 : ");
    scanf("%lf", &num1.imag);
    printf("\nEnter the real part of number 2 : ");
    scanf("%lf", &num2.real);
    printf("\nEnter the imaginary part of number 2 : ");
    scanf("%lf", &num2.imag);
    printf("\nEntered num 1 : %f + j(%f)", num1.real, num1.imag);
    printf("\nEntered num 2 : %f + j(%f)", num2.real, num2.imag);

    comp addition = add_comp_nums(num1, num2);
    printf("\n\n (%f + j(%f)) + (%f + j(%f)) = %f + j(%f)", num1.real, num1.imag, num2.real, num2.imag, addition.real, addition.imag);
    
    comp subtraction = sub_comp_nums(num1, num2);
    printf("\n\n (%f + j(%f)) - (%f + j(%f)) = %f + j(%f)", num1.real, num1.imag, num2.real, num2.imag, subtraction.real, subtraction.imag);

    comp mult = mult_comp_nums(num1, num2);
    printf("\n\n (%f + j(%f)) * (%f + j(%f)) = %f + j(%f)", num1.real, num1.imag, num2.real, num2.imag, mult.real, mult.imag);

    comp divison = div_comp_nums(num1, num2);
    printf("\n\n (%f + j(%f)) / (%f + j(%f)) = %f + j(%f)", num1.real, num1.imag, num2.real, num2.imag, divison.real, divison.imag);
    printf("\n");
}

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