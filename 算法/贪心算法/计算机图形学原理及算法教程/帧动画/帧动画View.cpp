// Ö¡¶¯»­View.cpp : implementation of the CMyView class
//

#include "stdafx.h"
#include "Ö¡¶¯»­.h"

#include "Ö¡¶¯»­Doc.h"
#include "Ö¡¶¯»­View.h"

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
	ON_COMMAND(ID_PLAY_FRAME, OnPlayFrame)
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
	flag=FALSE;
	index=0;
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
	if(flag)
	{
	pDC->SetStretchBltMode(COLORONCOLOR);
	pDC->StretchBlt(100, 50, m_sizeDest.cx, m_sizeDest.cy,
	                &m_pdcMemory[index], 0, 0,
	                m_sizeSource.cx, m_sizeSource.cy, SRCCOPY);
	}
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

void CMyView::OnPlayFrame() 
{
if(flag)
	{
		flag=FALSE;
		Invalidate();
	}
	else
		flag=TRUE;	
}

void CMyView::OnTimer(UINT nIDEvent) 
{
	if(flag)
	{

		if(index<5)
			index++;
		else
			index=0;
	   Invalidate();
	}
		CView::OnTimer(nIDEvent);
}

void CMyView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
	BITMAP bm; // Windows BITMAP data structure; see Win32 help
	m_pBitmap[0].LoadBitmap(IDB_BITMAP1);
	m_pBitmap[1].LoadBitmap(IDB_BITMAP2);
	m_pBitmap[2].LoadBitmap(IDB_BITMAP3);
	m_pBitmap[3].LoadBitmap(IDB_BITMAP4);
	m_pBitmap[4].LoadBitmap(IDB_BITMAP5);
	
	for(int i=0;i<5;i++)
	{
	
		CClientDC dc(this);
		OnPrepareDC(&dc); 
		m_pdcMemory[i].CreateCompatibleDC(&dc);
		m_pdcMemory[i].SelectObject(&m_pBitmap[i]);
		m_pBitmap[i].GetObject(sizeof(bm), &bm);
	
		m_sizeSource.cx = bm.bmWidth;
		m_sizeSource.cy = bm.bmHeight;
		m_sizeDest = m_sizeSource;
		dc.DPtoLP(&m_sizeDest);
	}
	int nTimer=SetTimer(1,700,NULL);
	ASSERT(nTimer!=0);	
}
