#include <stdio.h>
#include <stdlib.h>

int main()
{
   int n;
   scanf("%d",&n);

   int nArr[n],i,j,x;

   for(j=0;j<n;j++)
     scanf("%d",&nArr[j]);

   for(i=1;i<n;i++){
     x=nArr[i];
     for(j=i-1;j>=0;j--)
       if(nArr[j]>x)
         nArr[j+1]=nArr[j];
       else break;
     nArr[j+1]=x;
   }

   for(j=0;j<n;j++)
     printf("%d ", nArr[j]);

   return 0;
}
