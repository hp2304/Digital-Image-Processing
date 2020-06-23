#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <fcntl.h>
#include <malloc.h>
#include <unistd.h>
#include <math.h>

typedef struct pixel_info{
    int frq;
    double cum_prob;
}pixel_info;

int main(int argc, char* argv)
{
    int input_image1_fp,output_image_fp,a;
    char input_image1[100]="lenna_512_512.raw", output_image[100];
    pixel_info list_1[256]={0}, key;
    unsigned char max_val=0;
    int width=512,height=512,pix,scan;
    double sum = 0;
    
    printf("Give input image name : ");
    scanf("%s",input_image1);
    printf("\nGive width and height of image : ");
    scanf("%d%d",&width,&height);
    
    int num_pixels = width*height;
    unsigned char read_buffer1[width], write_buffer[width];
    input_image1_fp= open(input_image1,O_RDONLY);
    if (input_image1_fp<0)
    {
        printf("Error in opening %s image \n",input_image1);
        exit(1);
    }
    for (scan=0;scan<height;scan++)
    {
        read(input_image1_fp,&read_buffer1[0],width*sizeof(unsigned char));
        for (pix=0;pix<width;pix++)
        {
            
            if(read_buffer1[pix] > max_val){
                max_val = read_buffer1[pix];
            }
            list_1[read_buffer1[pix]].frq++;
        }
    }
    close(input_image1_fp);

    for(int i=0;i<256;i++){
        sum += list_1[i].frq;
        list_1[i].cum_prob = sum/num_pixels;
    }

//----------------------------------------------------
    pixel_info list_2[256] = {0};
    max_val = 0;
    sum=0;
    char input_image2[100] = "boat_512_512.raw";
    int input_image2_fp;
    
    printf("\n\nGive target image name : ");
    scanf("%s",input_image2);
    printf("\nGive width and height of image : ");
    scanf("%d%d",&width,&height);
    
    num_pixels = width*height;
    unsigned char read_buffer2[width];
    input_image2_fp= open(input_image2,O_RDONLY);
    if (input_image2_fp<0)
    {
        printf("Error in opening %s image \n",input_image2);
        exit(1);
    }
    for (scan=0;scan<height;scan++)
    {
        read(input_image2_fp,&read_buffer2[0],width*sizeof(unsigned char));
        for (pix=0;pix<width;pix++)
        {
            
            if(read_buffer2[pix] > max_val){
                max_val = read_buffer2[pix];
            }
            list_2[read_buffer2[pix]].frq++;
        }
    }
    close(input_image2_fp);
    
    for(int i=0;i<256;i++){
        sum += list_2[i].frq;
        list_2[i].cum_prob = sum/num_pixels;
    }
//------------------------------------------------------------------------
    input_image1_fp= open(input_image1,O_RDONLY);
    if (input_image1_fp<0)
    {
        printf("Error in opening %s image \n",input_image1);
        exit(1);
    }
    sprintf(output_image,"%s_out",input_image1);
    output_image_fp=creat(output_image,0667);
    if (output_image_fp<0){
        printf("Error in creating output %s image\n",output_image);
        exit(1);
    }
    unsigned char start=0;
    unsigned char map[256];
    for(int i=0;i<256;i++){
        for(int j=start;j<256;j++){
            if(list_2[j].cum_prob > list_1[i].cum_prob){
                map[i] = j-1;
                start = map[i];
                break;
            }
        }
     }
    
    for (scan=0;scan<height;scan++)
    {
        read(input_image1_fp,&read_buffer1[0],width*sizeof(unsigned char));
        for (pix=0;pix<width;pix++)
        {
            write_buffer[pix] = map[read_buffer1[pix]];
        }
        write(output_image_fp,&write_buffer[0],width*sizeof(unsigned char));
    }
    close(input_image1_fp);
    close(output_image_fp);

    printf("\n");
    
    for(int i=0;i<256;i++){
        printf("%d %f %f \n", i, list_1[i].cum_prob, list_2[i].cum_prob);
    }
    return 0;
}
