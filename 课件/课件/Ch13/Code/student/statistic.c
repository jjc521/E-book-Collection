#include <stdio.h>
typedef struct{
   char name[20];
   int num;
   float fScore;
}Student;
void main(){
  Student stu;
  FILE * fpIn=fopen("stud","rb");
  FILE * fpOut=fopen("failure","wb");
  while(1){
     fread((char*)&stu,sizeofi(stu),1,fpIn);
     if(feof(fpIn))break;
     if(stu.fScore<60)
        fwrite((char*)&stu,sizeof(stu),1,fpOut);
}
  fclose(fpIn); fclose(fpOut);
}
