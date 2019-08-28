#include <stdio.h>

void copy_string(char from[],char to[])
{
    int i=0;
    while(from[i]!='\0')
    {
        to[i] = from[i];
        i++;
    }
    to[i]='\n';
}

int main()
{
    char a[]="I am a teacher.";
    char b[]="You are a student.";

    printf("\nstring a = %s\nstring b = %s\n",a,b);
    copy_string(a,b);
    printf("\nstring a = %s\nstring b = %s\n",a,b);

    return 0;
}
