#include <stdio.h>
#include <math.h>
int main(){
    float a,b,c,d,disc,x1,x2,realpart,imagepart;
    scanf("%f%f%f",&a,&b,&c);
    printf("The Equation ");
    if(fabs(a)<1e-6)
      printf("is not a quadratic");
    else
    {
        disc = b*b-4*a*c;
        if(fabs(disc)<1e-6)
          printf("has two equal roots:%8.4f\n",-b/(2*a));
        else
          if(disc>1e-6)
          {
              x1=(-b+sqrt(disc))/(2*a);
              x2=(-b-sqrt(disc))/(2*a);
              printf("has two distinct real roots:%8.4f and %8.4f\n",x1,x2);
          }
          else
          {
              realpart=-b/(2*a);
              imagepart=sqrt(-disc)/(2*a);
              printf("has complex roots:\n");
              printf("%8.4f + %8.4fi\n",realpart,imagepart);
              printf("%8.4f - %8.4fi\n",realpart,imagepart);
          }
    }

    return 0;
}
