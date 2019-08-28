#include <stdio.h>
#define SIZE 10
struct student_type{
  char name[10];
  int num;
  int age;
  char addr[15];
};
int main(){
  int i, cnt=0;
  FILE *fp;
  struct student_type stud[SIZE];

  if((fp=fopen("stu_list","rb"))==NULL)
  { printf("Can not open file");return -1; }

  for(;;){
    fread(&stud[cnt],sizeof(struct student_type),1,fp);
    if (feof(fp)) break;
    cnt++;
  }
  fclose(fp);

  for(i=0;i<cnt;i++)
    printf("%s %d %d %s\n",stud[i].name,stud[i].num,
           stud[i].age,stud[i].addr);

  return 0;
}
