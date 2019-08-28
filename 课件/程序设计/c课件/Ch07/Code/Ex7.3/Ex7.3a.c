#include <stdio.h>
int main(){
    int a[11];
    int i,j,t,f;

    printf("Input 10 numbers:\n");
    for(i=1;i<11;i++)
      scanf("%d",&a[i]);
    printf("\n");
    for(j=1;j<=9;j++){
        f=0;
        for(i=1;i<=10-j;i++)
          if(a[i]>a[i+1])
          {
              t=a[i];
              a[i]=a[i+1];
              a[i+1]=t;
              f=1;
          }
        if(f==0)break;
    }
    for(i=1;i<=10;i++)
       printf("%d ",a[i]);

     return 0;
}
