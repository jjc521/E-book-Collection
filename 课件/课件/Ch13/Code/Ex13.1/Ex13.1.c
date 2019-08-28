#include <stdio.h>

int main()
{
    FILE *fp;
    char ch,filename[10];

    scanf("%s",filename);
    fp = fopen(filename,"w");
    if(fp==NULL)
    {
        printf("Error when openning file");
        exit(0);
    }

    getchar();
    ch=getchar();
    while(ch!='#')
    {
        fputc(ch,fp);
        putchar(ch);
        ch=getchar();
    }
    fclose(fp);

    return 0;
}
