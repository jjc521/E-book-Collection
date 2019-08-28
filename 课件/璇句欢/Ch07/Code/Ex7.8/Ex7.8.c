#include <stdio.h>
void main(){
    char string[80];
    int i,num=0,word=0;
    char c;

    gets(string);
    for(i=0;(c=string[i])!='\0';i++)
      if(c==' ')word=0;
      else if(word==0)
      {
          word=1;
          num++;
      }
    printf("There are %d words in the line.\n",num);

    getch();
}
