// 消隐View.cpp : implementation of the CMyView class
//

#include "stdafx.h"
#include "消隐.h"

#include "消隐Doc.h"
#include "消隐View.h"
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
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_TUMIANTI, OnTumianti)
	ON_COMMAND(ID_YUANJIN, OnYuanjin)
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

void  CMyView::Project(float X, float Y, float Z)// 此函数求点的平行投影和透视投影坐标值
{
       XObs = -X * Aux1 + Y * Aux3;
       YObs = -X * Aux5 - Y * Aux6 + Z * Aux4;
       // 求透视投影坐标值
	     ZObs = -X * Aux7 - Y * Aux8 - Z * Aux2 + Rol;
	     XProj = DE * XObs / ZObs;
	     YProj = DE * YObs / ZObs;
}

void  CMyView::WLineTo(float X, float Y, float Z,CDC*pDC)// 用三维点坐标直接从当前点画线到一点的函数
{ 
	  Project(X, Y, Z); // 将三维点作投影
	  XScreen = floor(0.5 + XProj * Scale +150); // 圆整
	  YScreen = floor(0.5 + 100 - YProj); // 圆整
	  pDC->LineTo(XScreen, YScreen); // 画线到一点
}

void  CMyView::WMoveTo(float X, float Y, float Z,CDC*pDC)// 三维坐标下直接将当前点移动到某点的函数
{ 
	  Project (X, Y, Z); // 将三维点作投影
	  XScreen = floor(0.5 + XProj * Scale + 150); // 圆整
	  YScreen = floor(0.5 + 100 - YProj); // 圆整
	  pDC->MoveTo(XScreen, YScreen); //移动到某点
}

void  CMyView::ReadVertics()// 此函数用来给数组St的元素赋顶点坐标值
{
      St[1][1]  = 40;    St[1][2]  = 154;    St[1][3]  =-20;
      St[2][1]  = 40;    St[2][2]  = 154;    St[2][3]  = 0;
      St[3][1]  = 40;    St[3][2]  =46;    St[3][3]  = 0;
      St[4][1]  = 40;    St[4][2]  =46;    St[4][3]  =-20;
      St[5][1]  =-40;    St[5][2]  =46;    St[5][3]  =-20;
      St[6][1]  =-40;    St[6][2]  = 154;    St[6][3]  =-20;
      St[7][1]  =-40;    St[7][2]  = 154;    St[7][3]  = 0;
      St[8][1]  = 0;     St[8][2]  = 134;    St[8][3]  = 40;
      St[9][1]  = 0;     St[9][2]  =66;    St[9][3]  = 40;
      St[10][1] =-40;    St[10][2] =46;    St[10][3] = 0;
}

void  CMyView::ReadFaces()// 此函数给数组Fc的元素赋表面有关的数据值
{
      NF= 9;
      Fc[1][0]=4;  Fc[1][1]=1;  Fc[1][2]=2;  Fc[1][3]=3;  Fc[1][4]=4;
      Fc[2][0]=4;  Fc[2][1]=1;  Fc[2][2]=6;  Fc[2][3]=7;  Fc[2][4]=2;
      Fc[3][0]=3;  Fc[3][1]=2;  Fc[3][2]=7;  Fc[3][3]=8;
      Fc[4][0]=4;  Fc[4][1]=2;  Fc[4][2]=8;  Fc[4][3]=9;  Fc[4][4]=3;
      Fc[5][0]=4;  Fc[5][1]=1;  Fc[5][2]=4;  Fc[5][3]=5;  Fc[5][4]=6;
      Fc[6][0]=4;  Fc[6][1]=7;  Fc[6][2]=10; Fc[6][3]=9;  Fc[6][4]=8;
      Fc[7][0]=3;  Fc[7][1]=3;  Fc[7][2]=9;  Fc[7][3]=10;
      Fc[8][0]=4;  Fc[8][1]=10; Fc[8][2]=5;  Fc[8][3]=4;  Fc[8][4]=3;
      Fc[9][0]=4;  Fc[9][1]=5;  Fc[9][2]=10; Fc[9][3]=7;  Fc[9][4]=6;
}

void  CMyView::VisionVector(int St1)  /* 该函数用于求观察方向矢量 St1 is the first point of a face.  */
{
       v1=O1-St[St1][1];
       v2=O2-St[St1][2];
       v3=O3-St[St1][3];
}

void  CMyView::NormalVector(int St1, int St2, int St3)// 此函数用表面三个顶点调用求该表面的法矢
  // St_i is the i_th point of a face. 
{
float   P1, P2, P3, Q1, Q2, Q3;
        // 求一个向量
	P1 = St[St2][1] - St[St1][1];
	P2 = St[St2][2] - St[St1][2];
	P3 = St[St2][3] - St[St1][3];
        // 求另一个向量
	Q1 = St[St3][1] - St[St1][1];
	Q2 = St[St3][2] - St[St1][2];
	Q3 = St[St3][3] - St[St1][3];
        //用向量积求法向量
	n1 = P2 * Q3 - Q2 * P3;
	n2 = P3 * Q1 - Q3 * P1;
	n3 = P1 * Q2 - Q1 * P2;
}

float  CMyView::ScaleProduct(float v1, float v2, float v3,
		    float n1, float n2, float n3)// 此函数用于求观察方向矢量与表面法矢的数量积
{
float   SProduct;
	SProduct = v1 * n1 + v2 * n2 + v3 * n3;
	return(SProduct);
}

void  CMyView::DrawFace(CDC*pDC)// 画出立体上的平面
{
int     S, NS, No;
float   X, Y, Z, X0, Y0, Z0;
	NS = Fc[F][0];
	for ( S = 1;  S<= NS;  S++ )
	{	    
	    No = Fc[F][S];
	    X = St[No][1];
	    Y = St[No][2];
	    Z = St[No][3];
		if ( S == 1 ) {
			  WMoveTo(X, Y, Z,pDC);
			  X0 = X;
			  Y0 = Y;
			  Z0 = Z;
		}
	    else  WLineTo(X, Y, Z,pDC);
	}
	WLineTo (X0, Y0, Z0,pDC);
}

void  CMyView::DrawObject()// 此函数用于绘出消隐立体图
   
{ int St1, St2, St3;
CDC*pDC=GetDC();
CPen pen1(PS_SOLID,1,(COLORREF)1),pen2(PS_DOT,1,(COLORREF)1);
CPen *pOldPen=pDC->SelectObject(&pen1);
	for ( F = 1;  F<= NF;  F++ )
	{	    
	    St1 = Fc[F][1];    St2 = Fc[F][2];    St3 = Fc[F][3];
	    VisionVector(St1); // 求观察方向矢量
	    NormalVector(St1, St2, St3); // 求表面法矢
	    if ( ScaleProduct( v1,v2,v3,n1,n2,n3 ) > 0 ) // 判断数量积正否
		{      
	       pDC->SelectObject(&pen1);
	       DrawFace(pDC); // 数量积大于零，表面可见，画出此表面
		}  
	    else;
	   }
	pDC->SelectObject(pOldPen);
	ReleaseDC(pDC);
}

void  CMyView::VisionPoint()// 此函数用于给出视点位置
{
  // 投影时初始值即正弦值和余弦值及其乘积的计算、赋值
	float  Th, Ph;
       Th   = 3.1415926 * Theta / 180;
       Ph   = 3.1415926 * Phi / 180;
       Aux1 = sin(Th);
       Aux2 = sin(Ph);
       Aux3 = cos(Th);
       Aux4 = cos(Ph);
       Aux5 = Aux3 * Aux2;
       Aux6 = Aux1 * Aux2;
       Aux7 = Aux3 * Aux4;
       Aux8 = Aux1 * Aux4;
      //给出视点位置
      O1 = Rol * Aux7;
      O2 = Rol * Aux8;
      O3 = Rol * Aux2;
}

void CMyView::Mydraw()
{
	RedrawWindow();
	ReadVertics();
	ReadFaces();
	// 绘出透视投影下的凸多面体图形
	VisionPoint(); // 给出视点位置
       DrawObject(); // 画出立体的图形
}

/////////////////////////////////////////////////////////////////////////////

void CMyView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{//此函数用来利用上下左右键移动视点角度位置,C键切换投影类型.
 //读者可以自己定义其他键值以及其他参数.
	switch(nChar){			
	case VK_UP:					//上下左右键选择		
		Phi=Phi-IncAng;
		Mydraw();
		break;
	case VK_DOWN:
		Phi=Phi+IncAng;
		Mydraw();
		break;
	case VK_RIGHT:
		Theta=Theta+IncAng;
		Mydraw();
		break;
	case VK_LEFT:
		Theta=Theta-IncAng;
		Mydraw();	
		break;
	default:
		break;
	}
}




void CMyView::OnTumianti() 
{//透视投影赋初值
	  Rol = 600.0;
 	  S=1;
 	  Theta = 60;
 	  Phi = 135;
 	  DE  = 1000;
 	   Mydraw();
 	   CDC*pDC=GetDC();
 	   pDC->TextOut(10,10,"按下键盘上的“上”、“下”、“左”、“右”箭头可从各方位观看图形");
 	   ReleaseDC(pDC);
}

void CMyView::OnYuanjin() 
{
	CClientDC *pdc=new CClientDC(this);
	CPen *pen1=new CPen(PS_SOLID,1,RGB(0,0XFF,0));
	CPen *pen2=new CPen(PS_SOLID,1,RGB(255,0,0));
	CPen *OldPen=pdc->SelectObject(pen1);

	CBrush brush;
    brush.CreateSolidBrush(RGB(0,0,0));
    CBrush *oldbrush=(CBrush*)pdc->SelectObject(&brush);
	int flag,k1,k2,r1,r2,n,d,m,p;
	int xs1,xs2,xs3,xs4,ys1,ys2,ys3,ys4,i,j,lastp;
	double x,y,z,thx,th1,th3,yw,zw,xw,thy,th2;
	double PI,ed,od,eh,zzw,ppw;
	double xs[50][17],zs[50][17],ys[50][17],zc[50][17],x1,y1;
	int zz[850],pp[850];

	r1=100;r2=40;k1=20;k2=16;ed=1500; eh=0;od=0;
	n=0;PI=3.14159;th3=1;thx=0.9;

	//计算顶点坐标值
for(d=-1;d<=1;d+=2){ 
	for(th1=0; th1<=2*PI+0.1;th1+=2*PI/k1){
        n=n+1; m=0;
       for(th2=0;th2<=2*PI+0.1;th2+=2*PI/k2){
            m=m+1;

		x=r1+r2*cos(th2);
		y=r2*sin(th2);
		z=0;
		thy=th1;

		//Call rot_y
		zw=z; xw=x;
		x=zw*cos(thy)-xw*sin(thy);
		z=zw*sin(thy)+xw*cos(thy);
		//
		x=x+r1/2*d;
   if(d==1)
   {
		yw=y;
		zw=z;
		y=yw*cos(PI/2)-zw*sin(PI/2);
		z=yw*sin(PI/2)+zw*cos(PI/2);
   }
			thy=th3;

			//Call rot_y 
			zw=z; xw=x;
			x=zw*cos(thy)-xw*sin(thy);
			z=zw*sin(thy)+xw*cos(thy);
			// Call rot_x:
			yw=y; zw=z;
			y=yw*cos(thx)-zw*sin(thx);
			z=yw*sin(thx)+zw*cos(thx);
			//Call pers
			x=x*ed/(ed-od-z);
			y=(y*ed-eh*(od+z))/(ed-od-z);

			xs[n][m]=x;
			ys[n][m]=y;
			zs[n][m]=z;
	   }
		//next th2
			
		flag=0;
		//Next th1
			}
		flag=0;	
		//Next d
	}
//计算center值
p=0;
  for(n=1;n<=k1;n+=1){
	  for(m=1;m<=k2;m+=1){
		zc[n][m]=int((zs[n][m]+zs[n+1][m+1])/2);
        zz[p]=zc[n][m];
        pp[p]=p;
        p=p+1;
    //Next m
    //Next n
	}
	}
 lastp=p-1;
 //排序
 for(i=2;i<=lastp;i+=1){
	   for(j=i-1;j>=0;j+=-1){
		 if(zz[j]>zz[j+1]) {
   zzw=zz[j];
   zz[j]=zz[j+1];
   zz[j+1]=zzw;
   ppw=pp[j];
   pp[j]=pp[j+1];
   pp[j+1]=ppw;
		 }
	 }
 }
  //绘图
	 for(p=0;p<=lastp;p+=1){
	  n=int(pp[p]/k2)+1;
	  m=pp[p]%k2+1;
	  if(n!=(k1+1)){
   
	  xs1=int(xs[n][m]);      ys1=int(ys[n][m]);
	  xs2=int(xs[n+1][m]);    ys2=int(ys[n+1][m]);
	  xs3=int(xs[n+1][m+1]);  ys3=int(ys[n+1][m+1]);
	  xs4=int(xs[n][m+1]);    ys4=int(ys[n][m+1]);
	  //}
  
	  if (abs(ys1*(xs2-xs3)+ys2*(xs3-xs1)+ys3*(xs1-xs2))>80){
		  pdc->MoveTo(xs1+320,ys1+200);
	pdc->SelectObject(pen1);
	  pdc->LineTo(xs2+320,ys2+200);
      pdc->LineTo(xs3+320,ys3+200);
      pdc->LineTo(xs4+320,ys4+200);
      pdc->LineTo(xs1+320,ys1+200);
  
  
	  //paint
  x=(xs[n][m]+xs[n+1][m+1])/2;
  y=(ys[n][m]+ys[n+1][m+1])/2;
  x1=int(x+320);
  y1=int(y+200);

  pdc->ExtFloodFill(x1,y1,RGB(0,255,0),0);
  //endif
  }

  pdc->MoveTo(xs1+320,ys1+200);
pdc->SelectObject(pen2);
	  pdc->LineTo(xs2+320,ys2+200);
      pdc->LineTo(xs3+320,ys3+200);
      pdc->LineTo(xs4+320,ys4+200);
      pdc->LineTo(xs1+320,ys1+200);
 }
 }
pdc->SelectObject(OldPen);
 delete pen1;
 delete pen2;
 pdc->DeleteDC();	
}
