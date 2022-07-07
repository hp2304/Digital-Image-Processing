#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <fcntl.h>
#include <malloc.h>
#include <unistd.h>
#include <string.h>
#include <float.h>
#define WINDOW_SIZE 25

void main(){
        
        char input_image[100] = "noisy_var_0.01.raw";
        int width = 512, height = 512;
        
        printf("Give input image name : ");
        scanf("%s",input_image);
        printf("\nGive width and height of image : ");
        scanf("%d%d",&width,&height);
        printf("\nInput Image is %s. width : %d height : %d \n",input_image,width,height);
        
        
        unsigned char input[height][width];
        int input_image_fp= open(input_image,O_RDONLY);
        if (input_image_fp<0)
        {
                printf("Error in opening %s image \n",input_image);
                exit(1);
        }
        read(input_image_fp, &input[0][0], width*height*sizeof(unsigned char));

        double noise_var = 0.01;
        printf("\nEnter the variance of the noise : ");
        scanf("%lf", &noise_var);

        for (int scan=0; scan<height; ++scan){
                for (int pix=0; pix<width; ++pix){
                        int cnt=0;
                        double mean = 0;
                        
                        for(int i=-(WINDOW_SIZE/2); i<=(WINDOW_SIZE/2); ++i){
                                for(int j=-(WINDOW_SIZE/2); j<=(WINDOW_SIZE/2); ++j){
                                        int r = scan+i;
                                        int c = pix+j;
                                        if(r >= 0 && c >= 0 && r<height && c<width){
                                                mean += input[r][c];
                                                cnt++;
                                        }
                                }
                        }
                        mean /= (double)cnt;

                        double reg_var = 0;
                        for(int i=-(WINDOW_SIZE/2); i<=(WINDOW_SIZE/2); ++i){
                                for(int j=-(WINDOW_SIZE/2); j<=(WINDOW_SIZE/2); ++j){
                                        int r = scan+i;
                                        int c = pix+j;
                                        if(r >= 0 && c >= 0 && r<height && c<width){
                                                reg_var += pow(input[r][c] - mean, 2);
                                        }
                                }
                        }
                        reg_var /= (double)cnt;
                        
                        input[scan][pix] = (unsigned char)((double)input[scan][pix] - ((noise_var/reg_var)*(input[scan][pix] - mean)));
                        
                }
        }
        char out_img_name[100];
        sprintf(out_img_name,"%s_out",input_image);
        //printf("\n%s\n", out_img_name);
        int output_image_fp=creat(out_img_name,0667);
        if (output_image_fp<0)
        {
                printf("Error in creating output %s image\n",out_img_name);
                exit(1);
        }
        write(output_image_fp,&input[0][0],width*height*sizeof(unsigned char));
        close(output_image_fp);
        printf("%s has been generated...", out_img_name);
        printf("\n\nCompleted...");
}