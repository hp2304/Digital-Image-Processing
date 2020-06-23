#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct char_info
{
    int frq;
    char character;
}char_info;

void change(char_info *something);

int main(int argc, char const *argv[])
{
   
    char *filename;
    printf("Enter file name : ");
    scanf("%s", filename);
    printf("%s", filename);
    FILE *file = fopen(filename, "r");
    fclose(file);
    return 0;
}

void change(char_info *something){
    something->character = 'b';
    something->frq = 11;
}
