#include <stdio.h>
int main(){
    float add(float x,float y);    /*对被调用函数的声明*/
    float a,b,c;

    scanf("%f%f",&a,&b);
    c=add(a,b);
    printf("sum is %f",c);

    return 0;
}

float add(float x,float y){
    float z;

    z=x+y;

    return z;
}
