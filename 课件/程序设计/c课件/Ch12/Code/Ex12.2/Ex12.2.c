#include <stdio.h>
int main() { 
   unsigned a,b,c;
   int n;
   scanf("%d%d",&a,&n);
   b=a << (sizeof(unsigned)*8-n);
   c=a>>n;
   c=c | b;
   printf("0x%x, 0x%x\n",a,c);

   return 0;
}
