#include <stdio.h>

int fac(int n)
{
  static int f=1;

  f=f*n;
  return f;
}

void main()
{
  int i;

  for(i=1;i<=5;i++)
    printf("%d!=%d\n",i,fac(i));

  getch();
}
