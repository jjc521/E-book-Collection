#include <stdio.h>
#include <stdlib.h>

int main() {
  int n;

  scanf("%d",&n);

  int nArr[n],i,j,k,t;

  for (i=0; i<n; i++)
    scanf("%d",&nArr[i]);

  for(i=0; i<n-1; i++) {
    k=i;
    for(j=i; j<n; j++)
      if(nArr[k]>nArr[j])
        k=j;
    t=nArr[i];
    nArr[i]=nArr[k];
    nArr[k]=t;
  }

  for(i=0; i<n; i++)
    printf("%d ", nArr[i]);

  return 0;
}
