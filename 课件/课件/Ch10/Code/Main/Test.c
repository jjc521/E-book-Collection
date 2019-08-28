#include <stdio.h>

int main(int argc,char *argv[])
{
  char c;
  FILE *fp=fopen(argv[1],"r");
  for(;;){
    fscanf(fp,"%c",&c);
    if(feof(fp))break;
    printf("%c",c);
  }
  fclose(fp);
/*
    int i;
    printf("Total parameter are: %d\n",argc);
    for(i=0;i<argc;i++)
      printf("\nargv[%d]= %s",i,argv[i]);
*/
    getch();
    return 0;
}
