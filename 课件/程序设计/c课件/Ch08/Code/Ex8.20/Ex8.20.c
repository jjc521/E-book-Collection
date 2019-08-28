#include <stdio.h>

int max(int x,int y)
{
    int z;
    z=x>y?x:y;
    return z;
}
int main()
{
    extern int A,B;
    printf("%d\n",max(A,B));

    return 0;
}
int A=13,B=-8;
