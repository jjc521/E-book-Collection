#include <stdio.h>
printstar()
{
    printf("********************\n");
}
print_message()
{
    printf("   How do you do!\n");
}

void main()
{
    int a=0,b=0,c=0;

    a=printstar();
    b=print_message();
    c=printstar();

    printf("%d %d %d\n",a,b,c);
    getch();
}
