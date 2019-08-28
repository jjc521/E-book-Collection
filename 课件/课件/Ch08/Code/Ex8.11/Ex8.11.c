#include <stdio.h>

float average(float array[10]){
    int i;
    float aver,sum=array[0];

    for(i=1;i<10;i++)
      sum += array[i];
    aver = sum / 10;

    return aver;
}

int main(){
    float score[10],aver;
    int i;

    printf("input 10 scores:");
    for(i=0;i<10;i++)
      scanf("%f",&score[i]);
    printf("\n");
    aver = average(score);
    printf("Average score is %5.2f\n",aver);

    return 0;
}
