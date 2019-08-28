#include <stdio.h>

int a=3,b=5;
int max(int a,int b)
{
 int c;

  c=a>b?a:b;
  return c;
}

void main()
{
 int a=8;

  printf("%d",max(a,b));

  getch();
}
