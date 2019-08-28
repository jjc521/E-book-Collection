// 三维变换View.h : interface of the CMyView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_VIEW_H__BFB29846_C242_48D0_8CA7_60B59B46A728__INCLUDED_)
#define AFX_VIEW_H__BFB29846_C242_48D0_8CA7_60B59B46A728__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
class CMyDoc;
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
	enum  {SEL_TS,SEL_RX,SEL_RY,SEL_RZ,SEL_SXYZ,SEL_SS,SEL_MX,SEL_MY,SEL_MZ,SEL_MOXY,
		SEL_MOYZ,SEL_MOZX,SEL_MO,SEL_SHX,SEL_SHY,SEL_SHZ,SEL_V,SEL_H,SEL_W,SEL_ST,SEL_VE,
		SEL_VT,SEL_SE,SEL_PRP,SEL_NONE} m_Select ;
	CString m_str;
	double Theta,Phi;
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
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMyView)
	afx_msg void OnTranslation();
	afx_msg void OnH();
	afx_msg void OnMirrorO();
	afx_msg void OnMirrorOxy();
	afx_msg void OnMirrorOyz();
	afx_msg void OnMirrorOzx();
	afx_msg void OnMirrorX();
	afx_msg void OnMirrorY();
	afx_msg void OnMirrorZ();
	afx_msg void OnPrp();
	afx_msg void OnRotationX();
	afx_msg void OnRotationY();
	afx_msg void OnScalingS();
	afx_msg void OnScalingXyz();
	afx_msg void OnShX();
	afx_msg void OnShY();
	afx_msg void OnV();
	afx_msg void OnW();
	afx_msg void OnSe();
	afx_msg void OnSt();
	afx_msg void OnVe();
	afx_msg void OnVt();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRotationZ();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in 三维变换View.cpp
inline CMyDoc* CMyView::GetDocument()
   { return (CMyDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEW_H__BFB29846_C242_48D0_8CA7_60B59B46A728__INCLUDED_)
