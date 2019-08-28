#include <stdio.h>
int main()
{
    float s1,s2,s3,s4,s5,s6,s7,s8,s9,s10;
    float average;

    printf("Enter scores:");
    scanf("%f%f%f%f%f%f%f%f%f%f",&s1,&s2,&s3,&s4,&s5,&s6,&s7,&s8,&s9,&s10);
    average=(s1+s2+s3+s4+s5+s6+s7+s8+s9+s10)/10;
    printf("Average is %f",average);
    printf("\nScores below average is:\n");
    if(s1<average)printf("%f ",s1);
    if(s2<average)printf("%f ",s2);
    if(s3<average)printf("%f ",s3);
    if(s4<average)printf("%f ",s4);
    if(s5<average)printf("%f ",s5);
    if(s6<average)printf("%f ",s6);
    if(s7<average)printf("%f ",s7);
    if(s8<average)printf("%f ",s8);
    if(s9<average)printf("%f ",s9);
    if(s10<average)printf("%f ",s10);

    return 0;
}
