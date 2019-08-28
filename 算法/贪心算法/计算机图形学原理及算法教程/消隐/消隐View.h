// 消隐View.h : interface of the CMyView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_VIEW_H__55118D9A_9F86_4469_BEBD_56716DBE060A__INCLUDED_)
#define AFX_VIEW_H__55118D9A_9F86_4469_BEBD_56716DBE060A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define       Scale    1.35
#define       MaxSt    50
#define       MaxFc    30
#define       MaxAt    10
#define       IncAng   5
#define       IncRol   15
#define       IncSn    15
#define       IncS     1.5

class CMyView : public CView
{
protected: // create from serialization only
	CMyView();
	DECLARE_DYNCREATE(CMyView)

// Attributes
public:
	CMyDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyView();
	void  Project(float X, float Y, float Z);
	void  WLineTo(float X, float Y, float Z,CDC* pDC);
	void  WMoveTo(float X, float Y, float Z,CDC* PDC);
	void  ReadVertics();
	void  ReadFaces();
	void  VisionVector(int St1);
	void  NormalVector(int St1, int St2, int St3);
	float  ScaleProduct(float v1, float v2, float v3,
		    float n1, float n2, float n3);
	void  DrawFace(CDC* pDC);
	void  DrawObject();
	void  VisionPoint();
	
public:
	void Mydraw();
	float   Rol, Theta, Phi, DE, Aux1, Aux2, Aux3, Aux4, Aux5, Aux6, Aux7, Aux8,
		XObs,YObs,ZObs,XProj,YProj,S,St[MaxSt][3],O1,O2,O3,v1,v2,v3,n1,n2,n3;
	int     Fc[MaxFc][MaxAt+1], XScreen, YScreen, F, NF;
// 变量说明： Rol, Theta, Phi是视点在用户坐标系中的球坐标变 
// 量，DE为视距。Aux1, Aux2, Aux3, Aux4, Aux5, Aux6, Aux7, 
// Aux8是用于存取计算用户坐标系点到观察坐标系点的
// 坐标值公式中的正余弦值。数组 St和Fc 分别存放顶点表和面表 
// 的数据，以便实现本例凸多面体的数据结构的具体存储结构。枚 
// 举型变量Projection用于选择投影类型。                  

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMyView)
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnTumianti();
	afx_msg void OnYuanjin();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in 消隐View.cpp
inline CMyDoc* CMyView::GetDocument()
   { return (CMyDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEW_H__55118D9A_9F86_4469_BEBD_56716DBE060A__INCLUDED_)
