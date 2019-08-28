#include <stdio.h>
#include <string.h>
#define FORMAT "%d\n%s\n%f\n%f\n%f\n"

struct student
{
    int num;
    char name[20];
    float score[3];
};

void main()
{
    void print(struct student);
    struct student stu;

    stu.num=12345;
    strcpy(stu.name,"Li Lin");
    stu.score[0]=67.5;
    stu.score[1]=89;
    stu.score[2]=78.6;
    print(stu);

    getch();
}

void print(struct student stu)
{
    printf(FORMAT,stu.num,stu.name,stu.score[0],stu.score[1],stu.score[2]);
    printf("\n");
}
