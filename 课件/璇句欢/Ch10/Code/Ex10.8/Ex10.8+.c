#include <stdio.h>

int max,min;

void max_min_value(int *array,int n)
{
    int *p,*array_end;

    array_end = array + n;
    max = min = *array;
    for(p=array+1;p<array_end;p++)
      if(*p>max)
         max = *p;
      else
         if(*p < min)
           min = *p;
}

void main()
{
    int i,number[10],*p;

    p=number;
    printf("Enter 10 integer numbers:");
    for(i=0;i<10;i++,p++)
      scanf("%d",p]);
    p=number;
    max_min_value(number,10);
    printf("\nmax=%d,min=%d",max,min);
    getch();
}
