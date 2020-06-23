#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <fcntl.h>
#include <malloc.h>
#include <unistd.h>
#include <math.h>

typedef struct pixel_info{
    int frq;
    unsigned char pixel_val;
    unsigned char maped_val;
}pixel_info;

void write_hist(pixel_info arr[]);

int main(int argc, char* argv)
{
    int input_image_fp,output_image_fp,a;
    char input_image[100], output_image[100];
    pixel_info list[256]={0}, key;
    unsigned char min_val=255, max_val=0;
    int width,height,pix,scan;
    double sum = 0;
    printf("Give input image name : ");
    scanf("%s",input_image);
    printf("\nGive width and height of image : ");
    scanf("%d%d",&width,&height);
    int num_pixels = width*height;
    unsigned char read_buffer[width], write_buffer[width];
    input_image_fp= open(input_image,O_RDONLY);
    if (input_image_fp<0)
    {
        printf("Error in opening %s image \n",input_image);
        exit(1);
    }
    for(int k=0;k<256;k++){
        list[k].pixel_val = k;
    }
    for (scan=0;scan<height;scan++)
    {
        read(input_image_fp,&read_buffer[0],width*sizeof(unsigned char));
        for (pix=0;pix<width;pix++)
        {
            
            if(read_buffer[pix] > max_val){
                max_val = read_buffer[pix];
            }
            if(read_buffer[pix] < min_val){
                min_val = read_buffer[pix];
            }
            list[read_buffer[pix]].frq++;
        }
    }
    close(input_image_fp);
    write_hist(list);

    
    for(int i=0;i<256;i++){
        sum += list[i].frq;
        //printf("%f \n", (sum*max_val)/num_pixels);
        list[i].maped_val = (unsigned char) round((sum*max_val)/num_pixels);
    }
    input_image_fp= open(input_image,O_RDONLY);
    if (input_image_fp<0)
    {
        printf("Error in opening %s image \n",input_image);
        exit(1);
    }
    sprintf(output_image,"%s_out",input_image);
    output_image_fp=creat(output_image,0667);
    if (output_image_fp<0){
        printf("Error in creating output %s image\n",output_image);
        exit(1);
    }
    for (scan=0;scan<height;scan++)
    {
        read(input_image_fp,&read_buffer[0],width*sizeof(unsigned char));
        for (pix=0;pix<width;pix++)
        {
             write_buffer[pix] = list[read_buffer[pix]].maped_val;
        }
        write(output_image_fp,&write_buffer[0],width*sizeof(unsigned char));
    }
    close(input_image_fp);
    close(output_image_fp);
    /*for(int j=0;j<256;j++){
        printf("%u %d %u\n", list[j].pixel_val, list[j].frq, list[j].maped_val);
    }*/
    return 0;
}

void write_hist(pixel_info list[256]){
    FILE *fp;
    char num[10];

    fp = fopen("img_hist.txt","w");
    if (fp<0)
    {
        printf("Error in creating file img_hist.txt\n");
        exit(1);
    }
    for(int i=0;i<256;i++){
        sprintf(num, "%d", list[i].pixel_val);
        fputs(num,fp);
        fputs(" ", fp);
        num[0] = '\0';
        sprintf(num, "%d", list[i].frq);
        fputs(num,fp);
        fputs("\n", fp);
        num[0] = '\0';
    }
    fclose(fp);
}
