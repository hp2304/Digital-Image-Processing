#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <fcntl.h>
#include <malloc.h>
#include <unistd.h>
#include <string.h>

void find_mappings(unsigned char *mappings, double gamma);

void main()
{
    int input_image_fp,output_image_fp,a;
    char input_image[100] = "babyincradle_blue.raw",output_image[100];
    int width = 663,height = 497,pix,scan;
    
    printf("Give input image name : ");
    scanf("%s",input_image);
    printf("\nGive width and height of image : ");
    scanf("%d%d",&width,&height);
    printf("\nInput Image is %s. width : %d height : %d \n",input_image,width,height);
    unsigned char read_buffer[width],write_buffer[width];

    sprintf(output_image,"%s_out",input_image);
    input_image_fp= open(input_image,O_RDONLY);
    if (input_image_fp<0)
    {
        printf("Error in opening %s image \n",input_image);
        exit(1);
    }
    output_image_fp=creat(output_image,0667);
    if (output_image_fp<0)
    {
        printf("Error in creating output %s image\n",output_image);
        exit(1);
    }

    double gamma = 1;
    printf("\nEnter gamma value : ");
    scanf("%lf", &gamma);

    unsigned char mappings[256] = {0};
    find_mappings(mappings, gamma);
    for (scan=0;scan<height;scan++)
    {
        read(input_image_fp,&read_buffer[0],width*sizeof(unsigned char));
        for (pix=0;pix<width;pix++)
        {
            write_buffer[pix]=mappings[read_buffer[pix]];
        }
        write(output_image_fp,&write_buffer[0],width*sizeof(unsigned char));
    }
    
    close(input_image_fp);
    close(output_image_fp);
    printf("\nOutput Image is %s. width : %d height : %d \n\n",output_image,width,height);
}

void find_mappings(unsigned char *mappings, double gamma){
    int len = 256;
    double invGamma = (1/gamma);
    for(int i=0;i<len;i++){
        *(mappings + i) = (unsigned char)(255*pow(i/(double)255, invGamma));    
    }
}