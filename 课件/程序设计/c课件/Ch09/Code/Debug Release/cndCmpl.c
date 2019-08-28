#include <stdio.h>
#include <graphics.h>

#define _RELEASE

void main()
{
    int d=DETECT,m,maxx,maxy;

    initgraph(&d,&m,"");
    maxx=getmaxx();maxy=getmaxy();
    setfillstyle(SOLID_FILL,BLUE);
    bar(0,0,maxx,maxy);
    circle(200,200,100);

    #ifdef _DEBUG
        printf("maxx=%d,maxy=%d\n",maxx,maxy);
        printf("maxx=%d,maxy=%d\n",maxx,maxy);
        printf("maxx=%d,maxy=%d\n",maxx,maxy);
        printf("maxx=%d,maxy=%d\n",maxx,maxy);
        printf("maxx=%d,maxy=%d\n",maxx,maxy);
        printf("maxx=%d,maxy=%d\n",maxx,maxy);
        printf("maxx=%d,maxy=%d\n",maxx,maxy);
        printf("maxx=%d,maxy=%d\n",maxx,maxy);
        printf("maxx=%d,maxy=%d\n",maxx,maxy);
        printf("maxx=%d,maxy=%d\n",maxx,maxy);
    #endif

    getch();
    closegraph();
}
