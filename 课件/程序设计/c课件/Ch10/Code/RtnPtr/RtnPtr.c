#include <stdio.h>

int *f()
{
    int t;
    return &t;
}

void main()
{
    int *p;

    p=f();
    *p=100;
    printf("%d\n",*p);
    getch();
}
