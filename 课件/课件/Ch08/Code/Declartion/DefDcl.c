#include <stdio.h>
float add(float x,float y)
{
    float z;

    z=x+y;

    return z;
}
void main()
{
    float a,b,c;

    scanf("%f%f",&a,&b);
    c=add(a,b);
    printf("sum is %f",c);

    getch();
}
