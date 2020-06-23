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

void find_padding_length(int *);

int main(){

        char input_image[100] = "cam2_128_128.raw";
        int width = 128, height = 128;
        
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
                        fft[scan][pix].real = pow((-1), scan+pix)*((double)read_buffer[pix]);
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

        int pad = 0;
        printf("\n\nEnter pad amount : ");
        scanf("%d", &pad);
        find_padding_length(&pad);
        len = len+(pad*2);
        comp (*padded_fft)[len] = malloc(sizeof(comp[len][len]));
        initZero2(&padded_fft[0][0], len);
        for(int i=pad; i<(len-pad); i++){
                for(int j=pad; j<(len-pad); j++){
                        padded_fft[i][j] = fft[i-pad][j-pad];
                }
        }
        free(fft);

        /* Inverse FFT Part : */
        pthread_t ifft_tids[len];
        conjugate_arr(&padded_fft[0][0], len, len);
        for (int i = 0; i < len; i++) {
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_create(&ifft_tids[i], &attr, find_1d_fft, &padded_fft[i][0]);
	}
        
        for (int i = 0; i < len; i++) {
		pthread_join(ifft_tids[i], NULL);
	}
        transpose(&padded_fft[0][0], len, len);
        for (int i = 0; i < len; i++) {
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_create(&ifft_tids[i], &attr, find_1d_fft, &padded_fft[i][0]);
	}

        for (int i = 0; i < len; i++) {
		pthread_join(ifft_tids[i], NULL);
	}
        //transpose(&fft[0][0], len, len);
        hermition_arr(&padded_fft[0][0], len, len);
        
        double pix_val;
        unsigned char output[height][width];
        //unsigned char output[len][len];
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
                        pix_val = sqrt(pow(padded_fft[i][j].real,2) + pow(padded_fft[i][j].imag, 2));
                        pix_val /= (len-(2*pad))*(len-(2*pad));
                        //printf("%u ", (unsigned char)((int)round(pix_val)));
                        output[i][j] = (unsigned char)((int)round(pix_val));
                }
                //printf("\n");
        }
        //write(output_image_fp,&output[0][0],len*len*sizeof(unsigned char));
        write(output_image_fp,&output[0][0],width*height*sizeof(unsigned char));
        close(output_image_fp);
        printf("\n\nCompleted...\n");
        printf("%s is created.", out_img_name);     
        return 0;   
}

void find_padding_length(int *pad){
        int temp_len = 2*(*pad) + len;
        int final_len = (int)pow(2, ceil(log2((double)temp_len)));
        *pad = (final_len-len)/2;
}