// 图形裁剪View.cpp : implementation of the CMyView class
//

#include "stdafx.h"
#include "图形裁剪.h"

#include "图形裁剪Doc.h"
#include "图形裁剪View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define LEFT 1
#define RIGHT 2
#define BOTTOM 4
#define  TOP 8

#define XL 100
#define XR 300
#define YT 100
#define YB 250

/////////////////////////////////////////////////////////////////////////////
// CMyView

IMPLEMENT_DYNCREATE(CMyView, CView)

BEGIN_MESSAGE_MAP(CMyView, CView)
	//{{AFX_MSG_MAP(CMyView)
	ON_COMMAND(ID_CLIPLINE, OnClipline)
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_CLIPPOLYGON, OnClippolygon)
	ON_WM_RBUTTONDBLCLK()
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
	CPen newpen(PS_SOLID,1,RGB(255,0,0));
	CPen *old=pDC->SelectObject(&newpen);
	pDC->Rectangle(CRect(XL,YT,XR,YB));//剪切窗口
//	ptset[0]=CPoint(200,190);
//	ptset[1]=CPoint(550,150);
	ptset[0]=CPoint(120,150);
	ptset[1]=CPoint(170,110);
    ptset[2]=CPoint(0,190);
	ptset[3]=CPoint(350,150);
	ptset[4]=CPoint(0,250);
	ptset[5]=CPoint(150,230);
	ptset[6]=CPoint(200,50);
	ptset[7]=CPoint(120,150);
	ptset1[0]=CPoint(20,150);
	ptset1[1]=CPoint(170,110);
   
	ptset1[2]=CPoint(250,150);

	ptset1[3]=CPoint(200,230);

	ptset1[4]=CPoint(20,150);
	pDC->TextOut(0,20,"双击鼠标左键，出现要剪切的线段");
	pDC->TextOut(0,50,"双击鼠标右键，出现要剪切的多边形");
	pDC->SelectObject(old);
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

void CMyView::OnClipline() 
{
	// TODO: Add your command handler code here
	CDC* pDC=GetDC();
	CPen newpen(PS_SOLID,1,RGB(255,0,0));
	CPen *old=pDC->SelectObject(&newpen);
	if(flag!=1) 
	{MessageBox("请先双击鼠标左键","警告！");}	
	else
	{
	float x,y;
	int i;
	int code1,code2;
			RedrawWindow();
	// 求两端点所在区号code
	for(i=0;i<N;i++,i++)
	{
		int c=0;
		if(ptset[i].x<XL) c=c|LEFT;
		else if (ptset[i].x>XR)c=c|RIGHT;
		if(ptset[i].y>YB) c=c|BOTTOM;
		else if(ptset[i].y<YT) c=c|TOP;
		code1=c;
		 c=0;
		if(ptset[i+1].x<XL) c=c|LEFT;
		else if(ptset[i+1].x>XR) c=c|RIGHT;
		if(ptset[i+1].y>YB) c=c|BOTTOM;
		else if(ptset[i+1].y<YT) c=c|TOP;
		code2=c;
	//线段与区域的相交情况
	if(code1!=0&&code2!=0&&(code1&code2)==0)
	{	
		if((LEFT&code1)!=0) 	        //线段与左边界相交
		{
		x=XL;
		y=(float)ptset[i].y+(ptset[i+1].y-ptset[i].y)*(XL-ptset[i].x)/(ptset[i+1].x-ptset[i].x);
		}
		else if((RIGHT&code1)!=0)          //线段与右边界相交
		{
		x=XR;
		y=(float)ptset[i].y+(ptset[i+1].y-ptset[i].y)*(XR-ptset[i].x)/(ptset[i+1].x-ptset[i].x);
		}
	
		else if((BOTTOM&code1)!=0)          //线段与下边界相交
		{
		y=YB;
		x=(float)ptset[i].x+(ptset[i+1].x-ptset[i].x)*(YB-ptset[i].y)/(ptset[i+1].y-ptset[i+1].y);
		}
		else if((TOP&code1)!=0)          //线段与上边界相交
		{
		y=YT;
		x=(float)ptset[i].x+(ptset[i+1].x-ptset[i].x)*(YT-ptset[i].y)/(ptset[i+1].y-ptset[i].y);
		}
	//	x1=x;
	//	y1=y;
		ptset[i].x=(long)x;
		ptset[i].y=(long)y;	
		if((LEFT&code2)!=0) 	        //线段与左边界相交
		{
		x=XL;
		y=(float)ptset[i].y+(ptset[i+1].y-ptset[i].y)*(XL-ptset[i].x)/(ptset[i+1].x-ptset[i].x);
		}
		else if((RIGHT&code2)!=0)          //线段与右边界相交
		{
		x=XR;
		y=(float)ptset[i].y+(ptset[i+1].y-ptset[i].y)*(XR-ptset[i].x)/(ptset[i+1].x-ptset[i].x);
		}
	
		else if((BOTTOM&code2)!=0)          //线段与下边界相交
		{
		y=YB;
		x=(float)ptset[i].x+(ptset[i+1].x-ptset[i].x)*(YB-ptset[i].y)/(ptset[i+1].y-ptset[i+1].y);
		}
		else if((TOP&code2)!=0)          //线段与上边界相交
		{
		y=YT;
		x=(float)ptset[i].x+(ptset[i+1].x-ptset[i].x)*(YT-ptset[i].y)/(ptset[i+1].y-ptset[i].y);
		}
		ptset[i+1].x=(long)x;
		ptset[i+1].y=(long)y;	
		pDC->MoveTo(ptset[i].x,ptset[i].y);
		pDC->LineTo(ptset[i+1].x,ptset[i+1].y);
	}	
	if(code1==0&&code2==0)
	{pDC->MoveTo(ptset[i].x,ptset[i].y);
		pDC->LineTo(ptset[i+1].x,ptset[i+1].y);
	}
	if(code1==0&&code2!=0)
	{
		pDC->MoveTo(ptset[0].x,ptset[0].y);	
		if((LEFT&code2)!=0) 	        //线段与左边界相交
		{
		x=XL;
		y=(float)ptset[i].y+(ptset[i+1].y-ptset[i].y)*(XL-ptset[i].x)/(ptset[i+1].x-ptset[i].x);
		}
		else if((RIGHT&code2)!=0)          //线段与右边界相交
		{
		x=XR;
		y=(float)ptset[i].y+(ptset[i+1].y-ptset[i].y)*(XR-ptset[i].x)/(ptset[i+1].x-ptset[i].x);
		}
	
		else if((BOTTOM&code2)!=0)          //线段与下边界相交
		{
		y=YB;
		x=(float)ptset[i].x+(ptset[i+1].x-ptset[i].x)*(YB-ptset[i].y)/(ptset[i+1].y-ptset[i+1].y);
		}
		else if((TOP&code2)!=0)          //线段与上边界相交
		{
		y=YT;
		x=(float)ptset[i].x+(ptset[i+1].x-ptset[i].x)*(YT-ptset[i].y)/(ptset[i+1].y-ptset[i].y);
		}
		
		ptset[i+1].x=(long)x;
		ptset[i+1].y=(long)y;
		
		pDC->LineTo(ptset[i+1].x,ptset[i+1].y);
	}
			
	if(code1!=0&&code2==0)
	{
		pDC->MoveTo(ptset[i+1].x,ptset[i+1].y);
		if((LEFT&code1)!=0) 	        //线段与左边界相交
		{
		x=XL;
		y=(float)ptset[i].y+(ptset[i+1].y-ptset[i].y)*(XL-ptset[i].x)/(ptset[i+1].x-ptset[i].x);
		}
		else if((RIGHT&code1)!=0)          //线段与右边界相交
		{
		x=XR;
		y=(float)ptset[i].y+(ptset[i+1].y-ptset[i].y)*(XR-ptset[i].x)/(ptset[i+1].x-ptset[i].x);
		}
	
		else if((BOTTOM&code1)!=0)          //线段与下边界相交
		{
		y=YB;
		x=(float)ptset[i].x+(ptset[i+1].x-ptset[i].x)*(YB-ptset[i].y)/(ptset[i+1].y-ptset[i+1].y);
		}
		else if((TOP&code1)!=0)          //线段与上边界相交
		{
		y=YT;
		x=(float)ptset[i].x+(ptset[i+1].x-ptset[i].x)*(YT-ptset[i].y)/(ptset[i+1].y-ptset[i].y);
		}
		
		ptset[i].x=(long)x;
		ptset[i].y=(long)y;
		pDC->LineTo(ptset[i].x,ptset[i].y);
	}
	}
	}		
}

void CMyView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CDC* pDC=GetDC();
	CPen newpen(PS_SOLID,1,RGB(255,0,0));
	CPen *old=pDC->SelectObject(&newpen);
	flag=1;	
	for(int i=0;i<N;i++)
	{
		pDC->MoveTo(ptset[i]);
	pDC->LineTo(ptset[i+1]);
	i++;
	}
	CView::OnLButtonDblClk(nFlags, point);
}

void CMyView::OnClippolygon() 
{
	// TODO: Add your command handler code here
		CDC* pDC=GetDC();
	CPen newpen(PS_SOLID,1,RGB(255,0,0));
	CPen *old=pDC->SelectObject(&newpen);
if(flag!=2)
{ MessageBox("请先双击鼠标右键","警告！");}
else{
//else	
	int i,k;
	int code1,code2;
	int	M=5;
	RedrawWindow();
	// 求两端点所在区号code
	k=0;
	for(i=0;i<M;i++)
	{	
		int c=0;
		if(ptset1[i].x<XL) c=1;
		else if (ptset1[i].x>XL)c=0;
		code1=c;
		 c=0;
		if(ptset1[i+1].x<XL) c=1;
		else if(ptset1[i+1].x>XL) c=0;
		code2=c;
		if(code1!=0&&code2==0)
		{
			pt[k].x=XL;
			pt[k].y=ptset1[i].y+(ptset1[i+1].y-ptset1[i].y)*(XL-ptset1[i].x)/(ptset1[i+1].x-ptset1[i].x);
			pt[k+1].x=ptset1[i+1].x;
			pt[k+1].y=ptset1[i+1].y;
			k=k+2;
		}				
		if(code1==0&&code2==0)
		{			
			if(k==0)
			{
				pt[k].x=ptset1[i].x;
				pt[k].y=ptset1[i].y;
				pt[k+1].x=ptset1[i+1].x;
				pt[k+1].y=ptset1[i+1].y;
				k=k+2;
			}
			if(k!=0)
			{
				pt[k].x=ptset1[i+1].x;
				pt[k].y=ptset1[i+1].y;
				k=k+1;
			}
		}
		if(code1==0&&code2!=0)
		{
			pt[k].x=XL;
			pt[k].y=ptset1[i].y+(ptset1[i+1].y-ptset1[i].y)*(XL-ptset1[i].x)/(ptset1[i+1].x-ptset1[i].x);
			k++;
		}						
	}
			pt[k].x=pt[0].x;
			pt[k].y=pt[0].y;
			M=k+1;
//	if(k==6)
		
//		pDC->MoveTo(pt[0].x,pt[0].y);

//	for(i=1;i<M;i++)
//	{	pDC->LineTo(pt[i].x,pt[i].y);
//	}
	
	k=0;		
	for(i=0;i<M;i++)
	{		
		int c=0;
		if(pt[i].x<XR) c=0;
		else if(pt[i].x>XR) c=2;
		code1=c;
		 c=0;
		if(pt[i+1].x<XR) c=0;
		else if(pt[i+1].x>XR) c=2;
		code2=c;
	if(code1==0&&code2==0)
	{
		if(k==0)
		{
			pts[k].x=pt[i].x;
			pts[k].y=pt[i].y;
			pts[k+1].x=pt[i+1].x;
			pts[k+1].y=pt[i+1].y;
			k=k+2;
		}
		if(k!=0)
		{
			pts[k].x=pt[i+1].x;
			pts[k].y=pt[i+1].y;
			k++;
		}
	}
	if(code1!=0&&code2==0)
		{
			
			pts[k].x=XR;
			pts[k].y=pt[i].y+(pt[i+1].y-pt[i].y)*(XR-pt[i].x)/(pt[i+1].x-pt[i].x);
			pts[k+1].x=pt[i+1].x;
			pts[k+1].y=pt[i+1].y;
			k=k+2;
		}	
	
		if(code1==0&&code2!=0)
		{
			pts[k].x=XR;
			pts[k].y=pt[i].y+(pt[i+1].y-pt[i].y)*(XR-pt[i].x)/(pt[i+1].x-pt[i].x);
			k=k+1;
		}		
	}
	//增加对最后一条边的判断
	pts[k]=pts[0];
		M=k+1;
//	pDC->MoveTo(pts[0].x,pts[0].y);

//	for(i=1;i<M;i++)
//	{	pDC->LineTo(pts[i].x,pts[i].y);
//	}

			k=0;
	for(i=0;i<M;i++)
	{			
		int c=0;
		if(pts[i].y>YB) c=4;
		else if(pts[i].y<YB) c=0;
		code1=c;
		 c=0;
		if(pts[i+1].y>YB) c=4;
		else if(pts[i+1].y<YB) c=0;
		code2=c;	
		
		if(code1==0&&code2==0)
		{
			if(k==0)
			{
				ptse[k].x=pts[i].x;
				ptse[k].y=pts[i].y;
				ptse[k+1].x=pts[i+1].x;
				ptse[k+1].y=pts[i+1].y;
				k=k+2;
			}
			if(k!=0)
			{
				ptse[k].x=pts[i+1].x;
				ptse[k].y=pts[i+1].y;
				k=k+1;
			}
		}
		
		
	if(code1!=0&&code2==0)
		{
			ptse[k].y=YB;
			ptse[k].x=pts[i].x+(pts[i+1].x-pts[i].x)*(YB-pts[i].y)/(pts[i+1].y-pts[i+1].y);
			ptse[k+1].x=pts[i+1].x;
			ptse[k+1].y=pts[i+1].y;
			k=k+2;
		}
	}
	if(code1==0&&code2!=0)
		{
			ptse[k].y=YB;
			ptse[k].x=pts[i].x+(pts[i+1].x-pts[i].x)*(YB-pts[i].y)/(pts[i+1].y-pts[i+1].y);
			k=k+1;
		}
	ptse[k]=ptse[0];		
	M=k+1;
//	pDC->MoveTo(ptse[0].x,ptse[0].y);
			
//	for(int j=1;j<M;j++)
//	{	pDC->LineTo(ptse[j].x,ptse[j].y);
//	}
			k=0;
	for(i=0;i<M;i++)
	{	
		int c=0;
		if(ptse[i].y>YT) c=0;
		else if(ptse[i].y<YT) c=1;
		code1=c;
		c=0;
		if(ptse[i+1].y>YT) c=0;
		else if(ptse[i+1].y<YT) c=1;
		code2=c;
		if(code1!=0&&code2==0)
		{
			p[k].y=YT;
			p[k].x=ptse[i].x+(ptse[i+1].x-ptse[i].x)*(YT-ptse[i].y)/(ptse[i+1].y-ptse[i].y);
			p[k+1].x=ptse[i+1].x;
			p[k+1].y=ptse[i+1].y;
			k=k+2;
		}
		if(code1==0&&code2==0)
		{
			if(k==0)
			{
				p[k].x=ptse[i].x;
				p[k].y=ptse[i].y;
				p[k+1].x=ptse[i+1].x;
				p[k+1].y=ptse[i+1].y;
				k=k+2;
			}
			if(k!=0)
			{
				p[k].x=ptse[i+1].x;
				p[k].y=ptse[i+1].y;
				k=k+1;
			}
		}
		if(code1==0&&code2!=0)
		{
			p[k].y=YT;
			p[k].x=ptse[i].x+(ptse[i+1].x-ptse[i].x)*(YT-ptse[i].y)/(ptse[i+1].y-ptse[i].y);
			k++;
		}
	}
	p[k]=p[0];
			M=k+1;
	pDC->MoveTo(p[0]);
	for(int j=1;j<=M;j++)
	{
		pDC->LineTo(p[j]);
	}
	}
}

void CMyView::OnRButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
CDC* pDC=GetDC();
	CPen newpen(PS_SOLID,1,RGB(255,0,0));
	CPen *old=pDC->SelectObject(&newpen);
	flag=2;	
	pDC->MoveTo(ptset1[0]);
	for(int i=1;i<5;i++)
	{
		
	pDC->LineTo(ptset1[i]);
	
	}
	CView::OnRButtonDblClk(nFlags, point);
}


