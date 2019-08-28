#include <stdio.h>

void max_min_value(int *array,int n,int *max,int *min)
{
    int *p,*array_end;

    array_end = array + n;
    *max = *min = *array;
    for(p=array+1;p<array_end;p++)
      if(*p > *max)
         *max = *p;
      else
         if(*p < *min)
           *min = *p;
}

int main()
{
    int i,number[10],mx,mn;

    printf("Enter 10 integer numbers:");
    for(i=0;i<10;i++)
      scanf("%d",&number[i]);
    max_min_value(number,10,&mx,&mn);
    printf("\nmax=%d,min=%d",mx,mn);

    return 0;
}
