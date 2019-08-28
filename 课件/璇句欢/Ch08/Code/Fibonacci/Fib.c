#include <stdio.h>

long Fib(int i)
{
    if(i==1 || i==2)
       return 1;
    return Fib(i-1) + Fib(i-2);
}
void main()
{
    int n;

    for(n=1;n<=20;n++)
    {
        printf("%ld ",Fib(n));
        if(n%5==0)
          printf("\n");
    }
    getch();
}
