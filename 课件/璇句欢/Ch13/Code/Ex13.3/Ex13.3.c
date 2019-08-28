#include <stdio.h>
#define SIZE 4

struct student_type
{
    char name[10];
    int num;
    int age;
    char addr[15];
}stud[SIZE];

void save()
{
    FILE * fp;
    int i;

    if((fp=fopen("stu_list","wb"))==NULL)
    {
        printf("Can not open file");
        return;
    }
    for(i=0;i<SIZE;i++)
      fwrite(&stud[i],sizeof(struct student_type),1,fp);
    fclose(fp);
}

void main()
{
    int i;
    for(i=0;i<SIZE;i++)
      scanf("%s %d %d %s",stud[i].name,&stud[i].num,&stud[i].age,stud[i].addr);
    save();

    getch();
}
