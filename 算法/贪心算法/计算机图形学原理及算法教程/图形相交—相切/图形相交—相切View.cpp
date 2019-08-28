// 图形相交—相切View.cpp : implementation of the CMyView class
//

#include "stdafx.h"
#include "图形相交—相切.h"

#include "图形相交—相切Doc.h"
#include "图形相交—相切View.h"
#include "math.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyView

IMPLEMENT_DYNCREATE(CMyView, CView)

BEGIN_MESSAGE_MAP(CMyView, CView)
	//{{AFX_MSG_MAP(CMyView)
	ON_COMMAND(ID_LINE_LINE, OnLineLine)
	ON_COMMAND(ID_LINE_CIERCLE1, OnLineCiercle1)
	ON_COMMAND(ID_CIRCLE_CIRCLE, OnCircleCircle)
	ON_COMMAND(ID_LINE_CIRCLE, OnLineCircle)
	ON_WM_RBUTTONDOWN()
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_PLANE_CYLINDER, OnPlaneCylinder)
	ON_COMMAND(ID_PLANE_CONE, OnPlaneCone)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyView construction/destruction

CMyView::CMyView()
{
	P0[0]=255;P0[1]=255;
	C[0]=120;C[1]=120;C[2]=50;
	int i;
	for(i=0;i<4;i++)
	{P2[i].x=0;P2[i].y=0;}
	c1[0]=420;c1[1]=120;c1[2]=50;
	c2[0]=420;c2[1]=120;c2[2]=50;
	l1[0]=400;l1[1]=50;l2[0]=200;l2[1]=200;
	c[0]=320;c[1]=120;c[2]=50;
	num=0;

}

CMyView::~CMyView()
{
}

BOOL CMyView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMyView drawing

void CMyView::OnDraw(CDC* pDC)
{
	CMyDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CMyView printing

BOOL CMyView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMyView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMyView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMyView diagnostics

#ifdef _DEBUG
void CMyView::AssertValid() const
{
	CView::AssertValid();
}

void CMyView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyDoc* CMyView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyDoc)));
	return (CMyDoc*)m_pDocument;
}
#endif //_DEBUG
void CMyView::Tiso(float p0[3],float x0, float y0, float p[3])
{
	p[0]=0.7071*(p0[0]-p0[1])+x0;
	p[1]=-0.4082*(p0[0]+p0[1])+0.8165*p0[2]+y0;
	p[2]=0;	
}
void CMyView::Mydraw()
{
	
	RedrawWindow();	//重绘窗口
	CDC*pDC=GetDC();//获得绘图类指针
	CPen pen1(PS_SOLID,1,(COLORREF)255),pen2(PS_SOLID,1,(COLORREF)255*255);
	CPen* pOldPen=pDC->SelectObject(&pen1);	
	int k;	
	if(PushNum==2)
	{
	//double a,b;
	pDC->TextOut(10,10,"按下键盘上的“上”、“下”、“左”、“右”箭头观看变化直线与圆的的相交情况");
	k=PLC(l1,l2,c,p1,p2);			 	//调用求切点切线子程序
	pDC->Ellipse(c[0]-c[2],c[1]-c[2],c[0]+c[2],c[1]+c[2]);		//画出已知圆
	pDC->SelectObject(&pen2);
	pDC->MoveTo(l1[0],l1[1]);	//画直线			
	pDC->LineTo(l2[0],l2[1]);
	switch(k)
	{	case -1:pDC->TextOut(10,50,"直线与圆不相交，没有交点!");
	         break;
		
		case 0:
			{pDC->TextOut(10,50,"直线与圆相切，切点为:");
			CString e;		
			e.Format("%e	%e",p1[0],p1[1]);	//将数字转化为字符串
			pDC->TextOut(10,70,e);}
			break;
		case 1:
			{pDC->TextOut(10,50,"直线与圆相交，交点为:");
			CString a1,a2;
			a1.Format("%e	%e",p1[0],p1[1]);			//将数字转化为字符串
			a2.Format("%e	%e",p2[0],p2[1]);			//将数字转化为字符串
			pDC->TextOut(10,70,a1);
			pDC->TextOut(10,90,a2);}
			break;
	}
	}
	if(PushNum==3)
	{
	//char ch;
	pDC->TextOut(10,10,"按下键盘上的“上”、“下”、“左”、“右”箭头观看不同点的切线变化");
	k=TPC(P0,C,P,L);							//调用求切点切线子程序
	pDC->Ellipse(C[0]-C[2],C[1]-C[2],C[0]+C[2],C[1]+C[2]);		//画出已知圆
	pDC->MoveTo(P0[0]-4,P0[1]);					//在P0点显示小十字光标
	pDC->LineTo(P0[0]+4,P0[1]);
	pDC->MoveTo(P0[0],P0[1]-4);
	pDC->LineTo(P0[0],P0[1]+4);
	if(k==-1)									//给定P0点落在圆内		
	{
		pDC->TextOut(20,20,"      Point is inside the circle!       ");
	}
	else
	{
	 pDC->MoveTo(P0[0]-4,P0[1]);
	 pDC->LineTo(P0[0]+4,P0[1]);
	 pDC->MoveTo(P0[0],P0[1]-4);
	 pDC->LineTo(P0[0],P0[1]+4);
	 pDC->SelectObject(&pen2);					//设置画切线颜色
	 pDC->MoveTo(P[0],P[1]);
	 pDC->LineTo(P0[0],P0[1]);
	 pDC->MoveTo(P[0]-4,P[1]);					//在切点处画小十字光标
	 pDC->LineTo(P[0]+4,P[1]);
	 pDC->MoveTo(P[0],P[1]-4);
	 pDC->LineTo(P[0],P[1]+4);
	}
	}
	
	if(PushNum==4)
	{
	pDC->TextOut(10,10,"按下键盘上的“上”、“下”、“左”、“右”箭头观看位置或大小不同的两圆相交情况");
	k=PCC(c1,c2,p1,p2);							//调用两圆相交子程序
	pDC->Ellipse(c1[0]-c1[2],c1[1]-c1[2],c1[0]+c1[2],c1[1]+c1[2]);		//画出已知圆1
	pDC->SelectObject(&pen2);
	pDC->Ellipse(c2[0]-c2[2],c2[1]-c2[2],c2[0]+c2[2],c2[1]+c2[2]);		//画出已知圆2
	switch(k)
	{	case -1:pDC->TextOut(10,50,"两个圆相离，没有交点!");
	         break;
		case 0:pDC->TextOut(10,50,"两个圆重合!");
		     break;
		case 1:
			{pDC->TextOut(10,50,"两个圆相切，切点为:");
			CString b;		
			b.Format("%e	%e",p1[0],p1[1]);	//将数字转化为字符串
			pDC->TextOut(10,70,b);
			}
			break;
		case 2:
			{pDC->TextOut(10,50,"两个圆相交，交点为:");
			CString a1,a2;
			a1.Format("%e	%e",p1[0],p1[1]);			//将数字转化为字符串
			a2.Format("%e	%e",p2[0],p2[1]);			//将数字转化为字符串
			pDC->TextOut(10,70,a1);
			pDC->TextOut(10,90,a2);
			pDC->MoveTo(p1[0],p1[1]);
			pDC->LineTo(p2[0],p2[1]);
			}
			break;
	}
		}

	pDC->SelectObject(pOldPen);
	ReleaseDC(pDC);
}


int CMyView::TPC(float P0[2],float C[3],float P[2],float L[3])
{
	float d,sa,ca,sb,cb,st,ct;
	d=sqrt((C[0]-P0[0])*(C[0]-P0[0])+(C[1]-P0[1])*(C[1]-P0[1]));
	//计算P0点到圆心的距离为d
	if(fabs(d)<fabs(C[2]))return -1;		//P0点落在圆内
	sa=(C[1]-P0[1])/d;							
	ca=(C[0]-P0[0])/d;
	sb=C[2]/d;
	cb=sqrt(d*d-C[2]*C[2])/d;
	st=ca*cb-sa*sb;
	ct=sa*cb+ca*sb;
	P[0]=C[0]-C[2]*ct;
	P[1]=C[1]+C[2]*st;
	L[0]=P[1]-P0[1];
	L[1]=-(P[0]-P0[0]);
	L[2]=-P0[0]*P[1]+P[0]*P0[1];
	return 1;								//相切成立
}

int CMyView::PLL(double P1x,double P1y,double P2x,double P2y,double P3x,double P3y,double P4x,double P4y,double &Px,double &Py)
{
	double a,b,c,d,e;			
	double eps=0;			//设置零值的计算精度
	a=P2x-P1x;				//线段P1P2的X坐标差
	b=P4x-P3x;				//线段P3P4的X坐标差
	c=P2y-P1y;				//线段P1P2的Y坐标差
	d=P4y-P3y;				//线段P3P4的Y坐标差
	e=a*d-b*c;
	if(fabs(e)<=eps)return -1;		//两线段平行或重合
	Py=(c*d*(P3x-P1x)+a*d*P1y-b*c*P3y)/e;
	if(fabs(c)<=eps)Px=P3x+b*(Py-P3y)/d;
	else Px=P1x+a*(Py-P1y)/c;
	if((Px-P1x)*(Px-P2x)<=0&&(Px-P3x)*(Px-P4x)<=0)
		return 1;					//有效交点
	else return 0;					//无效交点
}

//变量说明:
	//p1、p2为已知两圆的圆心坐标及半径，c1、c2为所求两圆的交点坐标
int CMyView::PCC(double c1[3],double c2[3],double p1[2],double p2[2])
{
	double d,sa,ca,sb,cb,x1,y1,x2,y2;
	d=sqrt((c1[0]-c2[0])*(c1[0]-c2[0])+(c1[1]-c2[1])*(c1[1]-c2[1]));
	//计算两圆圆心距离
	sa=fabs(c1[2])+fabs(c2[2]);
	sb=fabs(c1[2])-fabs(c2[2]);
	if(d>sa||d<sb) return -1;   //两圆相离
	else if(sb==0&&d==0) return 0;   //两圆重合
	else if(d==sa||d==sb)
	{cb=(c1[2]*c1[2]+d*d-c2[2]*c2[2])/(2.0*d*fabs(c1[2]));
	sb=sqrt(fabs(1.0-cb*cb));
	if(c1[2]>0.0) sb=-sb;   //当R1>0时，跟号前为负号
	ca=(c2[0]-c1[0])/d;     //计算cosα
	sa=(c2[1]-c1[1])/d;     //计算sinα
	x1=fabs(c1[2])*cb;
	y1=fabs(c1[2])*sb;

	p1[0]=x1*ca-y1*sa+c1[0];
	p1[1]=x1*sa+y1*ca+c1[1];
	return 1;
	}
	else 
	{
	cb=(c1[2]*c1[2]+d*d-c2[2]*c2[2])/(2.0*d*fabs(c1[2]));
	sb=sqrt(fabs(1.0-cb*cb));
	if(c1[2]>0.0) sb=-sb;   //当R1>0时，跟号前为负号
	ca=(c2[0]-c1[0])/d;     //计算cosα
	sa=(c2[1]-c1[1])/d;     //计算sinα
	x1=fabs(c1[2])*cb;
	y1=fabs(c1[2])*sb;
	x2=x1;
	y2=-y1;
	p1[0]=x1*ca-y1*sa+c1[0];
	p1[1]=x1*sa+y1*ca+c1[1];
	p2[0]=x2*ca-y2*sa+c1[0];
	p2[1]=x2*sa+y2*ca+c1[1];
	return 2;
	}
	
}
//变量说明:p1、p2为所求交点坐标，l为直线的法线方程系数，c为圆心坐标及半径	
int CMyView::PLC(double l1[2],double l2[2],double c[3],double p1[2],double p2[2])
{
double d,dd,dp,sa,ca,a,b,c1,xa,ya;
	a=l2[1]-l1[1];
	b=-(l2[0]-l1[0]);
	c1=-l1[0]*l2[1]+l2[0]*l1[1];
	dd=sqrt(a*a+b*b);
	d=-(a*c[0]+b*c[1]+c1)/dd;//计算圆心到直线的有向距离
	
	if(fabs(d)>fabs(c[2])) return -1;  //直线与圆不相交相离
	else if(fabs(d)==fabs(c[2]))   //直线与圆相切
	{
		xa=(b*b*c[0]-a*b*c[1]-a*c1)/(dd*dd);//A点坐标
	ya=-(a*a*c[1]-a*b*c[0]-b*c1)/(dd*dd);
	sa=a/dd;
	ca=-a/dd;
	dp=sqrt(c[2]*c[2]-d*d);
	
	p1[0]=xa-dp*ca;
	p1[1]=ya-dp*sa;
	return 0;
	}
	else if(fabs(d)<fabs(c[2]))
	{xa=(b*b*c[0]-a*b*c[1]-a*c1)/(dd*dd);//A点坐标
	ya=-(a*a*c[1]-a*b*c[0]-b*c1)/(dd*dd);
	sa=a/dd;
	ca=-a/dd;
	dp=sqrt(c[2]*c[2]-d*d);
	
	p1[0]=xa-dp*ca;
	p1[1]=ya-dp*sa;
	p2[0]=xa+dp*ca;
	p2[1]=ya+dp*sa;
	return 1;  //直线与圆相交
	}   

}

/////////////////////////////////////////////////////////////////////////////
// CMyView message handlers

void CMyView::OnLineLine() 
{
	// TODO: Add your command handler code here
	RedrawWindow();
	PushNum=1;
		CDC*pDC=GetDC();	//获得绘图类指针
pDC->TextOut(0,5,"用鼠标右键在窗口取选取四个点,当鼠标右键按下第5次求交点");
ReleaseDC(pDC);	
}

void CMyView::OnLineCiercle1() 
{
	// TODO: Add your command handler code here
	
	PushNum=2;
	Mydraw();
}

void CMyView::OnCircleCircle() 
{
	// TODO: Add your command handler code here
PushNum=4;	
Mydraw();	
}

void CMyView::OnLineCircle() 
{
	// TODO: Add your command handler code here
PushNum=3;
Mydraw();
}

void CMyView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
		if(PushNum=1)
	{
	num++;
	if(num<5)
	{	P2[num].x=point.x;			//初始化给相应变量
		P2[num].y=point.y;
	}

	else if(num=5)
	{
	CDC *pDC=GetDC();		//获得CDC对象
	CPen pen1(PS_SOLID,1,(COLORREF)255),pen2(PS_SOLID,1,(COLORREF)255*255);
	CPen* pOldPen=pDC->SelectObject(&pen1);		//设置画线颜色	
	pDC->MoveTo(P2[1].x,P2[1].y);					//在P0点显示小十字光标
	pDC->LineTo(P2[2].x,P2[2].y);
	pDC->MoveTo(P2[3].x,P2[3].y);
	pDC->LineTo(P2[4].x,P2[4].y);
		pDC->SelectObject(pOldPen);
	P1x=P2[1].x;
	P1y=P2[1].y;
	P2x=P2[2].x;
	P2y=P2[2].y;
	P3x=P2[3].x;
	P3y=P2[3].y;
	P4x=P2[4].x;
	P4y=P2[4].y;
	
	int k=PLL(P1x,P1y,P2x,P2y,P3x,P3y,P4x,P4y,Px,Py);		//调用两线段相交子程序
	switch(k)
	{case -1:pDC->TextOut(10,50,"两线段平行或重合!");
	         break;
	 case 0:pDC->TextOut(10,50,"无效交点!");
		     break;
	 case 1:pDC->TextOut(10,50,"您选取的四个点分别为:");
			CString a1,a2;		
			a1.Format("%e	%e      %e  	%e",P1x,P1y,P2x,P2y);	//将数字转化为字符串
			a2.Format("%e	%e      %e  	%e",P3x,P3y,P4x,P4y);
		//	pDC->TextOut(0,40,a);
			a1.Format("%e	%e",P1x,P1y,P2x,P2y);			//将数字转化为字符串
			a2.Format("%e	%e",P3x,P3y,P4x,P4y);			//将数字转化为字符串
					pDC->TextOut(10,70,a1);
					pDC->TextOut(10,90,a1);

		 pDC->TextOut(10,110,"有效交点为:");
			CString b;		
			b.Format("%e	%e",Px,Py);			//将数字转化为字符串
			pDC->TextOut(10,130,b);

			break;
	}
	ReleaseDC(pDC);			//释放CDC对象	
	}
	}
	CView::OnRButtonDown(nFlags, point);
}

void CMyView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	if(PushNum==2)
	{
		switch(nChar){			
		case VK_UP:					//上下左右键选择		
			l1[1]-=2;
			Mydraw();
			break;
		case VK_DOWN:
			l1[1]+=2;
			Mydraw();
			break;
		case VK_RIGHT:
			l2[0]+=2;
			Mydraw();
			break;
		case VK_LEFT:
			l2[0]-=2;
			Mydraw();
			break;
		default:
			break;
		}
	}

	if(PushNum==3)
	{
		switch(nChar){			
		case VK_UP:					//上下左右键选择		
			P0[1]-=2;
			Mydraw();
			break;
		case VK_DOWN:
			P0[1]+=2;
			Mydraw();
			break;
		case VK_RIGHT:
			P0[0]+=2;
			Mydraw();
			break;
		case VK_LEFT:
			P0[0]-=2;
			Mydraw();
			break;
		default:
			break;
		}
	}
	if(PushNum==4)
	{
		switch(nChar){			
		case VK_UP:					//上下左右键选择		
			c1[1]-=2;
			Mydraw();
			break;
		case VK_DOWN:
			c1[1]+=2;
			Mydraw();
			break;
		case VK_RIGHT:
			c2[2]+=2;
			Mydraw();
			break;
		case VK_LEFT:
			c2[2]-=2;
			Mydraw();
			break;
		default:
			break;
		}
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CMyView::OnPlaneCylinder() 
{
	// TODO: Add your command handler code here
	RedrawWindow();
	int i;
	float beta=0.0,db=3.14159/18.0,a;
	float x0=300,y0=200;         //初始化圆柱底圆中心坐标显示位置
	float p1[3],pp1[3],p2[3],pp2[3];  //p1，pp1为椭圆截交线上点变换前后的坐标，p2，pp2为椭圆截交线上点变换前后的坐标，
	float x1,y1,x2,y2;
	float p0[3],R,H,alfa;
	p0[0]=p0[1]=p0[2]=100;
	R=100,H=100,alfa=30;//初始化圆柱与截交面与底面夹角
	a=R*tan(alfa*db*0.1);
	CDC*pDC=GetDC();
	p1[0]=p2[0]=p0[0]+R;//计算底面初始点坐标
	p1[1]=p2[1]=p0[1];
	p1[2]=p0[2]+H+a;
	p2[2]=p0[2];
	
	Tiso(p1,x0,y0,pp1);//正等测变换
	Tiso(p2,x0,y0,pp2);
	x1=pp1[0],y1=pp1[1];
	x2=pp2[0],y2=pp2[2];
	pDC->MoveTo(x1,y1);   //连接z方向竖线
	pDC->LineTo(x2,y2);
	pDC->TextOut(250,80,"平面截圆柱体");
	for(i=1;i<=36;i++)  //按36等分计算和绘制圆柱截交线
	{
	beta+=db;
	p1[0]=p2[0]=p0[0]+R*cos(beta);
	p1[1]=p2[1]=p0[1]+R*sin(beta);
	p1[2]=p0[2]+H+a*(1.0-sin(beta));
	p2[2]=p2[0];
	Tiso(p1,x0,y0,pp1);
	Tiso(p2,x0,y0,pp2);
	CPen pen(PS_SOLID,1,(COLORREF)255);
	CPen* pOldPen=pDC->SelectObject(&pen);		//设置画线颜色	

		
	pDC->MoveTo(x1,y1);   //连接椭圆截交线
	pDC->LineTo(pp1[0],pp1[1]);
	pDC->SelectObject(pOldPen);
    x1=pp1[0],y1=pp1[1];
	x2=pp2[0],y2=pp2[2];
	pDC->MoveTo(x1,y1);   //连接z方向竖线
	pDC->LineTo(x2,y2);
	
	}
	ReleaseDC(pDC);	
}

void CMyView::OnPlaneCone() 
{
RedrawWindow();
	int i;
	float beta=0.0,db=3.14159/18.0,a,r1;
	float x0=300,y0=200;         //初始化圆柱底圆中心坐标显示位置
	float p1[3],pp1[3],p2[3],pp2[3];  //p1，pp1为椭圆截交线上点变换前后的坐标，p2，pp2为椭圆截交线上点变换前后的坐标，
	float x1,y1,x2,y2;
	float p0[3],R,H,alfa,theta;
	p0[0]=p0[1]=p0[2]=100;     //初始化圆锥、截交面与底面夹角
	R=50,H=100,theta=250,alfa=-30;
	r1=R-H*sin(theta*db*0.1);
	a=r1*tan(alfa*db*0.1);
	CDC*pDC=GetDC();
	p1[0]=p0[0]+r1;
	p2[0]=p0[0]+R;//计算底面初始点坐标
	p1[1]=p2[1]=p0[1];
	p1[2]=p0[2]+H+a;
	p2[2]=p0[2];
	
	Tiso(p1,x0,y0,pp1);//正等测变换
	Tiso(p2,x0,y0,pp2);
	x1=pp1[0],y1=pp1[1];
	x2=pp2[0],y2=pp2[2];
	pDC->MoveTo(x1,y1);   //连接z方向竖线
	pDC->LineTo(x2,y2);
	pDC->TextOut(250,60,"平面截圆锥体");
	for(i=1;i<=36;i++)  //按72等分计算和绘制圆柱截交线
	{
	beta+=db;
	p1[0]=p0[0]+r1*cos(beta);
	p2[0]=p0[0]+R*cos(beta);
	p1[1]=p0[1]+r1*sin(beta);
	p2[1]=p0[1]+R*sin(beta);
	p1[2]=p0[2]+H+a*(1.0-sin(beta));
	p2[2]=p0[2];
	Tiso(p1,x0,y0,pp1);
	Tiso(p2,x0,y0,pp2);
	CPen pen(PS_SOLID,1,(COLORREF)255);
	CPen* pOldPen=pDC->SelectObject(&pen);		//设置画线颜色	

	
	pDC->MoveTo(x1,y1);   //连接椭圆截交线
	pDC->LineTo(pp1[0],pp1[1]);
	pDC->SelectObject(pOldPen);
	x1=pp1[0],y1=pp1[1];
	x2=pp2[0],y2=pp2[2];
	pDC->MoveTo(x1,y1);   //连接z方向竖线
	pDC->LineTo(x2,y2);
	
	}	
	ReleaseDC(pDC);
	
}


