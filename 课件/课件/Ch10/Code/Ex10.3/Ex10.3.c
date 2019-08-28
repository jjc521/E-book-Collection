#include <stdio.h>

void swap(int *p1,int *p2)
{
    int temp;

    temp=*p1;
    *p1=*p2;
    *p2=temp;
}

int main()
{
    int a,b;
    int *pointer_1,*pointer_2;

    scanf("%d%d",&a,&b);
    pointer_1=&a;pointer_2=&b;

    if(a<b)
       swap(pointer_1,pointer_2);
    printf("\n%d %d",a,b);

    return 0;
}
