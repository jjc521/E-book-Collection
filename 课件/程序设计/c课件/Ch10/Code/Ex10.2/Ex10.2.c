#include <stdio.h>
int main()
{
    int *p1,*p2,*p,a,b;

    scanf("%d%d",&a,&b);
    p1=&a;p2=&b;

    if(a<b){
        p1=&b; p2=&a;
    }

		printf("a=%d,b=%d\n\n",a,b);
    printf("max=%d,min=%d",*p1,*p2);

    return 0;
}
