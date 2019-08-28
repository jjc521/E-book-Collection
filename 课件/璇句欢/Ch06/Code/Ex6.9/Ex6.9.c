#include <stdio.h>
#include <math.h>
void main(){
    int m,i,k,n=0;
    for(m=101;m<=200;m=m+2)
    {
        k=sqrt(m);
        for(i=2;i<=k;i++)
          if(m%i==0)break;
        if(i>k)printf("%d ",m);
    }
    getch();
}
