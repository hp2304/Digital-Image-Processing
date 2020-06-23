#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <fcntl.h>
#include <malloc.h>
#include <unistd.h>
#include <string.h>
#include "fft_dp.h"
#include <float.h>
#include "utils.h"


void main(){
        
        char input_image[100] = "boat_512_512.raw";
        int width = 512, height = 512;
        
        printf("Give input image name : ");
        scanf("%s",input_image);
        printf("\nGive width and height of image : ");
        scanf("%d%d",&width,&height);
        printf("\nInput Image is %s. width : %d height : %d \n",input_image,width,height);
        
        
        int len = findSize(height, width);
        comp (*fft)[len] = malloc(sizeof(comp[len][len]));
        
        initZero2(&fft[0][0], len);

        unsigned char read_buffer[width];
        int input_image_fp= open(input_image,O_RDONLY);
        if (input_image_fp<0)
        {
                printf("Error in opening %s image \n",input_image);
                exit(1);
        }

        for (int scan=0;scan<height;scan++){
                read(input_image_fp,&read_buffer[0],width*sizeof(unsigned char));
                for (int pix=0;pix<width;pix++){
                        fft[scan][pix].real = pow((-1), scan+pix)*((double)read_buffer[pix]);
                        //fft[scan][pix].real = ((double)read_buffer[pix]);
                        fft[scan][pix].imag = 0.0;
                }
                find_1d_fft(&fft[scan][0], len);
        }
        transpose(&fft[0][0], len, len);
        for(int i=0;i<len;i++){
                find_1d_fft(&fft[i][0], len);
        }
        transpose(&fft[0][0], len, len); 
        for(int i=0;i<len;i++){
            for(int j=0;j<len;j++){
                printf("(%lf %lf) ", fft[i][j].real, fft[i][j].imag);
            }
            printf("\n");
        }



}
