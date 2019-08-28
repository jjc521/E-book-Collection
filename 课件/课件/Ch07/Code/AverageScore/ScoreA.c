#include <stdio.h>
int main(){
    float s[10];
    float average=0;
    int i;

    for(i=0;i<10;i++)
    {
        scanf("%f",&s[i]);
        average+=s[i];
    }
    average/=10;
    printf("Average is %f\n",average);
    printf("Scores below average is:\n");
    for(i=0;i<10;i++)
      if(s[i]<average)
        printf("%f ",s[i]);

    return 0;
}
