#include <stdio.h>
void main(){
    float a,b,c,t;
    printf("Enter 3 numbers:");
    scanf("%f%f%f",&a,&b,&c);
    if(a>b)
    {t=a;a=b;b=t;}
    if(a>c)
    {t=a;a=c;c=t;}
    if(b>c)
    {t=b;b=c;c=t;}

    printf("%5.2f %5.2f %5.2f",a,b,c);
}
