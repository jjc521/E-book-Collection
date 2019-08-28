#include <stdio.h>
void main(){
    int n;

    for(n=100;n<=200;n++)
    {
        if(n%3==0)
           continue;
        printf("%d ",n);
    }
    getch();
}
