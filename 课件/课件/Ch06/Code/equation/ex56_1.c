#include <stdio.h>
#include <math.h>
int main(){
    float a,b,c,d,disc,x1,x2,realpart,imagepart;
    scanf("%f%f%f",&a,&b,&c);
    printf("The Equation ");
    if(fabs(a)<1e-6){    /* a==0 */
    	if(fabs(b)<1e-6){  /* b==0 */
        if(fabs(c)<1e-6)   /* c==0 */
          printf("is an identity, it has infinite roots.\n");
        else  /* c!=0 */
        	printf("is an inequality, it has no root.\n");
    	}
    	else{              /* b!=0 linear equation */
    	  x1=-c/b;
    	  printf("is a linear equation, its root is: %f\n", x1);
    	}
    }
    else{                /* a!=0 quadratic equation*/
        disc = b*b-4*a*c;
        if(fabs(disc)<1e-6)
           printf("has two equal roots:%8.4f\n",-b/(2*a));
        else if(disc>0){
              x1=(-b+sqrt(disc))/(2*a);x2=(-b-sqrt(disc))/(2*a);
              printf("has two distinct real roots:%8.4f and %8.4f\n", x1,x2);
          }
          else{
              realpart=-b/(2*a);imagepart=sqrt(-disc)/(2*a);
              printf("has complex roots:\n");
              printf("%8.4f + %8.4fi\n",realpart,imagepart);
              printf("%8.4f - %8.4fi\n",realpart,imagepart);
          }
    }
  return 0;
}
