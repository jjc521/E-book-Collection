// 实时动画View.cpp : implementation of the CMyView class
//

#include "stdafx.h"
#include "实时动画.h"

#include "实时动画Doc.h"
#include "实时动画View.h"
#include "Sphere.h"

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
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_TIMER()
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
		x = 9;
	y = 30;
	m_nSpeedX = 9;
	m_nSpeedY = 1;

	m_bPlay = TRUE;
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
		CRect rect;
	GetClientRect(&rect);
	int nClientWidth = rect.Width();
	int nClientHeight = rect.Height();
	
	CDC memDC;
	memDC.CreateCompatibleDC(pDC);

	CBitmap bitmap;
	bitmap.CreateCompatibleBitmap(pDC,  nClientWidth,  nClientHeight);
	CBitmap* pOldBitmap = memDC.SelectObject(&bitmap);
	CBrush* pBrush = new CBrush(RGB(0,  0,  0));
	memDC.FillRect(rect, pBrush);
	delete pBrush;
	
	DrawSphere(&memDC,  x,  y);
	pDC->BitBlt(0,  0,  nClientWidth,  nClientHeight,  &memDC,  0,  0,  SRCCOPY);	
	memDC.SelectObject(pOldBitmap);
	bitmap.DeleteObject();	
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


int CMyView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	SetTimer(1,  45,  NULL);
	
	return 0;
}

void CMyView::OnDestroy() 
{
	CView::OnDestroy();
	
	if(m_bPlay)	KillTimer(1);// TODO: Add your message handler code here
	
}

void CMyView::OnTimer(UINT nIDEvent) 
{
		CRect rect;
	GetClientRect(&rect);
	int nClientWidth = rect.Width();
	int nClientHeight = rect.Height();
	
	x += m_nSpeedX;
	
	//控制 x 坐标
	if( x > nClientWidth - 25)
	{
		x = nClientWidth - 25;
		m_nSpeedX = -m_nSpeedX;
	}
	else if(x < 9)
	{
		x = 9;
		m_nSpeedX = -m_nSpeedX;
	}

	//控制 y 坐标
	y += m_nSpeedY;
	m_nSpeedY++;

	if(y > (nClientHeight - 26))
	{
		y = 2 * (nClientHeight - 26) - y;
		m_nSpeedY = -m_nSpeedY + 4;
	}
	else if( y < 30)y = 30;

	Invalidate(FALSE);

	CView::OnTimer(nIDEvent);
}
//绘制小球(运动部件)
void CMyView::DrawSphere(CDC *pDC,  int x,  int y)
{
	//半径为 36 个像素单位
	//其它采用缺省设置
	CSphere vs(36);
	vs.SetColor(255,  255,  255);

	vs.Draw(pDC,  x,  y);
}

