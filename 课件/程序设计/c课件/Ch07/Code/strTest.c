#include <stdio.h>
#include <string.h>

int main(){
	char result[200];
	char mid[6][30];
	int i;
	char c;
	FILE * fp;

	fp=fopen("users","w");

	while(1){
	  for(i=0;i<6;i++)
	  	  scanf("%s",&mid[i][0]);
	  fflush(stdin);

	  sprintf(result, "%s/%s/%s/%s/%s/%s\n",mid[0],mid[1],mid[2],mid[3],mid[4],mid[5]);
	  printf("%s\n", result);
	  fprintf(fp,"%s\n", result);
     
    getchar();
	  c=getchar();
	  if (c=='n' or c=='N') break;
	}

	fclose(fp);

	return 0;
}