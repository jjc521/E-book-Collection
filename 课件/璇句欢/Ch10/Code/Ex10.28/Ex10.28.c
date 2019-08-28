#include <stdio.h>
void main()
{
    char * name[]={"Follow me","Basic","Great Wall","Fortran","Computer design"};
    char **p;
    int i;

    for(i=0;i<5;i++)
    {
        p=name+i;
        printf("%s\n",*p);
    }

    getch();
}
