#include <stdio.h>

int main()
{
    int *p,i,a[10];

    p=a;
    for(i=0;i<10;i++)
      scanf("%d",p++);
    printf("\n");
    for(i=0;i<10;i++,p++)
      printf("%d ",*p);

    return 0;
}
