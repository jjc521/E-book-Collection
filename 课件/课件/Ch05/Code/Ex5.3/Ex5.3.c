#include <stdio.h>
/*/*
void main(){
    int x,y;
    printf("Enter x:");
    scanf("%d",&x);
    if(x>0)y=1;
    else if(x==0)y=0;
    else y=-1;

    printf("%d",y);
}
*/
/**/
int  main(){
    int x,y;

    printf("Enter x:");
    scanf("%d",&x);
    if(x>=0)
      if(x>0)y=1;
      else y=0;
    else y=-1;
    printf("%d",y);

    return 0;
}
/**/
