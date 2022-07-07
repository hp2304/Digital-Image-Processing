#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <fcntl.h>
#include <malloc.h>
#include <unistd.h>
#include <string.h>
#include "fct_dp.h"
#include <float.h>
#include "utils.h"

//void store_mag(comp *, int, char[]);

void main(){

        char input_image[100] = "test_255_300.raw";
        int width = 255, height = 300;
        
        printf("Give input image name : ");
        scanf("%s",input_image);
        printf("\nGive width and height of image : ");
        scanf("%d%d",&width,&height);
        printf("\nInput Image is %s. width : %d height : %d \n",input_image,width,height);
        
        len = findSize(height, width);
        comp (*fct)[len] = malloc(sizeof(comp[len][len]));
        initZero2(&fct[0][0], len);
        
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
                        fct[scan][pix].real = ((double)read_buffer[pix]);
                        fct[scan][pix].imag = 0.0;
                }
        }
        
        pthread_t tids[len];
        for (int i = 0; i < len; i++) {
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_create(&tids[i], &attr, find_1d_fct, &fct[i][0]);
	}

        for (int i = 0; i < len; i++) {
		pthread_join(tids[i], NULL);
	}
        
        transpose(&fct[0][0], len, len);
        for (int i = 0; i < len; i++) {
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_create(&tids[i], &attr, find_1d_fct, &fct[i][0]);
	}

        for (int i = 0; i < len; i++) {
		pthread_join(tids[i], NULL);
	}
        transpose(&fct[0][0], len, len);
        for(int i=0; i<len; i++){
                printf("%lf \n", fct[i][0].real);
        }
        free(fct); 
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
