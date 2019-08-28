#include <stdio.h>
#include <conio.h>
/**/
void main()
{
    unsigned int a=65535;
    int b=-2;

    char c = 'A';
    float x=111111.111,y=222222.222;
    double dx=1111111111111.111111111,dy=2222222222222.222222222;

    printf("\n\n\n");
    printf("a=%d  %o  %x  %X  %u\n",a,a,a,a,a);
    printf("b=%d  %o  %x  %X  %u\n",b,b,b,b,b);
    getch();

    printf("%c\n",c);
    printf("%s\n","ABCDEFGabcdefg");
    printf("%f %e %E %g %G\n",123.456,123.456,123.456,123.456,123.456);
    getch();

    printf("%f\n",x+y);
    printf("%f\n",dx+dy);
    getch();
}
/**/
/*/
int main()
{
    int a=3;
    printf("\n\n\n");
    printf("12345678901234567890\n");
    printf("%d %4d %-4d\n",a,a,a);
    printf("%ld %d \n",65535,65535);
    printf("%10s %-10s\n","ABCDE","ABCDE");
    getch();
    printf("%10.3s %-10.3s\n","China","China");
    getch();
    printf("f: %10.3f %-10.3f\n",123.456,123.456);
    printf("e: %10.3e %-10.3e\n",123.456,123.456);
    getch();
    return 0;
}
/**/
