// BaseClass.cpp: implementation of the CMyClass class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "三维变换.h"
#include "BaseClass.h"
#include "三维变换View.h"
#include "math.h"

#define PI 3.141592654

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBaseClass::CBaseClass()
{
 ed=2000,eh=100,od=400,hl=1,ps=0;
}

CBaseClass::~CBaseClass()
{

}

// 此函数赋轴测图中立体上顶点的齐次坐标值
void   CBaseClass::ReadWorkpiece() 
{
	  X[1] = 0;  Y[1] = 0;  Z[1] = 0;  C[1] = 1;
	  X[2] = 45;  Y[2] = 0;  Z[2] = 0;  C[2] = 1;
	  X[3] = 45; Y[3] = 37;  Z[3] = 0;  C[3] = 1;
	  X[4] = 0;  Y[4] = 37;  Z[4] = 0;  C[4] = 1;
	  X[5] = 0;  Y[5] = 37;  Z[5] = 45;  C[5] = 1;
	  X[6] = 0;  Y[6] = 0;  Z[6] = 45;  C[6] = 1;
	  X[7] = 12;  Y[7] = 0;  Z[7] = 45;  C[7] = 1;
	  X[8] = 30;  Y[8] = 0;  Z[8] = 14;  C[8] = 1;
	  X[9] = 45;  Y[9] = 0;  Z[9] = 14;  C[9] = 1;
	  X[10] = 45;  Y[10] = 37;  Z[10] = 14;  C[10] = 1;
	  X[11] = 30;  Y[11] = 37;  Z[11] = 14;  C[11] = 1;
	  X[12] = 12;  Y[12] = 37;  Z[12] = 45;  C[12] = 1;
	  X[13] = 12;  Y[13]=21;  Z[13]=45;  C[13] = 1;
//	 X[14] = 22;  Y[14]=31;  Z[14]=27;  C[14] = 1;
}

/***************************************************
* 此函数分别用于三个视图的投影变换，统一用变换后顶 *
* 点的三个坐标计算公式求其坐标值。这三个公式是由点 *
* 的齐次坐标乘以变换矩阵得来的。实际上每个视图投影 *
* 只有二个非零坐标需要计算求得，而另一个坐标是零勿 *
* 需计算。因此也可以根据三个不同视图的投影，分别采 *
* 用其投影后的二个坐标计算式来求坐标值。函数中可用 *
* 条件语句选择不同视图投影采用不同坐标计算式求值。 *
***************************************************/
void   CBaseClass::Calculate(array2d B)
{
	  ReadWorkpiece();
	  for (int i = 1;  i <= 12;  ++i )
	  {
	     XT[i] =3*X[i]*B[1][1]+3*Y[i]*B[2][1]+3*Z[i]*B[3][1]+C[i]*B[4][1];
	     YT[i] =3*X[i]*B[1][2]+3*Y[i]*B[2][2]+3*Z[i]*B[3][2]+C[i]*B[4][2];
	     ZT[i] =3*X[i]*B[1][3]+3*Y[i]*B[2][3]+3*Z[i]*B[3][3]+C[i]*B[4][3];
	  }
}

// 此函数求轴测投影后点的坐标值
void   CBaseClass::MCalculate(array2d B)
{
	  ReadWorkpiece();
	  for ( int i = 1;  i <= 12;  ++i )
      {
	     XT[i] =3*X[i]*B[1][1]+3*Z[i]*B[2][1]+3*Y[i]*B[3][1]+C[i]*B[4][1];
	     YT[i] =3*X[i]*B[1][2]+3*Z[i]*B[2][2]+3*Y[i]*B[3][2]+C[i]*B[4][2];
	     ZT[i] =3*X[i]*B[1][3]+3*Z[i]*B[2][3]+3*Y[i]*B[3][3]+C[i]*B[4][3];
      } 
	  // 三个坐标计算公式由点的齐次坐标乘以轴测投影变换矩阵得来。
}
void   CBaseClass::XCalculate(array2d B)
{int i;
	  Read();
	  for (i = 1;i<9;i++ )
	  {
	     ax[i] =XP[i]*B[1][1]+YP[i]*B[2][1]+ZP[i]*B[3][1]+CP[i]*B[4][1];
	     ay[i] =XP[i]*B[1][2]+YP[i]*B[2][2]+ZP[i]*B[3][2]+CP[i]*B[4][2];
	     az[i] =XP[i]*B[1][3]+YP[i]*B[2][3]+ZP[i]*B[3][3]+CP[i]*B[4][3];
	  }
	
}
void CBaseClass::Display()
{
	CFrameWnd* pWnd=(CFrameWnd*)AfxGetApp()->m_pMainWnd;
	CDC* pdc=pWnd->GetActiveView()->GetDC();
	CRect rr;
	::GetClientRect(pWnd->GetActiveView()->m_hWnd,rr);
	DrawText();
	
	DrawViewV(pdc,rr);
	DrawViewH(pdc,rr);
	DrawViewW(pdc,rr);
	pWnd->GetActiveView()->ReleaseDC(pdc);
}

//绘制主视图
void CBaseClass::DrawViewV(CDC* pdc,CRect rr)
{
	xx=rr.right/2;
	yy=rr.bottom/2;
	Calculate(A);  // 作主视图的投影变换
	moveto(xx-XT[1], yy-ZT[1],pdc);
	for ( int i = 2;  i <=12;  ++i )  // 画出主视图
		lineto(xx-XT[i], yy-ZT[i],pdc);
	moveto(xx-XT[1], yy-ZT[1],pdc);
	lineto(xx-XT[4], yy-ZT[4],pdc);
	moveto(xx-XT[1], yy-ZT[1],pdc);
	lineto(xx-XT[6], yy-ZT[6],pdc);
	moveto(xx-XT[7], yy-ZT[7],pdc);
	lineto(xx-XT[12], yy-ZT[12],pdc);
	moveto(xx-XT[3], yy-ZT[3],pdc);
	lineto(xx-XT[10], yy-ZT[10],pdc);
	moveto(xx-XT[2], yy-ZT[2],pdc);
	lineto(xx-XT[9], yy-ZT[9],pdc);
	moveto(xx-XT[12], yy-ZT[12],pdc);
	lineto(xx-XT[5], yy-ZT[5],pdc);
	moveto(xx-XT[8], yy-ZT[8],pdc);
	lineto(xx-XT[11], yy-ZT[11],pdc);  
}

//定义自己的定点函数，(x,y)为所要定的点
void CBaseClass::moveto(double x,double y,CDC* pdc)
{
	pdc->MoveTo((int)x,(int)y);
}

//定义自己的画线函数，由当前点画至(x,y)处
void CBaseClass::lineto(double x,double y,CDC* pdc)
{	
	pdc->LineTo((int)x,(int)y);
}
void CBaseClass::setpixel(double x,double y,CDC* pdc)
{	
	pdc->SetPixel((int)x,(int)y,RGB(255,0,0));
}
//绘制俯视图
void CBaseClass::DrawViewH(CDC* pdc,CRect rr)
{
	xx=rr.right/2;
	yy=rr.bottom/2;
	Calculate(Ah);//作俯视图的投影变换
	moveto(xx-XT[1], yy+ZT[1],pdc);
	for ( int i = 2;  i <= 12;  ++i )  // 画出俯视图
		lineto(xx-XT[i], yy+ZT[i],pdc);
	moveto(xx-XT[1], yy+ZT[1],pdc);
	lineto(xx-XT[4], yy+ZT[4],pdc);
	moveto(xx-XT[1], yy+ZT[1],pdc);
	lineto(xx-XT[6], yy+ZT[6],pdc);
	moveto(xx-XT[7], yy+ZT[7],pdc);
	lineto(xx-XT[12], yy+ZT[12],pdc);
	moveto(xx-XT[3], yy+ZT[3],pdc);
	lineto(xx-XT[10], yy+ZT[10],pdc);
	moveto(xx-XT[2], yy+ZT[2],pdc);
	lineto(xx-XT[9], yy+ZT[9],pdc);
	moveto(xx-XT[12], yy+ZT[12],pdc);
	lineto(xx-XT[5], yy+ZT[5],pdc);
	moveto(xx-XT[8], yy+ZT[8],pdc);
	lineto(xx-XT[11], yy+ZT[11],pdc);  
}

//绘制侧视图
void CBaseClass::DrawViewW(CDC* pdc,CRect rr)
{	
	xx=rr.right/2;
	yy=rr.bottom/2;
	Calculate(Aw);//作侧视图的投影变换
	moveto(xx+XT[1], yy-ZT[1],pdc);
	for ( int i = 2;  i <= 12;  ++i )  // 画出侧视图
		lineto(xx+XT[i], yy-ZT[i],pdc);
	moveto(xx+XT[1], yy-ZT[1],pdc);
	lineto(xx+XT[4], yy-ZT[4],pdc);
	moveto(xx+XT[1], yy-ZT[1],pdc);
	lineto(xx+XT[6], yy-ZT[6],pdc);
	moveto(xx+XT[7], yy-ZT[7],pdc);
	lineto(xx+XT[12], yy-ZT[12],pdc);
	moveto(xx+XT[3], yy-ZT[3],pdc);
	lineto(xx+XT[10], yy-ZT[10],pdc);
	moveto(xx+XT[2], yy-ZT[2],pdc);
	lineto(xx+XT[9], yy-ZT[9],pdc);
	moveto(xx+XT[12], yy-ZT[12],pdc);
	lineto(xx+XT[5], yy-ZT[5],pdc);
	moveto(xx+XT[8], yy-ZT[8],pdc);
	lineto(xx+XT[11], yy-ZT[11],pdc);  
}

//绘制正等测图
void CBaseClass::Drawve()
{	
	int I;
	CFrameWnd* pWnd=(CFrameWnd*)AfxGetApp()->m_pMainWnd;
	CDC* pdc=pWnd->GetActiveView()->GetDC();
	CRect rr;
	::GetClientRect(pWnd->GetActiveView()->m_hWnd,rr);
	xx=rr.right/3;
	yy=rr.bottom*2/4;
	MCalculate(A);//作正等测投影变换
	DrawText();

	moveto(xx+XT[1], yy-YT[1],pdc);
	for ( I = 2;  I <= 3;  ++I )  // 画出正等测图
		lineto(xx+XT[I], yy-YT[I],pdc);

	moveto(xx+XT[5], yy-YT[5],pdc);
	for ( I = 6;  I <= 12;  ++I)
		lineto(xx+XT[I], yy-YT[I],pdc);
	moveto(xx+XT[1], yy-YT[1],pdc);
	lineto(xx+XT[6], yy-YT[6],pdc);
	moveto(xx+XT[7], yy-YT[7],pdc);
	lineto(xx+XT[12], yy-YT[12],pdc);
	moveto(xx+XT[3], yy-YT[3],pdc);
	lineto(xx+XT[10], yy-YT[10],pdc);
	moveto(xx+XT[2], yy-YT[2],pdc);
	lineto(xx+XT[9], yy-YT[9],pdc);
	moveto(xx+XT[12], yy-YT[12],pdc);
	lineto(xx+XT[5], yy-YT[5],pdc);
	moveto(xx+XT[8], yy-YT[8],pdc);
	lineto(xx+XT[11], yy-YT[11],pdc);
	pWnd->GetActiveView()->ReleaseDC(pdc);
}

//绘制正二测图
void CBaseClass::Drawvt()
{
	int I;
	CFrameWnd* pWnd=(CFrameWnd*)AfxGetApp()->m_pMainWnd;
	CDC* pdc=pWnd->GetActiveView()->GetDC();
	CRect rr;
	::GetClientRect(pWnd->GetActiveView()->m_hWnd,rr);
	xx=rr.right/3;
	yy=rr.bottom*2/3;
	MCalculate(A);//作正二测投影变换
	DrawText();
	moveto(xx+XT[1], yy-YT[1],pdc);  // 下面语句画出正二测图
	for ( I = 2;  I <= 12;  ++I )
		lineto(xx+XT[I], yy-YT[I],pdc);
	moveto(xx+XT[1], yy-YT[1],pdc);
	lineto(xx+XT[4], yy-YT[4],pdc);
	moveto(xx+XT[1], yy-YT[1],pdc);
	lineto(xx+XT[6], yy-YT[6],pdc);
	moveto(xx+XT[7], yy-YT[7],pdc);
	lineto(xx+XT[12], yy-YT[12],pdc);
	moveto(xx+XT[3], yy-YT[3],pdc);
	lineto(xx+XT[10], yy-YT[10],pdc);
	moveto(xx+XT[2], yy-YT[2],pdc);
	lineto(xx+XT[9], yy-YT[9],pdc);
	moveto(xx+XT[12], yy-YT[12],pdc);
	lineto(xx+XT[5], yy-YT[5],pdc);
	moveto(xx+XT[8], yy-YT[8],pdc);
	lineto(xx+XT[11], yy-YT[11],pdc);  
	pWnd->GetActiveView()->ReleaseDC(pdc);
}

//绘制斜等测图
void CBaseClass::Drawse()
{
	int I;
	CFrameWnd* pWnd=(CFrameWnd*)AfxGetApp()->m_pMainWnd;
	CDC* pdc=pWnd->GetActiveView()->GetDC();
	CRect rr;
	::GetClientRect(pWnd->GetActiveView()->m_hWnd,rr);
	xx=rr.right/3;
	yy=rr.bottom*2/3;
	MCalculate(A);  // 作斜等测投影变换
	DrawText();
    moveto(xx+XT[1], yy-YT[1],pdc);
	for ( I = 2;  I <= 3;  ++I )  // 以下语句画出斜等测图
		lineto(xx+XT[I], yy-YT[I],pdc);
	moveto(xx+XT[5], yy-YT[5],pdc);
	for ( I = 6;  I <= 12;  ++I)
		lineto(xx+XT[I], yy-YT[I],pdc);
	moveto(xx+XT[1], yy-YT[1],pdc);
	lineto(xx+XT[6], yy-YT[6],pdc);
	moveto(xx+XT[7], yy-YT[7],pdc);
	lineto(xx+XT[12], yy-YT[12],pdc);
	moveto(xx+XT[3], yy-YT[3],pdc);
	lineto(xx+XT[10], yy-YT[10],pdc);
	moveto(xx+XT[2], yy-YT[2],pdc);
	lineto(xx+XT[9], yy-YT[9],pdc);
	moveto(xx+XT[12], yy-YT[12],pdc);
	lineto(xx+XT[5], yy-YT[5],pdc);
	moveto(xx+XT[8], yy-YT[8],pdc);
	lineto(xx+XT[11], yy-YT[11],pdc);
	pWnd->GetActiveView()->ReleaseDC(pdc);

}

//在(5,5)处输出当前所画图形的名称
void CBaseClass::DrawText()
{
	CFrameWnd* pWnd=(CFrameWnd*)AfxGetApp()->m_pMainWnd;
	CDC* pdc=pWnd->GetActiveView()->GetDC();
	CMyView* pView=(CMyView*)pWnd->GetActiveView();
	pdc->TextOut(300,200,pView->m_str);
	pWnd->GetActiveView()->ReleaseDC(pdc);
}



void   CBaseClass::Draw() 
{
	CFrameWnd* pWnd=(CFrameWnd*)AfxGetApp()->m_pMainWnd;
	CDC* pdc=pWnd->GetActiveView()->GetDC();
DrawText();
double cx,cy;
 cx=320;
 cy=180;

 XCalculate(A); 
for (int i = 1; i <5; i++ )
	  {
	     bx[i+4]=bx[i] =ax[i+4];
	     by[i+4]=by[i] =ay[i+4];
	     bz[i+4]=bz[i] =az[i+4];
	  }
		for ( i = 1; i <5; i++ )
	  {
	    ax[i+4] =ax[i];
	     ay[i+4] =ay[i];
	     az[i+4] =az[i];
	  }

for(nn=1;nn<=n;nn++)
{
moveto(cx+ax[nn],cy+ay[nn],pdc);
lineto(cx+ax[nn],cy+ay[nn],pdc);
lineto(cx+ax[nn+1],cy+ay[nn+1],pdc);
lineto(cx+bx[nn+1],cy+by[nn+1],pdc);
lineto(cx+bx[nn],cy+by[nn],pdc);
} 	
pWnd->GetActiveView()->ReleaseDC(pdc);
}

void   CBaseClass::Read() 
{
int flag,r,h;
double pi,x,y,z,cx,cy,thx,thy,th;
double xw,yw,zw;

pi=3.14159;
cx=320;
cy=180;
int ed=2000,eh=100,od=400,hl=1; 
 
h=80; thy=0.2;r=100;n=4;thx=0.2;
flag=0;nn=1;

for(th=0;th<=2*pi+0.1;th+=2*pi/n)
{
x=r*cos(th); y=h; z=r*sin(th);

//Call rot_y: Call rot_x
zw=z; xw=x;
x=zw*cos(thy)-xw*sin(thy);
z=zw*sin(thy)+xw*cos(thy);

yw=y; zw=z;
y=yw*cos(thx)-zw*sin(thx);
z=yw*sin(thx)+zw*cos(thx);

if(ps==1){
	x=x*ed/(ed-od-z);
	y=(y*ed-eh*(od+z))/(ed-od-z);
}
//ax[nn]=x; ay[nn]=y; az[nn]=z;
XP[nn]=x; YP[nn]=y; ZP[nn]=z;
nn=nn+1;
}

flag=0;
nn=1;
for(th=0;th<=2*pi+0.1;th+=2*pi/n){
x=r*cos(th); y=-h; z=r*sin(th);

//Call rot_y: Call rot_x
zw=z; xw=x;
x=zw*cos(thy)-xw*sin(thy);
z=zw*sin(thy)+xw*cos(thy);

yw=y; zw=z;
y=yw*cos(thx)-zw*sin(thx);
z=yw*sin(thx)+zw*cos(thx);

if(ps==1){
	x=x*ed/(ed-od-z);
	y=(y*ed-eh*(od+z))/(ed-od-z);}
//bx[nn]=x; by[nn]=y; bz[nn]=z;
XP[nn+4]=x; YP[nn+4]=y; ZP[nn+4]=z;
nn=nn+1;
}

CP[1] = 1;CP[2] = 1;CP[3] = 1; CP[4] = 1;CP[5] = 1;CP[6] = 1;CP[7] = 1;CP[8] = 1;	

}


	