#include <stdio.h>
void main()
{
    int a,b,c;

    scanf("%d%d",&a,&b);
    c=max(a,b);
    printf("max is %d\n",c);

    getch();
}

int max(int x,int y)
{
    return x>y?x:y;
}
