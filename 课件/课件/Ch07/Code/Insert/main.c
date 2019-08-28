#include <stdio.h>
#include <stdlib.h>
int main() {
  int nArr[10]= {1,5,6,7},j,n=3,x;

  scanf("%d", &x);

  for(j=n; j>=0; j--)
    if(nArr[j]>x)
      nArr[j+1]=nArr[j];
    else break;
  nArr[j+1]=x;

  for (j=0; j<=n+1; j++)
    printf("%d ", nArr[j]);

  return 0;
}
