#include <stdio.h>

int main()
{
    char a[]="I am a boy.",b[20],*p1,*p2;
    int i;

    p1=a;p2=b;
    for(;*p1!='\0';p1++,p2++)
      *p2=*p1;
    *p2='\0';
    printf("string a is: %s\n",a);
    printf("string b is: ");
    for(i=0;b[i]!='\0';i++)
      printf("%c",b[i]);
    printf("\n");

    return 0;
}
