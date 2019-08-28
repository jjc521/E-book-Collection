// 图形相交—相切View.h : interface of the CMyView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_VIEW_H__A13A4649_984F_4B8E_9DB9_6AD35DB39371__INCLUDED_)
#define AFX_VIEW_H__A13A4649_984F_4B8E_9DB9_6AD35DB39371__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


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
	int TPC(float P0[2],float C[3],float P[2],float L[3]);
	int PLL(double P1x,double P1y,double P2x,double P2y,double P3x,double P3y,double P4x,double P4y,double &Px,double &Py);
	int PCC(double c1[3],double c2[3],double p1[2],double p2[2]);
	int PLC(double l1[2],double l2[2],double c[3],double p1[2],double p2[2]);
	void Mydraw();
	void Tiso(float p0[3],float x0, float y0, float p[3]);
	float p0[3],x0,y0,p[3];
	int x1,y1,x2,y2,x,y;
	//变量说明:
	//P0为圆外一点坐标，C为圆的圆心坐标及半径，P为所求切线的法线系数。
	float C[3],L[3],P0[2],P[2];
	double l1[2],l2[2],c[3],c1[3],c2[3],p1[2],p2[2];
	double P1x,P1y,P2x,P2y,P3x,P3y,P4x,P4y,Px,Py;
	int num,PushNum;
	CPoint P2[5];
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMyView)
	afx_msg void OnLineLine();
	afx_msg void OnLineCiercle1();
	afx_msg void OnCircleCircle();
	afx_msg void OnLineCircle();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnPlaneCylinder();
	afx_msg void OnPlaneCone();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in 图形相交—相切View.cpp
inline CMyDoc* CMyView::GetDocument()
   { return (CMyDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEW_H__A13A4649_984F_4B8E_9DB9_6AD35DB39371__INCLUDED_)
