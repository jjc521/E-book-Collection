#include <stdio.h>

int max(int x,int y)
{
    return x>y?x:y;
}

void main()
{
    int (*pf)(int,int);

    pf=max;
    printf("%d",pf(10,100));
    getch();
}
