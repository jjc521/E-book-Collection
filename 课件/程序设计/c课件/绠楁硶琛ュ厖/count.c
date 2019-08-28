#include <stdio.h>
int main(){
	int x;
	for (x=0;;x++){
		if (x<1500) continue;
	  if (x%3==2 && x%5==3 && x%7==2)
	    printf("%d\n", x);
	}


	return 0;
}