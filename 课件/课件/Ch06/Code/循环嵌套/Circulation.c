#include <stdio.h>
int main(){
    int i,j;

    for(i=1;i<=5;i++)
    {
        j=0;
        do
        {
            printf(" ");
            j++;
        }while(j<42-2*i);
        j=0;
        while(j<2*i-1)
        {
            printf(" *");
            j++;
        }
        printf("\n");
    }
    getch();
    return 0;
}
