#include <stdio.h>
void main()
{
    int a,b,c;

    scanf("%d%d",&a,&b);
    c=max(a,b);
    printf("Max is %d\n",c);
    getch();
}

int max(int x,int y)
{
    int z;

    z=x>y?x:y;

    return z;
}
