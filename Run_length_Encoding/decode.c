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

        int output_image_fp;
        char output_image[100] = "out.raw";
        int width = 512,height = 512;

        
        printf("Give output image name : ");
        scanf("%s",output_image);
        printf("\nGive width and height of image : ");
        scanf("%d%d",&width,&height);
        printf("\noutput Image is %s. width : %d height : %d \n",output_image,width,height);
        
        unsigned char output[height][width];
        output_image_fp=creat(output_image,0667);

        if(output_image_fp<0){
                printf("Error creating %s image \n",output_image);
                exit(1);
        }
        

        FILE *fp = fopen("encodings.txt","r"); 
        if (fp == NULL) 
                printf("Can't create file encodings.txt..."); 


        int cnt=0;
        unsigned char pix_val = 0, start_flag = 1;
        int row_count = 0, total_count = 0;

        while((cnt = getw(fp)) != EOF){
                pix_val = (unsigned char)getc(fp);
                for(int j=0; j<cnt; ++j){
                        if(total_count % width == 0 && start_flag == 0)
                                row_count++;
                        if(start_flag)
                                start_flag = 0;
                        output[row_count][total_count%width] = pix_val;
                        total_count++;
                }
        } 
        fclose(fp);

        write(output_image_fp,&output[0][0],width*height*sizeof(unsigned char));
        printf("\n\n%s file has been created...", output_image);   
        close(output_image_fp);
}