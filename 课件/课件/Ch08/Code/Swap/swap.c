#include <stdio.h>

int swap(int x,int y){
    int t;

    t=x; x=y; y=t;

    return 0;
}

void main(){
    int a=2,b=3;

    swap(a,b);
    printf("a=%d,b=%d",a,b);

    getch();
}
