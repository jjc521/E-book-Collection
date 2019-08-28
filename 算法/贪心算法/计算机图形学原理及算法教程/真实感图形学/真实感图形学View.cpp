// 真实感图形学View.cpp : implementation of the CMyView class
//

#include "stdafx.h"
#include "真实感图形学.h"

#include "真实感图形学Doc.h"
#include "真实感图形学View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#include "ZBuffer.h"
#include "BRender.h"
#include "TypedStack.h"
#include "Lighting.h"
/////////////////////////////////////////////////////////////////////////////
// CMyView

IMPLEMENT_DYNCREATE(CMyView, CView)

BEGIN_MESSAGE_MAP(CMyView, CView)
	//{{AFX_MSG_MAP(CMyView)
	ON_WM_CREATE()
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
//视点
	VERTEX3D viewer = {0.0f,  0.0f,  8.0f};

	//视口变换中进行放大处理, 屏幕位置距离视点100个单位;
	//透视中心(屏幕坐标)为(250, 250)
	VIEWFINDER viewFinder = {100.0f,  8.0f,  8.0f,  {200,  200}};

	m_viewer = viewer;
	m_viewFinder = viewFinder;
}


	


CMyView::~CMyView()
{
delete m_pSphere0;
	delete m_pSphere1;
	delete m_pSphere2;
//	delete m_pSphere3;
//	delete m_pSphere4;
//	delete m_pSphere5;
	delete[] m_pLights;
	delete m_pCB;
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
	m_pCB->SwapBuffer(pDC);
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
	
	// TODO: Add your specialized creation code here
	//
	//the first stage

	//第一阶段, 建立场景，设置光源和材质属性，完成光照计算
	
	//第一步, 申明一个球对象
	m_pSphere0 = new CSphere(0.5f, 32, 32);

	//克隆五个球
	m_pSphere1 = m_pSphere0->Clone();
	m_pSphere2 = m_pSphere0->Clone();
//	m_pSphere3 = m_pSphere0->Clone();
//	m_pSphere4 = m_pSphere0->Clone();
//	m_pSphere5 = m_pSphere0->Clone();

	//组织场景, 进行几何变换

	//构造一个矩阵堆栈
	CTypedStack<CMatrix3d> matrixStack;
	//变换矩阵
	CMatrix3d mGeometry;

	//方位矩阵
	mGeometry.RotateX(45.0f);
	matrixStack.Push(mGeometry);

	//上一层球
	mGeometry.Translate(-1.1f,  1.0f,  0.0f);
	m_pSphere0->Transform(mGeometry);
	
	mGeometry.Translate(1.1f,  0.0f,  0.0f);
	m_pSphere1->Transform(mGeometry);

	mGeometry.Translate(1.1f,  0.0f,  0.0f);
	m_pSphere2->Transform(mGeometry);

/*	//下一层球
	mGeometry.Translate(0.0f,  -1.4f,  0.0f);
	m_pSphere5->Transform(mGeometry);

	mGeometry.Translate(-1.1f,  0.0f,  0.0f);
	m_pSphere4->Transform(mGeometry);

	mGeometry.Translate(-1.1f,  0.0f,  0.0f);
	m_pSphere3->Transform(mGeometry);*/

	//法线:
	CMatrix3d mn = matrixStack.Pop();

	
	//物体的顶点法线:
	m_pSphere0->TransVertexNormals(mn);
	m_pSphere1->TransVertexNormals(mn);
	m_pSphere2->TransVertexNormals(mn);
//	m_pSphere3->TransVertexNormals(mn);
//	m_pSphere4->TransVertexNormals(mn);
//	m_pSphere5->TransVertexNormals(mn);
	

	//第二步:设置材质和光源

	//设置两个光源
	m_pLights = new CLightObj[2];

	//设置第一盏灯(泛光灯)
	float amb_omni[4] = {0.2f,  0.2f,  0.2f,  1.0f};
	float dif_omni[4] = {1.0f,  1.0f,  1.0f,  1.0f};
	float spe_omni[4] = {1.0f,  1.0f,  1.0f,  1.0f};
	float pos_omni[4] = {0.0f,  0.0f,  8.0f,  1.0f};

	m_pLights[0].Lightfv(G3D_AMBIENT,   amb_omni);
	m_pLights[0].Lightfv(G3D_DIFFUSE,   dif_omni);
	m_pLights[0].Lightfv(G3D_SPECULAR,  spe_omni);
	m_pLights[0].Lightfv(G3D_POSITION,  pos_omni);
	//m_pLights[0].Lightf(G3D_CONSTANT_ATTENUATION,  2.5f);
	//m_pLights[0].Lightb(G3D_LIGHT_ON_OFF,  FALSE);

	//设置第一盏灯(聚光灯)
	float amb_spot[4] = {0.2f, 0.2f, 0.2f, 1.0f};
	float dif_spot[4] = {1.0f, 0.0f, 0.0f, 1.0f};
	float spe_spot[4] = {1.0f, 1.0f, 1.0f, 1.0f};
	float pos_spot[4] = {0.0f, 8.0f, 8.0f, 1.0f};
	float dir_spot[4] = {0.0f, -1.0f, -1.0f, 1.0f};

	m_pLights[1].Lightfv(G3D_AMBIENT,  amb_spot);
	m_pLights[1].Lightfv(G3D_DIFFUSE,  dif_spot);
	m_pLights[1].Lightfv(G3D_SPECULAR,  spe_spot);
	m_pLights[1].Lightfv(G3D_POSITION,  pos_spot);
	m_pLights[1].Lightfv(G3D_SPOT_DIRECTION,  dir_spot);

	m_pLights[1].Lightf(G3D_SPOT_CUTOFF,  5.3f);
	m_pLights[1].Lightf(G3D_SPOT_EXPONENT, 50.0f);
	//m_pLights[1].Lightf(G3D_CONSTANT_ATTENUATION,  2.5f);
	//m_pLights[1].Lightb(G3D_LIGHT_ON_OFF,  FALSE);



	//第三步, 定义材质
	//黄色材质
	float ambMaterial[4] = {0.2f,  0.2f,  0.2f,  1.0f};
	float difMaterial[4] = {0.8f,  0.8f,  0.0f,  1.0f};
	float speMaterial[4] = {1.0f,  1.0f,  1.0f,  1.0f};

	float shininess = 50.0f;	


	//金
	//float ambMaterial[4] = {0.247f,  0.200f,  0.075f,  1.0f};
	//float difMaterial[4] = {0.752f,  0.606f,  0.226f,  1.0f};
	//float speMaterial[4] = {0.628f,  0.556f,  0.336f,  1.0f};
	//float shininess = 51.2f;	
	

	//设置材质
	m_material.Materialfv(G3D_FRONT,  G3D_AMBIENT,  ambMaterial);
	m_material.Materialfv(G3D_FRONT,  G3D_DIFFUSE,  difMaterial);
	m_material.Materialfv(G3D_FRONT,  G3D_SPECULAR,  speMaterial);
	m_material.Materialf(G3D_FRONT,   G3D_SHININESS,  shininess);

	
	//第四步, 进行光照计算
	CLighting lighting;
	
	//允许局部光照模型
	lighting.LightModelb(G3D_LIGHT_MODEL_LOCAL_VIEWER,  TRUE);

	//光照计算
	lighting.Lighting(m_pSphere0,  m_material,  m_viewer,  m_pLights,  2);
	lighting.Lighting(m_pSphere1,  m_material,  m_viewer,  m_pLights,  2);
	lighting.Lighting(m_pSphere2,  m_material,  m_viewer,  m_pLights,  2);
	
//	lighting.Lighting(m_pSphere3,  m_material,  m_viewer,  m_pLights,  2);
//	lighting.Lighting(m_pSphere4,  m_material,  m_viewer,  m_pLights,  2);
//	lighting.Lighting(m_pSphere5,  m_material,  m_viewer,  m_pLights,  2);

	//第一阶段已经完毕


	//////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////
	//

	//       The second stage      

	//第二阶段, 开始绘制到内存


	//第一步, 初始化颜色缓冲区, 申请深度缓冲区
	m_pCB = new CColorBuffer(410, 350);
	
	//深度缓冲区, 与颜色缓冲区大小保持一致
	CZBuffer* pZB = new CZBuffer(410,  350);
	pZB->InitAllDepth(500.0f);

	//第二步,  着色
	CBRender renderer;

	//线框模型
	renderer.Render(m_pSphere0,  m_viewer,  m_viewFinder,   m_pCB,  pZB,  G3D_RENDER_WIRE);

	//刻面模型
	renderer.Render(m_pSphere1,  m_viewer,  m_viewFinder,   m_pCB,  pZB,  G3D_RENDER_FLAT);

	//光滑明暗模型
	renderer.Render(m_pSphere2,  m_viewer,  m_viewFinder,   m_pCB,  pZB,  G3D_RENDER_GOURAUD_SMOOTH);

/*	//线框模型
	renderer.Render(m_pSphere3,  m_viewer,  m_viewFinder,   m_pCB,  pZB,  G3D_RENDER_WIRE);

	//刻面模型
	renderer.Render(m_pSphere4,  m_viewer,  m_viewFinder,   m_pCB,  pZB,  G3D_RENDER_FLAT);

	//光滑明暗模型
	renderer.Render(m_pSphere5,  m_viewer,  m_viewFinder,   m_pCB,  pZB,  G3D_RENDER_GOURAUD_SMOOTH);*/
	
	delete pZB;
	return 0;
}
