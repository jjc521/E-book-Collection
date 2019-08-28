// 真实感图形学View.h : interface of the CMyView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_VIEW_H__26A0C9F0_064F_4123_AE6C_FA66BAAE6F98__INCLUDED_)
#define AFX_VIEW_H__26A0C9F0_064F_4123_AE6C_FA66BAAE6F98__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Sphere.h"
#include "LightObj.h"
#include "Material.h"

#include "ColorBuffer.h"


class CMyView : public CView
{
protected: // create from serialization only
	CMyView();
	DECLARE_DYNCREATE(CMyView)
private:
	CSphere* m_pSphere0;
	CSphere* m_pSphere1;
	CSphere* m_pSphere2;
	//视点
	VERTEX3D m_viewer;
	//取景器
	VIEWFINDER m_viewFinder;

	//光源
	CLightObj* m_pLights;

	//材质(为了简单,用一种材质)
	CMaterial  m_material;

	//颜色缓冲区
	CColorBuffer* m_pCB;
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
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMyView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in 真实感图形学View.cpp
inline CMyDoc* CMyView::GetDocument()
   { return (CMyDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEW_H__26A0C9F0_064F_4123_AE6C_FA66BAAE6F98__INCLUDED_)
