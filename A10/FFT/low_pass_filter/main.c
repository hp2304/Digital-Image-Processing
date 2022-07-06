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

//void store_mag(comp *, int, char[]);
int rad = 0;
typedef struct row_info
{
        comp *ptr;
        int idx;
}row_info;

void* apply_filter(void *);

void* apply_filter(void *arg){
    row_info *arr = (row_info *)arg;
    comp *inp = arr->ptr;
    int idx = arr->idx;
    for(int i=0;i<len;i++){
        if((pow(i-(len/2), 2) + pow(idx-(len/2), 2)) > pow(rad, 2)){
                comp temp = {0};
                *(inp+i) = temp;
        }
    }
    pthread_exit(0);
}

void main(){

        char input_image[100] = "test_255_300.raw";
        int width = 255, height = 300;
        
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

        printf("\nEnter the radius : ");
        scanf("%d", &rad);
        for (int i = 0; i < len; i++) {
		pthread_attr_t attr;
		pthread_attr_init(&attr);
                row_info row_selector = {&fft[i][0], i};
		pthread_create(&tids[i], &attr, apply_filter, &row_selector);
	}

        for (int i = 0; i < len; i++) {
		pthread_join(tids[i], NULL);
	}

        /* Inverse FFT Part : */
         
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
        //transpose(&fft[0][0], len, len);
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
                        pix_val = fft[i][j].real * pow((-1), i+j);
                        pix_val /= len;
                        pix_val /= len;
                        //printf("%u ", (unsigned char)((int)round(pix_val)));
                        output[i][j] = (unsigned char)((int)round(pix_val));
                }
                //printf("\n");
        }
        write(output_image_fp,&output[0][0],width*height*sizeof(unsigned char));
        close(output_image_fp);
        printf("\n\nCompleted...\n");
        printf("%s is created.", out_img_name);   
        free(fft);     
}
/*
void store_mag(comp *fft, int len, char inp_img_name[]){

        char out_img_name[100];
        int output_image_fp;
        double max,min;
        sprintf(out_img_name,"%s_out",inp_img_name);
        printf("\nOutput Image is %s width : %d height : %d \n\n",out_img_name,len,len);
        output_image_fp=creat(out_img_name,0667);
        max=0;
        min=DBL_MAX;
        comp val;
        for(int i=0;i<len;i++){
                for(int j=0;j<len;j++){
                        if(j>i){
                                val = *((fft + (i*len)) + j);
                                *((fft + i*len) + j) = *((fft + j*len) + i);
                                *((fft + j*len) + i) = val;
                        }
                        val = *((fft + (i*len)) + j);
                        val.real = sqrt(pow(val.real, 2)+pow(val.imag, 2));
                        *((fft + (i*len)) + j) = val;
                        if(max < val.real){
                                max=val.real;
                        }
                        if(min > val.real){
                                min=val.real;
                        }
                }
        }
        unsigned char mag_ft[len][len];
        max=log10(1+max);
        min=log10(1+min);
        double temp;
        for(int i=0;i<len;i++){
                for(int j=0;j<len;j++){
                        val = *((fft + (i*len)) + j);
                        temp = log10(1 + val.real);
                        temp = round(255*((temp-min)/(max - min)));
                        if(temp<=255){
                                mag_ft[i][j] = (unsigned char)temp;
                        }
                        else
                        {
                                mag_ft[i][j] = 255;
                        }
                
                }
        }
        write(output_image_fp,&mag_ft[0][0],len*len*sizeof(unsigned char));
        close(output_image_fp);
        printf("\n\nCompleted...\n");
}*/
