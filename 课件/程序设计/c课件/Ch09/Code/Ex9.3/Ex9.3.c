#define PI 3.1415926
#define S(r) PI*r*r

int main()
{
    float a,area;

    a=3.6;
    area = S(a);
    printf("r = %f\narea = %f\n",a,area);

    return 0;
}
