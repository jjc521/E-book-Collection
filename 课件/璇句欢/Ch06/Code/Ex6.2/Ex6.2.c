#include <stdio.h>
void main(){
    int i,sum=0;

    i=1;
    while(i<=100)
    {
        sum=sum+i;
        i++;
    }

    printf("%d",sum);
    getch();
}
