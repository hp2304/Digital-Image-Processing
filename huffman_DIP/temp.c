#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

void main(){
        char buff[3][10] = {"0001", "001110", "0111111"};
        unsigned char cnt=7;
        unsigned char temp=0;
        for(int i=0;i<3;i++){
                for(int j=0; buff[i][j]!='\0'; ++j){
                        int s=(int)buff[i][j];
                        s=s-48;
                        //printf("%d %d \n", s, cnt);
                        temp += (s*pow(2, cnt));
                        if(cnt==0){
                                cnt=7;
                                printf("%d ", temp);
                                temp = 0;
                                continue;
                        }
                        cnt--;
                }
        }
        printf("%d", temp);
        /* Encoding logic (read file byte by byte)
        unsigned char b = 0x80;
        char num[8];
        for(int i = 0; i < CHAR_BIT; i++)
        {
                int something = ((b<<i)&(0x80))/128;
                num[i] = (char)something+48;
        }
        printf("%s \n", num);
        */
}