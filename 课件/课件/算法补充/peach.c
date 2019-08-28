#include <stdio.h>

int main(){
	int peach=1;
	int day=10;
	for(;day>1;day--){
	  peach = (peach+1)*2;
	}
	printf("%d\n",peach);

	return 0;
}