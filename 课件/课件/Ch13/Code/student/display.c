#include <stdio.h>
typedef struct{
   char name[20];
   int num;
   float fScore;
}Student;
void main(int argc, char*argv[]){
  Student stu;
  FILE * fp;
  if(argc!=2){
  	printf("usage: display filename\n");
  	exit(0);
  }
  fp=fopen(argv[1],"rb");
  while(1){
     fread((char*)&stu,sizeof(stu),1,fp);
     if(feof(fp))break;
     printf("%s %d %f\n",stu.name,stu.num,stu.fScore);
}
  fclose(fp);
}
