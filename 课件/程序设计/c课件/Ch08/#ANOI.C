#include "stdio.h"
#include "graphics.h"
#include "conio.h"
#include "string.h"
#include "alloc.h"

#define dy 200  //box's size,you can modify them.
#define dh 10
#define dw 10
#define time1 5 //control the speed of movice
#define time2 5

int m,x[4]={0,105,320,535},y[4]={370,370,370,370},p[640];
char c;
delay(int);
stpic();
hanoi(int,char,char,char);
move(char,char);
trace(int,int,int,int);
movbox(int,int);
movice(int,int);

void main()
 {
  printf("input the number:   ");
  scanf("%d",&m);
  printf("how do you want to watch the display?   n:normal;   m:movice;\nPlease choos:  ");
  getchar();
  scanf("%c",&c);
  stpic();
  getch();
  hanoi(m,'A','B','C');
  bar(0,420,639,460);
  setcolor(WHITE);
  outtextxy(10,430,"press any key to Exit...");
  getch();
  closegraph();
  }
stpic()
 {
  int drive=DETECT,mode,i,j;

  registerbgidriver(EGAVGA_driver);
  //If you want the program to run without file of EGAVGA.BGI then
  //the this command is necessary.But you must prepare something
  //before compile these codes.
  initgraph(&drive,&mode,"");

  setfillstyle(1,1);
  settextstyle(0,0,3);
  bar(0,420,639,460);
  outtextxy(10,430,"press any to continue......");
  setcolor(GREEN);
  for(i=1;i<=3;i++) line(x[i]-100,y[i],x[i]+100,y[i]);
  for(i=1;i<=3;i++) line(x[i],y[i]-dy,x[i],y[i]);
  outtextxy(95,375,"A");
  outtextxy(310,375,"B");
  outtextxy(525,375,"C");
  setcolor(WHITE);
  for(i=m,j=1;(i>0)&&(j<=m);i--,j++)
    {setfillstyle(1,j);
     rectangle(x[1]-i*dw,y[1]-j*dh,x[1]+i*dw,y[1]-(j-1)*dh);
     floodfill(x[1]-i*dw+3,y[1]-j*dh+3,WHITE);
     }
  y[1]-=m*dh;
  return(0);
 }
trace(int x1,int y1,int x2,int y2)
 {
  int x3,y3=60,i;
  double q;
  x3=(x1+x2)/2;
  q=(x1-x3);
  q=q*(x1-x3);
  q=q/(y1-y3)/2.0;
  if (x1<=x2) for(i=x1;i<=x2;i++) p[i]=(i-x3)/2.0/q*(i-x3)+y3;
  if (x1>x2)  for(i=x2;i<=x1;i++) p[i]=(i-x3)/2.0/q*(i-x3)+y3;
  return(0);
  }
move(char b1,char b2)
 {
  int b1c,b2c,i;
  char str[20];
  for (i=0;i<20;i++) str[i]='\0';
  switch (b1)
   {
    case 'A': b1c=1;break;
    case 'B': b1c=2;break;
    case 'C': b1c=3;
    }
  switch (b2)
   {
    case 'A': b2c=1;break;
    case 'B': b2c=2;break;
    case 'C': b2c=3;
    }
  strcat(str,"move ");
  str[5]=b1;
  strcat(str," to ");
  str[10]=b2;
  bar(0,420,639,460);
  setcolor(WHITE);
  outtextxy(10,430,str);
  if (c=='m') movice(b1c,b2c);
  else movbox(b1c,b2c);
  return(0);
  }
hanoi(int n,char one,char two,char three)
 {
  if (n==1) move(one,three);
  else {
  hanoi(n-1,one,three,two);
  move(one,three);
  hanoi(n-1,two,one,three);
  }
  return(0);
  }
movbox(int a,int b)
 {
  int xl,i;
  unsigned size;
  void *buf;
  for(xl=x[a]-1;;xl--) if (getpixel(xl,y[a])!=WHITE) break;
  xl+=1;
  size=imagesize(xl,y[a],2*x[a]-xl,y[a]+dh);
  buf=malloc(size);
  getimage(xl,y[a],2*x[a]-xl,y[a]+dh,buf);
  getch();
  putimage(x[b]-x[a]+xl,y[b]-dh,buf,COPY_PUT);
  putimage(xl,y[a],buf,XOR_PUT);
  setcolor(WHITE);
  line(xl,y[a]+dh,2*x[a]-xl,y[a]+dh);
  y[a]+=dh;
  y[b]-=dh;
  setcolor(GREEN);
  for (i=1;i<=3;i++)
     {
       line(x[i],y[i],x[i],y[0]-dy);
       if (y[i]==y[0]) line(x[i]-100,y[0],x[i]+100,y[0]);
      }
  free(buf);
  return(0);
 }
movice(int a,int b)
 {
  int xl,i;
  unsigned size;
  void *buf;
  for(xl=x[a]-1;;xl--)
     if (getpixel(xl,y[a])!=getpixel(xl-1,y[a])) break;
  size=imagesize(xl,y[a],2*x[a]-xl,y[a]+dh);
  buf=malloc(size);
  getimage(xl,y[a],2*x[a]-xl,y[a]+dh,buf);
  for (i=y[a];i>(y[0]-dy);i--)
    {
     putimage(xl,i,buf,XOR_PUT);
     setcolor(GREEN);
     line(x[a],y[a]+dh,x[a],i);
     putimage(xl,i-1,buf,COPY_PUT);
     setcolor(WHITE);
     line(xl-1,y[a]+dh,2*x[a]-xl,y[a]+dh);
     if (y[a]+dh==y[0])
   {
    setcolor(GREEN);
    line(x[a]-100,y[0],x[a]+100,y[0]);
   }
     delay(time1);
     }
  putimage(xl,i,buf,XOR_PUT);
  trace(x[a],i,x[b],i);
  for(i=x[a];(x[a]<=x[b])? i<x[b]:i>x[b];(x[a]<=x[b])? i++:i--)
    {
     putimage(i-x[a]+xl,p[i],buf,COPY_PUT);
     delay(time2);
     putimage(i-x[a]+xl,p[i],buf,XOR_PUT);
     }
  setcolor(GREEN);
  for(i=y[0]-dy;i<y[b]-dh;i++)
    {
     line(x[b],y[0]-dy,x[b],i);
     putimage(x[b]-x[a]+xl,i,buf,COPY_PUT);
     delay(time1);
     putimage(x[b]-x[a]+xl,i,buf,XOR_PUT);
     }
  putimage(x[b]-x[a]+xl,i,buf,COPY_PUT);
  y[a]+=dh;
  y[b]-=dh;
  free(buf);
  return(0);
 }
delay(int n)
{
 int i,j;
 for (;n>0;n--)
   for (i=100;i>0;i--)
     for (j=1000;j>0;j--);
 return(0);
 }

