#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <fcntl.h>
#include <malloc.h>
#include <unistd.h>
#include <string.h>

void main()
{
    int input_image_fp,output_image_fp,a;
    char input_image[100],output_image[100];
    unsigned char read_buffer[1000],write_buffer[1000];
    int width,height,pix,scan;
    printf("Give input image name : ");
    scanf("%s",input_image);
    printf("\nGive width and height of image : ");
    scanf("%d%d",&width,&height);
    printf("\nInput Image is %s. width : %d height : %d \n",input_image,width,height);
    sprintf(output_image,"%s_v_out",input_image);
    printf("\nOutput Image is %s. width : %d height : %d \n\n",output_image,width,height);
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
    for (scan=0;scan<height;scan++)
    {
        lseek(input_image_fp, width*(height-1-scan), SEEK_SET);
        read(input_image_fp,&read_buffer[0],width*sizeof(unsigned char));
        for (pix=0;pix<width;pix++)
        {
            
            a=(int)read_buffer[pix];
            write_buffer[pix]=(unsigned char)a;
        }
        write(output_image_fp,&write_buffer[0],width*sizeof(unsigned char));
    }
    
    close(input_image_fp);
    close(output_image_fp);
}