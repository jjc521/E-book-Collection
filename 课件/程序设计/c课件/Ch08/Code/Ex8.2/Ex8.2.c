#include <stdio.h>
int main()
{
    int a,b,c;

    scanf("%d%d",&a,&b);
    c=max(a,b);
    printf("Max is %d\n",c);

    return 0;
}

int max(int x,int y)
{
    int z;

    z=x>y?x:y;

    return z;
}
