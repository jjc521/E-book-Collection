#include <stdio.h>
int main()
{
    long f1,f2;
    int i;

    f1=1;f2=1;
    for(i=1;i<=20;i++)
    {
        printf("%ld %ld ",f1,f2);
        f1=f1+f2;
        f2=f1+f2;
    }

    return 0;
}
