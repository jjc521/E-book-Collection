#include <stdio.h>
#include <string.h>

int main(){
	char cName[]="³Ì½¨¾ü";
	unsigned char zm[3][32];
	long qu,wei,pos;
	int i,j,k,bit,len;
	FILE * fp;

	fp=fopen("HZK16","rb");

  printf("{");
	len=strlen(cName);
	for(i=0;i<3;i++){
		qu=(cName[2*i]-0xA1)&0x7f;
		wei=(cName[2*i+1]-0xA1)&0x7f;
		pos=(qu*94+wei)*32L;
		fseek(fp,pos,SEEK_SET);
		fread(zm[i],1,32,fp);
		printf("{");
		for(j=0;j<32;j++)
			if(j<31)
				printf("0X%02X,",zm[i][j]);
			else
				printf("0X%02X},",zm[i][j]);
	}
	printf("\b}\n\n");
	fclose(fp);

	for(i=0;i<16;i++){
		for(j=0;j<3;j++){
			for(k=0;k<2;k++){
				for(bit=0;bit<8;bit++){
					if((zm[j][i*2+k]>>(7-bit))&1)
						printf("O");
					else printf(" ");
				}
			}
			printf("   ");
		}
		printf("\n");
	}

  printf("\n\n");
	return 0;
}