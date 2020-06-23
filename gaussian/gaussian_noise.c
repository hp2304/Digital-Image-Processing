#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <fcntl.h>
#include <malloc.h>
#include <unistd.h>
#include <string.h>
#include <float.h>
#include <sys/resource.h>
#include <stdbool.h>

void main(){

    int input_image_fp,output_image_fp,a;
    char input_image[100] = "boat_512_512.raw",out_img_name[100];
    int width = 512,height = 512;
    int gaussian_freq[100], i;
    float sum = 1;


    printf("Give input image name : ");
    scanf("%s",input_image);
    printf("\nGive width and height of image : ");
    scanf("%d%d",&width,&height);
    printf("\nInput Image is %s. width : %d height : %d \n",input_image,width,height);

    unsigned char input[height][width];
    bool flag[height][width];


    sprintf(out_img_name,"%s_out",input_image);
    input_image_fp= open(input_image,O_RDONLY);

    if(input_image_fp<0){
        printf("Error in opening %s image \n",input_image);
        exit(1);
    }
    output_image_fp=creat(out_img_name,0667);
    if (output_image_fp<0){
        printf("Error in creating output %s image\n",out_img_name);
        exit(1);
    }

    read(input_image_fp,&input[0][0],width*height*sizeof(unsigned char));
    close(input_image_fp);

    for (i = 0; (int)sum != 0; ++i){
        sum = 0;
        for (float p = i - 0.5; p < i + 0.5; p += 0.001) {
            sum += ( 1 / sqrt(2 * M_PI * 100) ) * exp(- ( pow(p, 2) / (2 * 100) ) ) * 0.001;
        }
        sum *= (512 * 512);
        gaussian_freq[i] = sum;
    }


    for (int j = 0; j <= i; j++) {
        while (gaussian_freq[j] != 0) {
            int pix = rand() % width;
            int scan = rand() % height;
            if (flag[scan][pix] == 1) {
                continue;
            }
            flag[scan][pix] = 1;
            int temp = (int)input[scan][pix];
            if(!(temp+j > 255)){
                input[scan][pix] += j;
            }
            gaussian_freq[j] -= 1;
        }
    }

    for (int j = -1; -j <= i; j--) {
        while (gaussian_freq[-j] != 0){
            int pix = rand() % width;
            int scan = rand() % height;
            if (flag[scan][pix] == 1){
                continue;
            }
            flag[scan][pix] = 1;
            int temp = (int)input[scan][pix];
            if(!(temp+j < 0)){
                input[scan][pix] += j;
            }
            gaussian_freq[j] -= 1;
        }
    }

    write(output_image_fp,input,width*height*sizeof(unsigned char));

    close(output_image_fp);
    printf("\n\nCompleted...\n");
    printf("%s is created.", out_img_name);
}
