#include <stdio.h>

void move(char x,char y)
{
  printf("\n%c --> %c",x,y);
}

void hanoi(int n,char one,char two,char three)
{
  if(n==1) move(one,three);
  else
  {
    hanoi(n-1,one,three,two);
    move(one,three);
    hanoi(n-1,two,one,three);
  }
}

void main()
{
  int m;

  printf("\nInput the number of disks:");
  scanf("%d",&m);
  printf("\nThe step to moving %3d disks:\n");
  hanoi(m,'A','B','C');

  getch();
}

