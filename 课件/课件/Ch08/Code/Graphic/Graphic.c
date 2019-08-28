#include <graphics.h>
#include "conio.h"
#include "math.h"
#define PI 3.141592654
#define a 15
void main()
{
   int d=DETECT,m,errcode;
   int maxx,maxy;
   float x1,y1,x2,y2,t;
   char c;

   initgraph(&d,&m,"");
   
   maxx=getmaxx();maxy=getmaxy();

   circle(maxx/2,maxy/2,100);
   getch();

   setfillstyle(SOLID_FILL,LIGHTGREEN);
   setcolor(RED);
   bar(maxx/2-120,maxy/2-120,maxx/2+120,maxy/2+120);
   rectangle(maxx/2-120,maxy/2-120,maxx/2+120,maxy/2+120);
   line(maxx/2-120,maxy/2,maxx/2+120,maxy/2);
   line(maxx/2,maxy/2-120,maxx/2,maxy/2+120);

   t=0;
   while(t<=2*PI)
   {
      x1=80*sin(2*t)*cos(t);
      y1=80*sin(2*t)*sin(t);
      putpixel(maxx/2+x1,maxy/2-y1,RED);
      delay(100);
      t+=0.002;
    }
   getch();

   bar(maxx/2-120,maxy/2-120,maxx/2+120,maxy/2+120);
   rectangle(maxx/2-120,maxy/2-120,maxx/2+120,maxy/2+120);
   line(maxx/2-120,maxy/2,maxx/2+120,maxy/2);
   line(maxx/2,maxy/2-120,maxx/2,maxy/2+120);
   t=0;
   while(t<=2*PI)
   {
       x1=80*cos(2*t)*cos(t);
       y1=80*cos(2*t)*sin(t);
       putpixel(maxx/2+x1,maxy/2-y1,RED);
       delay(100);
       t+=0.002;
    }
   getch();

   bar(maxx/2-120,maxy/2-120,maxx/2+120,maxy/2+120);
   rectangle(maxx/2-120,maxy/2-120,maxx/2+120,maxy/2+120);
   line(maxx/2-120,maxy/2,maxx/2+120,maxy/2);
   line(maxx/2,maxy/2-120,maxx/2,maxy/2+120);
   t=0;
   while(t<PI)
   {
       x1=80*cos(3*t)*cos(t);
       y1=80*cos(3*t)*sin(t);
       putpixel(maxx/2+x1,maxy/2-y1,RED);
       delay(100);
       t+=0.002;
   }
   getch();

   bar(maxx/2-120,maxy/2-120,maxx/2+120,maxy/2+120);
   rectangle(maxx/2-120,maxy/2-120,maxx/2+120,maxy/2+120);
   line(maxx/2-120,maxy/2,maxx/2+120,maxy/2);
   line(maxx/2,maxy/2-120,maxx/2,maxy/2+120);
   t=0;
   while(t<PI)
   {
       x1=80*sin(3*t)*cos(t);
       y1=80*sin(3*t)*sin(t);
       putpixel(maxx/2+x1,maxy/2-y1,RED);
       delay(100);
       t+=0.002;
   }
   getch();

   closegraph();
}