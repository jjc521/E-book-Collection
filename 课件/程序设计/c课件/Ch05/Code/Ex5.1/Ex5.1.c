#include <stdio.h>
int main(){
    float a,b,t;
    printf("Enter two numbers:");
    scanf("%f%f",&a,&b);
    if(a>b)
    {
        t=a;
        a=b;
        b=t;
    }
    printf("%f %f",a,b);

    return 0;
}
