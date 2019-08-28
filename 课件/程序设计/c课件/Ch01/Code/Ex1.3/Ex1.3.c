#include <stdio.h>

int main()
{
    int a,b,c;
    printf("Enter 2 integers:");
    scanf("%d%d",&a,&b);
    c=max(a,b);
    printf("max=%d",c);

    return 0;
}

int max(int x,int y)
{
    int z;
    if(x>y)z=x;
    else z=y;

    return (z);
}
