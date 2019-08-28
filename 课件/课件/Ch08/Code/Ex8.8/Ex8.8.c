#include <stdio.h>
float fac(int n)
{
    float f;

    if(n==0 || n==1)
      return 1;
    return n*fac(n-1);
}

int main()
{
    int n;
    float y;

    printf("input a integer number:");
    scanf("%d",&n);
    y=fac(n);
    printf("%d!=%.0f",n,y);

    return 0;
}
