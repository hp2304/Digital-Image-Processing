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
#include <sys/resource.h>
#define BLUR_FACTOR 21

void main(){

        char input_image[100] = "blurry.raw";
        int width = 256, height = 256;
        
        printf("Give input image name : ");
        scanf("%s",input_image);
        printf("\nGive width and height of image : ");
        scanf("%d%d",&width,&height);
        printf("\nInput Image is %s. width : %d height : %d \n",input_image,width,height);
        
        
        len = findSize(height, width);
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
                        fft[scan][pix].real = ((double)read_buffer[pix]);
                        fft[scan][pix].imag = 0.0;
                }
        }
        pthread_t tids[len];
        for (int i = 0; i < len; i++) {
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_create(&tids[i], &attr, find_1d_fft, &fft[i][0]);
	}

        for (int i = 0; i < len; i++) {
		pthread_join(tids[i], NULL);
	}

        transpose(&fft[0][0], len, len);
        for (int i = 0; i < len; i++) {
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_create(&tids[i], &attr, find_1d_fft, &fft[i][0]);
	}

        for (int i = 0; i < len; i++) {
		pthread_join(tids[i], NULL);
	}
        transpose(&fft[0][0], len, len);
        // FFT of input image computed
//----------------------------------------------------------------------------------------------------
        double psf[BLUR_FACTOR] = {0};
        comp *psf_ft = calloc(len, sizeof(comp));
        for(int i=0; i<BLUR_FACTOR; ++i){
                psf[i] = (1/(double)BLUR_FACTOR);
                psf_ft[i].real = psf[i];
                psf_ft[i].imag = 0.0;
        }
        
        for (int i = 0; i < 1; i++) {
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_create(&tids[i], &attr, find_1d_fft, &psf_ft[0]);
	}

        for (int i = 0; i < 1; i++) {
		pthread_join(tids[i], NULL);
	}
        // FFT of point spread function is computed.
//-----------------------------------------------------------------------------------------------------
        for(int i=0; i<len; ++i){
                for(int j=0; j<len; ++j){
                        fft[i][j] = div_comp_nums(fft[i][j], psf_ft[j]);
                }
        }
        // Divide by the fourier transfor of psf
//------------------------------------------------------------------------------------------------------
        //Inverse FFT Part : 
         
        conjugate_arr(&fft[0][0], len, len);
        for (int i = 0; i < len; i++) {
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_create(&tids[i], &attr, find_1d_fft, &fft[i][0]);
	}

        for (int i = 0; i < len; i++) {
		pthread_join(tids[i], NULL);
	}
        transpose(&fft[0][0], len, len);
        for (int i = 0; i < len; i++) {
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_create(&tids[i], &attr, find_1d_fft, &fft[i][0]);
	}

        for (int i = 0; i < len; i++) {
		pthread_join(tids[i], NULL);
	}
        hermition_arr(&fft[0][0], len, len);
        
        double pix_val;
        unsigned char output[height][width];
        char out_img_name[100];

        sprintf(out_img_name,"%s_out",input_image);
        int output_image_fp=creat(out_img_name,0667);
        if (output_image_fp<0)
        {
                printf("Error in creating output %s image\n",out_img_name);
                exit(1);
        }
        for(int i=0;i<height;i++){
                for(int j=0;j<width;j++){
                        pix_val = fft[i][j].real;
                        pix_val /= len;
                        pix_val /= len;
                        if(round(pix_val) > 255){
                                output[i][j] = 255;
                        }
                        else if(round(pix_val) < 0){
                                output[i][j] = 0;
                        }
                        else
                        {
                                output[i][j] = (unsigned char)((int)round(pix_val));
                        }
                        //printf("%d ", ((int)round(pix_val)));
                }
                //printf("\n");
        }
        write(output_image_fp,&output[0][0],width*height*sizeof(unsigned char));
        close(output_image_fp);
        printf("\n\nCompleted...\n");
        printf("%s is created.", out_img_name);
        free(fft);
}