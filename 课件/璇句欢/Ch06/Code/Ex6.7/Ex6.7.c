#include <stdio.h>
void main(){
    int i;
    long f1,f2,f3;

    f1=1;f2=1;
    printf("%ld %ld ",f1,f2);
    for(i=3;i<=40;i++)
    {
        f3=f1+f2;
        printf("%ld ",f3);
        f1=f2;f2=f3;
    }
    getch();
}
