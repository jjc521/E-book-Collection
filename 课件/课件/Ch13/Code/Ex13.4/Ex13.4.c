#include <stdio.h>
#define SIZE 4

struct student_type
{
    char name[10];
    int num;
    int age;
    char addr[15];
}stud[SIZE];

void load()
{
    FILE *fp;
    int i;

    if((fp=fopen("stu_list","rb"))==NULL)
    {
        printf("Can not open file");
        return;
    }

    for(i=0;i<SIZE;i++)
      fread(&stud[i],sizeof(struct student_type),1,fp);
    fclose(fp);
}

int main()
{
    int i;

    load();
    for(i=0;i<SIZE;i++)
      printf("%s %d %d %s\n",stud[i].name,stud[i].num,stud[i].age,stud[i].addr);

    return 0;
}
