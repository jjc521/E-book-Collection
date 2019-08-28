#include <stdio.h>

void main()
{
    FILE *in,*out;
    char ch,infile[10],outfile[10];

    scanf("%s",infile);scanf("%s",outfile);
    in=fopen(infile,"r");
    if(in==NULL)
    {
        printf("Error when openning input file");
        exit(0);
    }
    if((out=fopen(outfile,"w"))==NULL)
    {
        printf("Error when openning output file");
        exit(0);
    }
    while(1)
    {
        ch = fgetc(in);
        if(feof(in))break;
        fputc(ch,out);
    }
    fclose(in);fclose(out);

    getch();
}
