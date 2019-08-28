#include <stdio.h>
#define SIZE 4
struct student_type{
  char name[10];
  int num;
  int age;
  char addr[15];
};
int main(){
  int i;
  FILE * fp;
  struct student_type stud[SIZE];

  for(i=0;i<SIZE;i++)
    scanf("%s %d %d %s",stud[i].name,&stud[i].num,
          &stud[i].age,stud[i].addr);

  if((fp=fopen("stu_list","wb"))==NULL)
  { printf("Can not open file"); return -1; }
  for(i=0;i<SIZE;i++)
    fwrite(&stud[i],sizeof(struct student_type),1,fp);
  fclose(fp);

  return 0;
}
