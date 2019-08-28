#include <stdio.h>

void main()
{
    int a[10],*p,i;

    p=a;
    for(i=0;i<10;i++)
     scanf("%d",p+i);
    printf("\n");
    for(i=0;i<10;i++)
      printf("%d ",p[i]);
    getch();
}
