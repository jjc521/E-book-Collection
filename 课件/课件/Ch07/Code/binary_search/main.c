#include <stdio.h>
#include <stdlib.h>

int main() {
  int nArr[]= {10,20,30,40,50,60,70,80,90,100},x,l=0,h=sizeof(nArr)/sizeof(nArr[0]),m,k=-100;

  scanf("%d",&x);
  for(; l<=h;) {
    m=(l+h)/2;
    if(x==nArr[m]) {
      k=m;
      break;
    }
    if(x<nArr[m])h=m-1;
    else l=m+1;
  }
  if(l>h) k=-1;

  printf("%d", k);

  return 0;
}
