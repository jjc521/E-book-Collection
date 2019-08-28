#include <stdio.h>
typedef struct{
   char name[20];
   int num;
   float fScore;
}Student;

void main(){
	Student stu;
  FILE * fp=fopen("stud","wb");
  stu.fScore=stu.fScore;
  while(1){
     scanf("%s%d%f",stu.name,&stu.num,&stu.fScore);
	 if(stu.num<0)break;

     fwrite((char*)&stu,sizeof(stu),1,fp);
  }
  fclose(fp);
}
