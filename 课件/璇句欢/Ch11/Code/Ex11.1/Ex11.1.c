#include <stdio.h>
void main()
{
    struct student
    {
        long int num;
        char name[20];
        char sex;
        char addr[20];
    }a={89031,"Li Lin",'M',"123 Beijing Road"};

    printf("NO.:%ld\nName:%s\nSex:%c\nAddress:%s\n",a.num,a.name,a.sex,a.addr);
    getch();
}
