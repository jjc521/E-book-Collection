#include <stdio.h>
void main(){
    char grade;
    printf("Enter Grade:");
    scanf("%c",&grade);
    switch(grade)
    {
        case 'A':printf("90~100\n");
        case 'B':printf("80~89\n");
        case 'C':printf("70~80\n");
        case 'D':printf("60~69\n");
        case 'E':printf("<60\n");
        default:printf("error\n");
    }

    getch();
}
