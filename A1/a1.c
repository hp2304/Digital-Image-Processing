#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct char_info{
    int frq;
    char character;
}char_info;

int main(int argc, char const *argv[]){
    char_info list[128] = {0};
    char filename[20];
    printf("Enter file name : ");
    scanf("%s", filename);
    FILE *file = fopen(filename, "r");
    int num_distinct_chars = 0;
    int c, flag;
    char_info key; 
    int j;

    if (file == NULL)
        printf("Can't open file");

    while ((c = fgetc(file)) != EOF)
    {
        flag = 1;
        for(int i=0;i<num_distinct_chars;i++){
            if(list[i].character == (char)c){
                flag = 0;
                list[i].frq++;
                break;
            }
        }
        if(flag){
            list[num_distinct_chars].character = (char) c;
            list[num_distinct_chars].frq++;
            num_distinct_chars++;
        }
        
    } 
    fclose(file);
    /*for(int j=0;j<num_distinct_chars;j++){
        printf("%c", list[j].character);
    }
    printf("\n\n%d\n\n", num_distinct_chars);
    */
    for (int i = 1; i < num_distinct_chars; i++) 
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
    for(int i=0;i<num_distinct_chars;i++){
        if((int)list[i].character == 32){
            printf("SPACE --> %d\n", list[i].frq);
            continue;
        }
        if((int)list[i].character == 13){
            printf("CARRIAGE RETURN --> %d\n", list[i].frq);
            continue;
        }
        if((int)list[i].character == 10){
            printf("NEW LINE --> %d\n", list[i].frq);
            continue;
        }
        printf("%c --> %d\n", list[i].character, list[i].frq);
    }
    return 0;
}

