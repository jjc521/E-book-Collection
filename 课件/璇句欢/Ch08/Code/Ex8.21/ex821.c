#include <stdio.h>

int A;
void main()
{
    int power(int);
    int b=3,c,d,m;

    printf("Enter the number a and its power m:\n");
    scanf("%d%d",&A,&m);
    c=A*b;
    printf("%d*%d=%d\n",A,b,c);
    d=power(m);
    printf("%d**%d=%d\n",A,m,d);

    getch();
}
