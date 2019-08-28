#include <stdio.h>
void main(){
    char c;
    while((c=getchar())!='\n')
    {
        if((c>='a' && c<='z') || (c>='A' && c<='Z'))
        {
            c+=4;
            if(c>'Z' && c<='Z'+4 || c>'z')
              c-=26;
        }
        printf("%c",c);
    }
    getch();
}
