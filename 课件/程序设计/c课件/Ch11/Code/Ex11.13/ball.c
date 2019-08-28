#include <stdio.h>
int main(){
  enum clrTbl{red,yellow,blue,white,black};
  char *color[]={"Red","Yellow","Blue","White","Black"};
  enum clrTbl i,j,k;
  int n=0;

  for (i=red;i<=black;i++)
    for (j=red;j<=black;j++)
    if (i!=j){
      for (k=red;k<=black;k++)
        if (k!=i && k!=j){
          n++;
          printf("%d: %s  %s  %s\n",n,color[i],color[j],color[k]);
        }
    }
  
  return 0;
}
