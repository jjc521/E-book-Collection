#include <stdio.h>

void main()
{
    float score[][4]={{60,70,80,90},{56,89,67,88},{34,78,90,66}};
    float *search(float (*pointer)[4],int n);
    float *p;
    int i,m;

    printf("Enter the number os student:");
    scanf("%d",&m);
    printf("The scores of No.%d are:\n",m);
    p=search(score,m);
    for(i=0;i<4;i++)
      printf("%5.2f\t",*(p+i));
    getch();
}
float *search(float (*pointer)[4],int n)
{
    float *pt;
    pt=*(pointer+n);
    return pt;
}
