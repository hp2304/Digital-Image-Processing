#include <stdio.h>
#include <math.h>

void main(){
    double sum = 262144;
    int cnt = 255;
    sum = round((double)(sum/cnt));
    printf("%d", sum);
}