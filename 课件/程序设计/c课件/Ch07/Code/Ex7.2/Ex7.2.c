#include <stdio.h>
int main()
{
    int i;
    long f[40]={1,1};

    for(i=2;i<40;i++)
      f[i]=f[i-1]+f[i-2];

    for(i=0;i<40;i++)
    {
        if(i%5==0)printf("\n");
        printf("%12ld ",f[i]);
    }
    printf("\n");

    return 0;
}
