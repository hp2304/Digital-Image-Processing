#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <fcntl.h>
#include <malloc.h>
#include <unistd.h>

typedef struct pixel_info{
    int frq;
    unsigned char pixel_val;
}pixel_info;

int main()
{
    int input_image_fp,a;
    char input_image[100] = "boat_512_512.raw";
    int j;
    pixel_info list[256]={0}, key;
    unsigned char read_buffer[3000];
    int width = 512,height = 512,pix,scan;
    FILE *fp;
    char num[10];
    printf("Give input image name : ");
    scanf("%s",input_image);
    printf("\nGive width and height of image : ");
    scanf("%d%d",&width,&height);
    printf("\nInput Image is %s. width : %d height : %d \n",input_image,width,height);
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
            list[read_buffer[pix]].frq++;
        }
    }
    close(input_image_fp);
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
    for (int i = 1; i < 256; i++) 
    { 
        key = list[i]; 
        j = i-1; 
        while (j >= 0 && list[j].frq < key.frq) 
        { 
            list[j+1] = list[j]; 
            j = j-1; 
        } 
        list[j+1] = key; 
    } 
    for(int i=0;i<256;i++){
        printf("%d --> %d\n", list[i].pixel_val, list[i].frq);
    }
    
    return 0;
}
