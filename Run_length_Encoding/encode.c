#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <fcntl.h>
#include <malloc.h>
#include <unistd.h>
#include <string.h>
#include <float.h>
#include <sys/resource.h>

void main(){

        int input_image_fp;
        char input_image[100] = "boat_512_512.raw";
        int width = 512,height = 512;

        printf("Give input image name : ");
        scanf("%s",input_image);
        printf("\nGive width and height of image : ");
        scanf("%d%d",&width,&height);
        printf("\nInput Image is %s. width : %d height : %d \n",input_image,width,height);
        
        unsigned char input[height][width];
        input_image_fp= open(input_image,O_RDONLY);

        if(input_image_fp<0){
                printf("Error in opening %s image \n",input_image);
                exit(1);
        }
        read(input_image_fp,&input[0][0],width*height*sizeof(unsigned char));
        close(input_image_fp);

        FILE *fp = fopen("encodings.txt","w"); 
        if (fp == NULL) 
                printf("Can't create file encodings.txt..."); 


        int cnt=0;
        unsigned char pix_val = 255-input[0][0], start_flag = 1;

        for(int i=0; i<height; ++i){
                for(int j=0; j<width; ++j){
                        if(pix_val == input[i][j]){
                                cnt++;
                        }
                        else
                        {
                                if(start_flag != 1){
                                        putw(cnt, fp);
                                        putc(pix_val, fp);
                                }
                                else{
                                        start_flag = 0;
                                }
                                pix_val = input[i][j];
                                cnt = 1;
                        }
                }
        }        
        putw(cnt, fp);
        putc(pix_val, fp);         
        printf("\n\nEncodings.txt file has been created...");   
        fclose(fp);
}