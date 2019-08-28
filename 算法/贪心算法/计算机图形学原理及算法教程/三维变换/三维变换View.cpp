// 三维变换View.cpp : implementation of the CMyView class
//

#include "stdafx.h"
#include "三维变换.h"
#include "BaseClass.h"
#include "三维变换Doc.h"
#include "三维变换View.h"
#include "math.h"
#define PI 3.141592654 
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
	ON_COMMAND(ID_TRANSLATION, OnTranslation)
	ON_COMMAND(ID_H, OnH)
	ON_COMMAND(ID_MIRROR_O, OnMirrorO)
	ON_COMMAND(ID_MIRROR_OXY, OnMirrorOxy)
	ON_COMMAND(ID_MIRROR_OYZ, OnMirrorOyz)
	ON_COMMAND(ID_MIRROR_OZX, OnMirrorOzx)
	ON_COMMAND(ID_MIRROR_X, OnMirrorX)
	ON_COMMAND(ID_MIRROR_Y, OnMirrorY)
	ON_COMMAND(ID_MIRROR_Z, OnMirrorZ)
	ON_COMMAND(ID_PRP, OnPrp)
	ON_COMMAND(ID_ROTATION_X, OnRotationX)
	ON_COMMAND(ID_ROTATION_Y, OnRotationY)
	ON_COMMAND(ID_SCALING_S, OnScalingS)
	ON_COMMAND(ID_SCALING_XYZ, OnScalingXyz)
	ON_COMMAND(ID_SH_X, OnShX)
	ON_COMMAND(ID_SH_Y, OnShY)
	ON_COMMAND(ID_V, OnV)
	ON_COMMAND(ID_W, OnW)
	ON_COMMAND(ID_SE, OnSe)
	ON_COMMAND(ID_ST, OnSt)
	ON_COMMAND(ID_VE, OnVe)
	ON_COMMAND(ID_VT, OnVt)
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_ROTATION_Z, OnRotationZ)
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
	// TODO: add construction code here
	m_Select=SEL_NONE;
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
	pDC->TextOut(10,10,"点击右键出现正立方体原图");
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

/////////////////////////////////////////////////////////////////////////////
// CMyView message handlers

void CMyView::OnTranslation() 
{
	// TODO: Add your command handler code here
	m_Select=SEL_TS;
	m_str="平移";
	CBaseClass my1;  //构造新的CBaseClass对象
		int i,j;
	
	for ( i=1;i<=4;++i)
		{
			for ( j=1;j<=4;++j)
				my1.A[i][j]=0;
		}
		my1.A[1][1]=1;
		my1.A[2][2]=1;
		my1.A[4][4]=1;
		my1.A[3][3]=1;
	my1.A[4][1]=6;    //x轴方向上平移
		my1.A[4][2]=4;	 //y轴方向上平移
		my1.A[4][3]=4;	 //z轴方向上平移
//		RedrawWindow();
	my1.Draw();
}

void CMyView::OnH() 
{
	// TODO: Add your command handler code here
	m_Select=SEL_H;
	m_str="俯视图";
		int i,j;
		CBaseClass my1;  //构造新的CMyClass对象
		
		//将俯视图变换矩阵清零
		for (i=1;i<=4;++i)
		{
			for (j=1;j<=4;++j)
				my1.Ah[i][j]=0;
		}
		//给俯视图变换矩阵赋值
		my1.Ah[1][1]=1;
		my1.Ah[2][3]=-1;
	//	my1.Ah[4][3]=10;   //俯视图平移量
		my1.Ah[4][4]=1;
		RedrawWindow();
	my1.Display();
	}


void CMyView::OnMirrorO() 
{
	// TODO: Add your command handler code here
m_Select=SEL_MO;
	m_str="关于原点对称";
	CBaseClass my1;  //构造新的CBaseClass对象
	
		int i,j;
	
	for ( i=1;i<=4;++i)
		{
			for ( j=1;j<=4;++j)
				my1.A[i][j]=0;
		}
		my1.A[1][1]=-1;
		my1.A[2][2]=-1;
		my1.A[3][3]=-1;
		my1.A[4][4]=1;
	//	RedrawWindow();
	my1.Draw();
}
	


void CMyView::OnMirrorOxy() 
{
	// TODO: Add your command handler code here
	m_Select=SEL_MOXY;
	m_str="关于OXY平面对称";
	CBaseClass my1;  //构造新的CBaseClass对象
			int i,j;
	
	for ( i=1;i<=4;++i)
		{
			for ( j=1;j<=4;++j)
				my1.A[i][j]=0;
		}
		my1.A[1][1]=1;
		my1.A[2][2]=1;
		my1.A[3][3]=-1;
		my1.A[4][4]=1;
	//RedrawWindow();
	my1.Draw();
}

void CMyView::OnMirrorOyz() 
{
	// TODO: Add your command handler code here
m_Select=SEL_MOYZ;
	m_str="关于OYZ平面对称";
	CBaseClass my1;  //构造新的CBaseClass对象
		int i,j;
	
	for ( i=1;i<=4;++i)
		{
			for ( j=1;j<=4;++j)
				my1.A[i][j]=0;
		}
		my1.A[1][1]=-1;
		my1.A[2][2]=1;
		my1.A[3][3]=1;
		my1.A[4][4]=1;
	//	RedrawWindow();
	my1.Draw();	
}

void CMyView::OnMirrorOzx() 
{
	// TODO: Add your command handler code here
m_Select=SEL_MOZX;
	m_str="关于OZX平面对称";
	CBaseClass my1;  //构造新的CBaseClass对象
	
		int i,j;
	
	for ( i=1;i<=4;++i)
		{
			for ( j=1;j<=4;++j)
				my1.A[i][j]=0;
		}
		my1.A[1][1]=1;
		my1.A[2][2]=-1;
		my1.A[3][3]=1;
		my1.A[4][4]=1;
		RedrawWindow();
	my1.Draw();
}

void CMyView::OnMirrorX() 
{
	// TODO: Add your command handler code here
m_Select=SEL_MX;
	m_str="关于X对称";
	CBaseClass my1;  //构造新的CBaseClass对象
	
		int i,j;
	
	for ( i=1;i<=4;++i)
		{
			for ( j=1;j<=4;++j)
				my1.A[i][j]=0;
		}
		my1.A[1][1]=1;
		my1.A[2][2]=-1;
		my1.A[3][3]=-1;
		my1.A[4][4]=1;
//		RedrawWindow();
	my1.Draw();
}

void CMyView::OnMirrorY() 
{
	// TODO: Add your command handler code here
m_Select=SEL_MY;
	m_str="关于Y对称";
	CBaseClass my1;  //构造新的CBaseClass对象
	
		int i,j;
	
	for ( i=1;i<=4;++i)
		{
			for ( j=1;j<=4;++j)
				my1.A[i][j]=0;
		}
		my1.A[1][1]=-1;
		my1.A[2][2]=1;
		my1.A[3][3]=-1;
		my1.A[4][4]=1;
//		RedrawWindow();
	my1.Draw();	
}

void CMyView::OnMirrorZ() 
{
	// TODO: Add your command handler code here
m_Select=SEL_MZ;
	m_str="关于Z对称";
	CBaseClass my1;  //构造新的CBaseClass对象

		int i,j;
	
	for ( i=1;i<=4;++i)
		{
			for ( j=1;j<=4;++j)
				my1.A[i][j]=0;
		}
		my1.A[1][1]=-1;
		my1.A[2][2]=-1;
		my1.A[3][3]=1;
		my1.A[4][4]=1;
	//	RedrawWindow();
	my1.Draw();
}

void CMyView::OnPrp() 
{
	// TODO: Add your command handler code here
		m_Select=SEL_PRP;
		m_str="透视图";
	CBaseClass my1;
	my1.ps=1;
		int i,j;
	
	for ( i=1;i<=4;++i)
		{
			for ( j=1;j<=4;++j)
				my1.A[i][j]=0;
		}
		my1.A[1][1]=1;
		my1.A[2][2]=1;
		my1.A[3][3]=1;
		my1.A[4][4]=1;
		RedrawWindow();
	my1.Draw();
//	my1.DrawText();
}

void CMyView::OnRotationX() 
{
	// TODO: Add your command handler code here
//	RedrawWindow();
	m_Select=SEL_RX;
	m_str="关于X轴旋转";
	CBaseClass my1;  //构造新的CBaseClass对象
			int i,j;
	
	for ( i=1;i<=4;++i)
		{
			for ( j=1;j<=4;++j)
				my1.A[i][j]=0;
		}
		my1.A[1][1]=1;
		my1.A[2][2]=cos(60*PI/180);//旋转60度
		my1.A[3][2]=sin(60*PI/180);
		my1.A[2][3]=-sin(60*PI/180);
		my1.A[3][3]=cos(60*PI/180);
		my1.A[4][4]=1;
		my1.Draw();
}

void CMyView::OnRotationY() 
{
	// TODO: Add your command handler code here
m_Select=SEL_RY;
	m_str="关于Y轴旋转";
	CBaseClass my1;  //构造新的CBaseClass对象

		int i,j;
	
	for ( i=1;i<=4;++i)
		{
			for ( j=1;j<=4;++j)
				my1.A[i][j]=0;
		}
		my1.A[2][2]=1;
		my1.A[1][1]=cos(60*PI/180);//旋转60度
		my1.A[3][1]=sin(60*PI/180);
		my1.A[1][3]=-sin(60*PI/180);
		my1.A[3][3]=cos(60*PI/180);
		my1.A[4][4]=1;
	//	RedrawWindow();
	my1.Draw();	
}

void CMyView::OnScalingS() 
{
	// TODO: Add your command handler code here
m_Select=SEL_MO;
	m_str="整体变比";
	CBaseClass my1;  //构造新的CBaseClass对象
			int i,j;
	
	for ( i=1;i<=4;++i)
		{
			for ( j=1;j<=4;++j)
				my1.A[i][j]=0;
		}
		my1.A[1][1]=1;
		my1.A[2][2]=1;
		my1.A[3][3]=1;
		my1.A[4][4]=0.5;
	//	RedrawWindow();
		my1.Draw();
}

void CMyView::OnScalingXyz() 
{
	// TODO: Add your command handler code here
m_Select=SEL_MO;
	m_str="XYZ变比";
	CBaseClass my1;  //构造新的CBaseClass对象
		int i,j;
	
	for ( i=1;i<=4;++i)
		{
			for ( j=1;j<=4;++j)
				my1.A[i][j]=0;
		}
		my1.A[1][1]=2;   //x轴方向上比例
		my1.A[2][2]=1;   //y轴方向上比例
		my1.A[3][3]=1;   //z轴方向上比例
		my1.A[4][4]=1;
	//	RedrawWindow();
		my1.Draw();
}

void CMyView::OnShX() 
{
	// TODO: Add your command handler code here
m_Select=SEL_SHX;
	m_str="X方向错切";
	CBaseClass my1;  //构造新的CBaseClass对象
		int i,j;
	
	for ( i=1;i<=4;++i)
		{
			for ( j=1;j<=4;++j)
				my1.A[i][j]=0;
		}
		my1.A[1][1]=1;   
		my1.A[2][2]=1;   
		my1.A[3][3]=1;   
		my1.A[4][4]=1;
		my1.A[1][2]=0.5;   //为0错切平面离开Z轴，沿X方向移动
		my1.A[1][3]=0.5;		//为0错切平面离开Y轴，沿X方向移动

//		RedrawWindow();
		my1.Draw();		
}

void CMyView::OnShY() 
{
	// TODO: Add your command handler code here
	m_Select=SEL_SHY;
	m_str="Y方向错切";
	CBaseClass my1;  //构造新的CBaseClass对象
		int i,j;
	
	for ( i=1;i<=4;++i)
		{
			for ( j=1;j<=4;++j)
				my1.A[i][j]=0;
		}
		my1.A[1][1]=1;   
		my1.A[2][2]=1;   
		my1.A[3][3]=1;   
		my1.A[4][4]=1;
		my1.A[1][2]=0.5;		//为0错切平面离开Z轴，沿Y方向移动
		my1.A[3][2]=0.5;		//为0错切平面离开X轴，沿Y方向移动
	//	RedrawWindow();
		my1.Draw();	
		
}


void CMyView::OnV() 
{
	// TODO: Add your command handler code here
m_Select=SEL_V;
	m_str="主视图";
		int i,j;
		CBaseClass my1;  //构造新的CMyClass对象
		
		//将主视图变换矩阵清零
		for ( i=1;i<=4;++i)
		{
			for ( j=1;j<=4;++j)
				my1.A[i][j]=0;
		}
		//给主视图变换矩阵赋值
		my1.A[1][1]=1;
		my1.A[3][3]=1;
		my1.A[4][4]=1;
		RedrawWindow();
		my1.Display();
	

}

void CMyView::OnW() 
{
		// TODO: Add your command handler code here
		m_Select=SEL_H;
		m_str="侧视图";
		int i,j;
		CBaseClass my1;  //构造新的CMyClass对象
		//将俯视图变换矩阵清零
		//将侧视图变换矩阵清零
		for (i=1;i<=4;++i)
		{
			for (j=1;j<=4;++j)
				my1.Aw[i][j]=0;
		}
		//给侧视图变换矩阵赋值
		my1.Aw[2][1]=-1;
		my1.Aw[3][3]=1;
		my1.Aw[4][4]=1;
		RedrawWindow();
		my1.Display();	
}

void CMyView::OnSe() 
{
	// TODO: Add your command handler code here
		m_Select=SEL_SE;
	m_str="斜等测视图";
		int i,j;
		CBaseClass my1;  //构造新的CBaseClass对象
						
		for ( i=1;i<=4;++i)
		{
			for ( j=1;j<=4;++j)
				my1.A[i][j]=0;
		}
		my1.A[1][1]=1;
		my1.A[2][2]=1;
		my1.A[3][1]=0.707f;    //X方向错切位移量
		my1.A[3][2]=0.707f;   //Y方向错切位移量
		my1.A[4][4]=1;
		RedrawWindow();
		my1.Drawse();
	
}

void CMyView::OnSt() 
{
	// TODO: Add your command handler code here
m_Select=SEL_ST;
	m_str="斜二测视图";
		int i,j;
		CBaseClass my1;  //构造新的CMyClass对象
		for ( i=1;i<=4;++i)
		{
			for ( j=1;j<=4;++j)
				my1.A[i][j]=0;
		}
		my1.A[1][1]=1;
		my1.A[2][2]=1;
		my1.A[3][1]=0.3535f;       //X方向错切位移量
		my1.A[3][2]=0.3535f;       //Y方向错切位移量
		my1.A[4][4]=1;
		RedrawWindow();
		my1.Drawvt();
		
}

void CMyView::OnVe() 
{
	// TODO: Add your command handler code here
m_Select=SEL_VE;
	m_str="正等测视图";
		int i,j;
		CBaseClass my2;  //构造新的CMyClass对象
		my2.theta_y =45;      //Y轴夹角
		my2.phi_x=125;     //X轴夹角
				
		//给正等测变换矩阵清零
		for ( i=1;i<=4;++i)
		{
			for ( j=1;j<=4;++j)
				my2.A[i][j]=0;
		}
		//给正等测变换矩阵赋值
		my2.A[1][1]=(float)cos(my2.theta_y*PI/180);
		my2.A[1][2]=(float)sin(my2.theta_y*PI/180)*(float)sin(my2.phi_x*PI/180);
		my2.A[2][2]=(float)cos(my2.phi_x*PI/180);
		my2.A[3][1]=(float)sin(my2.theta_y*PI/180);
		my2.A[3][2]=(float)-cos(my2.theta_y*PI/180)*(float)sin(my2.phi_x*PI/180);
		my2.A[4][4]=1;

		RedrawWindow();
		my2.Drawve();
}

void CMyView::OnVt() 
{
	// TODO: Add your command handler code here
	m_Select=SEL_VT;
	m_str="正二测视图";
	
		int i,j;
		CBaseClass my2;  //构造新的CMyClass对象
		my2.theta_y =115;    //Y轴夹角25-115
		my2.phi_x=25;      //X轴夹角
				
		//给正二测变换矩阵清零
		for ( i=1;i<=4;++i)
		{
			for ( j=1;j<=4;++j)
				my2.A[i][j]=0;
		}
		//给正二测变换矩阵赋值
		my2.A[1][1]=(float)cos(my2.theta_y*PI/180);
		my2.A[1][2]=(float)sin(my2.theta_y*PI/180)*(float)sin(my2.phi_x*PI/180);
		my2.A[2][2]=(float)cos(my2.phi_x*PI/180);
		my2.A[3][1]=(float)sin(my2.theta_y*PI/180);
		my2.A[3][2]=(float)-cos(my2.theta_y*PI/180)*(float)sin(my2.phi_x*PI/180);
		my2.A[4][4]=1;

		RedrawWindow();
		my2.Drawvt();
		
}




void CMyView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	m_str="原三维图形";
	CBaseClass my1;  //构造新的CBaseClass对象
	
		int i,j;
	
			for ( i=1;i<=4;++i)
		{
			for ( j=1;j<=4;++j)
				my1.A[i][j]=0;
		}
		my1.A[1][1]=1;
		my1.A[2][2]=1;
		my1.A[3][3]=1;
		my1.A[4][4]=1;
		RedrawWindow();
		my1.Draw();
	CView::OnRButtonDown(nFlags, point);
}


void CMyView::OnRotationZ() 
{
	// TODO: Add your command handler code here
m_Select=SEL_RZ;
	m_str="关于Z轴旋转";
	CBaseClass my1;  //构造新的CBaseClass对象
			int i,j;
	
	for ( i=1;i<=4;++i)
		{
			for ( j=1;j<=4;++j)
				my1.A[i][j]=0;
		}
		my1.A[3][3]=1;
		my1.A[1][1]=cos(60*PI/180);//旋转60度
		my1.A[1][2]=sin(60*PI/180);
		my1.A[2][1]=-sin(60*PI/180);
		my1.A[2][2]=cos(60*PI/180);
		my1.A[4][4]=1;
//		RedrawWindow();
		my1.Draw();		
}


