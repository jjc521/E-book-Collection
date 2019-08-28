#define PI 3.1415926
#define S(r) PI*r*r

void main()
{
    float a,area;

    a=3.6;
    area = S(a);
    printf("r = %f\narea = %f\n",a,area);
    getch();
}
