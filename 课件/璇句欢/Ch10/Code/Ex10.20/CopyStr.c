#include <stdio.h>

void copy_string(char *from,char *to)
{
    for(;*from!='\0';from++,to++)
      *to = *from;
    *to='\0';
}

void main()
{
    char *a="I am a teacher.";
    char *b="you are a student.";
    printf("\nstring a = %s\nstring b = %s\n",a,b);
    copy_string(a,b);
    printf("\nstring a = %s\nstring b = %s\n",a,b);
    getch();
}
