/////////////////////////////////////////////////////////////////////////////////
//	
// CBRender.cpp: implementation of the CBRender class.
#include "stdafx.h"
#include "BRender.h"

#include "ViewFinder.h"
#include "BLine.h"
#include "BTriangle.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBRender::CBRender()
{

}

CBRender::~CBRender()
{

}

//着色处理, 利用深度进行消隐
//pObj---------三维物体对象   (单个物体)
//viewer------视点(定义于世界坐标系)
//viewFinder--取景器
//pCB---------颜色缓冲
//pZB---------深度缓冲
//dwRop-------着色模式
void CBRender::Render(CObject3d* pObj,  VERTEX3D viewer,  VIEWFINDER viewFinder,  CColorBuffer* pCB,  CZBuffer* pZB,  DWORD dwRop)
{
	ASSERT(pCB);
	ASSERT(pZB);
	//第一步, 获取几何元素的个数
	
	//物体顶点的个数
	int nNumVertex = pObj->GetVertexListSize();
	

	//存储将世界坐标变换为观察坐标后的结果
	HOMOCOORD* pvInView = new HOMOCOORD[nNumVertex];

	if(pvInView == NULL)
	{
		::AfxMessageBox("内存分配失败!");
		exit(1);
	}
	
	//////////////////////////////////////////
	//第二步:完成从世界坐标到观察坐标的变换

	//观察矩阵(初始化为单位矩阵)
	CMatrix3d mWatch;

	//获取观察矩阵
	mWatch.Watch(viewer.x,  viewer.y,  viewer.z);

	int i;
	//将世界坐标系的点变换为观察坐标系的点
	for(i = 0; i < nNumVertex; i++)
	{
		//获取一个顶点的齐次坐标
		//将顶点变换至到获取观察坐标
		pvInView[i] = mWatch.Transform(pObj->m_vList[i].m_coord);
	}//end for i (1st)

	//
	//////////////////////////////////////////
	//第三步:完成从观察坐标到屏幕坐标的变换

	//中间省略了如下几个步骤:
	//其一, 透视剪切;其二, 设备坐标规格化
	
	//保存变换之结果
	POINT* pPtOnScrn = new POINT[nNumVertex];

	if(pPtOnScrn == NULL)
	{
		::AfxMessageBox("内存分配失败!");
		exit(1);
	}

	//设置视口变换工具.
	CViewFinder  vf(viewFinder);
	//执行缩减的透视变换和视口变换
	for(i = 0; i < nNumVertex; i++)
		pPtOnScrn[i] = vf.Perspective(pvInView[i]);

	//第四步, 用观察坐标系中的 z 坐标来代替屏幕坐标系下的 z 坐标
	//这是一个几何跨越

	//利用齐次坐标获取实际深度, 
	//注意, CViewFinder类的Perspective()函数作了与下后面这个循环相同的除法运算;
	//在计算上有些重复, 但观察坐标在更加复杂的系统中还有其它的应用.
	//因而, 我们并不通过CViewFinder类的Perspective()函数来把观察坐标变换为等价的三维坐标
	//

	for(i = 0; i < nNumVertex; i++)
	{
		float z = pvInView[i].z;
		float w = pvInView[i].w;

		if(ABS(w) < 0.00001f)
			z = 100000.0f;
		else
			z /= w;
		pvInView[i].z = z;
	}

	//第五步, 绘制

	//绘制选择器
	switch(dwRop)
	{
		case G3D_RENDER_VERTICES:
			Vertexize(pObj,  pPtOnScrn,  pvInView,  pCB,  pZB);
			break;

		case G3D_RENDER_WIRE:
			FlatWirize(pObj,  pPtOnScrn,  pvInView,  pCB,  pZB);
			break;

		case G3D_RENDER_WIRE_LIGHTED:
			GouraudWirize(pObj,  pPtOnScrn,  pvInView,  pCB,  pZB);
			break;

		case G3D_RENDER_FLAT:
			Flat(pObj,  pPtOnScrn,  pvInView,  pCB,  pZB);
			break;

		case G3D_RENDER_GOURAUD_SMOOTH:
			Gouraud(pObj,  pPtOnScrn,  pvInView,  pCB,  pZB);
			break;
	}
}

//绘制点模型

void CBRender::Vertexize(CObject3d* pObj,  POINT* pPtOnScrn,  HOMOCOORD* pvInView,  CColorBuffer* pCB,  CZBuffer* pZB)
{
	//顶点个数
	int nNumPt = pObj->GetVertexListSize();
	
	//绘制点模型
	for(int i = 0; i < nNumPt; i++)
	{
		//颜色(R, G, B, A)
		float fRed = pObj->m_vList[i].m_clr.red;
		float fGreen = pObj->m_vList[i].m_clr.green;
		float fBlue = pObj->m_vList[i].m_clr.blue;
		float fAlpha = pObj->m_vList[i].m_clr.alpha;

		//坐标
		int x = pPtOnScrn[i].x;
		int y = pPtOnScrn[i].y;

		//深度

		float z = pvInView[i].z;
		
		//缓冲区中的深度
		float zInBuffer = pZB->GetDepth(x,  y);
		
		//如果当前点的z坐标小于深度缓冲区中的相同位置z的坐标
		if(z < zInBuffer)
		{
			//在颜色缓冲区中绘制第一个点
			pCB->SetPixel(x,  y,  fRed,  fGreen,  fBlue,  fAlpha); 

			//重置深度缓冲区的值
			pZB->SetDepth(x,  y,  z);
		
		}
		
	} 

}

//绘制线框模型
//pObj---------三维物体对象
//pPtOnScrn---最终透视到屏幕上的点
//pvInView----观察坐标系中的坐标
//pCB---------颜色缓冲
//pZB---------深度缓冲
void CBRender::FlatWirize(CObject3d* pObj,  POINT* pPtOnScrn,  HOMOCOORD* pvInView,  CColorBuffer* pCB,  CZBuffer* pZB)
{
	//物体边数
	int nNumEdge = pObj->GetEdgeListSize();
	
	//绘制工具:直线基元
	CBLine bl;
	//绘制单色模型
	for(int i = 0; i < nNumEdge; i++)
	{
		//获取边的顶点索引
		int n1 = pObj->m_eList[i].m_nStart;
		int n2 = pObj->m_eList[i].m_nEnd;

		//端点深度
		float z1 = pvInView[n1].z;
		float z2 = pvInView[n2].z;
		
		//由顶点决定边的颜色, 还是由外部决定边的颜色
		BOOL bAutoColor = pObj->GetAutoColorProperty();

		if(bAutoColor)
		{

			//获取第一个顶点的颜色代替整条边的颜色
			FLOATCOLORRGBA rgba = pObj->m_vList[n1].m_clr;
			//绘制
			bl.Draw(pPtOnScrn[n1],  pPtOnScrn[n2],  z1,  z2,   rgba,  rgba,  pCB,  pZB);
		}
		else
		{
			FLOATCOLORRGBA rgba = pObj->m_eList[i].m_clr;
			bl.Draw(pPtOnScrn[n1],  pPtOnScrn[n2],  z1,  z2,   rgba,  rgba,  pCB,  pZB);
		}
	}
}


//绘制线框模型
//pObj---------三维物体对象
//pPtOnScrn---最终透视到屏幕上的点
//pvInView----观察坐标系中的坐标
//pCB---------颜色缓冲
//pZB---------深度缓冲
void CBRender::GouraudWirize(CObject3d* pObj,  POINT* pPtOnScrn,  HOMOCOORD* pvInView,  CColorBuffer* pCB,  CZBuffer* pZB)
{
	//物体边数
	int nNumEdge = pObj->GetEdgeListSize();
	
	//绘制工具:直线基元
	CBLine bl;
	//绘制单色模型
	for(int i = 0; i < nNumEdge; i++)
	{
		//获取边的顶点索引
		int n1 = pObj->m_eList[i].m_nStart;
		int n2 = pObj->m_eList[i].m_nEnd;

		//端点深度
		float z1 = pvInView[n1].z;
		float z2 = pvInView[n2].z;
		
		//获取两顶点的浮点颜色
		FLOATCOLORRGBA rgba1 = pObj->m_vList[n1].m_clr;
		FLOATCOLORRGBA rgba2 = pObj->m_vList[n2].m_clr;
		
		//绘制
		bl.Draw(pPtOnScrn[n1],  pPtOnScrn[n2],  z1,  z2,  rgba1,  rgba2,  pCB,  pZB);

	}
}

//绘制实体模型, Flat模型
//pObj---------三维物体对象
//pPtOnScrn---最终透视到屏幕上的点
//pvInView----观察坐标系中的坐标
//pCB---------颜色缓冲
//pZB---------深度缓冲
void CBRender::Flat(CObject3d* pObj,  POINT* pPtOnScrn,  HOMOCOORD* pvInView,  CColorBuffer* pCB,  CZBuffer* pZB)
{
	//物体小面个数
	int nNumFacet = pObj->GetFacetListSize();
	
	//面绘制工具: 三角形基元
	CBTriangle bt;

	//由顶点决定小面的颜色, 还是由外部决定小面的颜色
	BOOL bAutoColor = pObj->GetAutoColorProperty();

	//绘制, 面循环
	for(int i = 0; i < nNumFacet; i++)
	{
		//获取小面的顶点数
		int nNumVertex = pObj->m_sList[i].m_avIndex.GetSize();
		if(nNumVertex == 3)
		{
			//获取顶点索引号
			int n1 = pObj->m_sList[i].m_avIndex[0];
			int n2 = pObj->m_sList[i].m_avIndex[1];
			int n3 = pObj->m_sList[i].m_avIndex[2];

			//顶点深度
			float z1 = pvInView[n1].z;
			float z2 = pvInView[n2].z;
			float z3 = pvInView[n3].z;

			//小面颜色
			FLOATCOLORRGBA rgba;
				
			//获取顶点颜色
			if(bAutoColor)
			{
				//一般地, 采用第一个顶点的颜色来表示小面的颜色
				//这对模型的顶点安排要求比较高
				//因而, 我们采用三个顶点颜色的平均值来表示小面的颜色
				//在光照条件下, 这样处理也是可以接受的
				FLOATCOLORRGBA rgba1 = pObj->m_vList[n1].m_clr;
				FLOATCOLORRGBA rgba2 = pObj->m_vList[n2].m_clr;
				FLOATCOLORRGBA rgba3 = pObj->m_vList[n3].m_clr;

				//顶点颜色归一化应该在外部进行
				rgba.red = (rgba1.red + rgba2.red + rgba3.red) / 3.0f;
				rgba.green = (rgba1.green + rgba2.green + rgba3.green) / 3.0f;
				rgba.blue = (rgba1.blue + rgba2.blue +  rgba3.blue) / 3.0f;
				
				//透明度, 这里也简单地处理成同一值
				rgba.alpha = (rgba1.alpha + rgba2.alpha +  rgba3.alpha) / 3.0f;

			}
			//获取小面颜色
			else
				rgba = pObj->m_sList[i].m_clr;

			//绘制
			bt.Draw(pPtOnScrn[n1],  pPtOnScrn[n2],  pPtOnScrn[n3], z1,  z2,  z3,  rgba,  rgba,  rgba,  pCB,  pZB);

		}

		else if(nNumVertex == 4)
		{
			//获取顶点索引号
			int n1 = pObj->m_sList[i].m_avIndex[0];
			int n2 = pObj->m_sList[i].m_avIndex[1];
			int n3 = pObj->m_sList[i].m_avIndex[2];
			int n4 = pObj->m_sList[i].m_avIndex[3];

			//顶点深度
			float z1 = pvInView[n1].z;
			float z2 = pvInView[n2].z;
			float z3 = pvInView[n3].z;
			float z4 = pvInView[n4].z;

			//小面颜色
			FLOATCOLORRGBA rgba;
	
			//获取顶点颜色
			if(bAutoColor)
			{
				//一般地, 采用第一个顶点的颜色来表示小面的颜色
				//这对模型的顶点安排要求比较高
				//因而, 我们采用三个顶点颜色的平均值来表示小面的颜色
				//在光照条件下, 这样处理也是可以接受的
				FLOATCOLORRGBA rgba1 = pObj->m_vList[n1].m_clr;
				FLOATCOLORRGBA rgba2 = pObj->m_vList[n2].m_clr;
				FLOATCOLORRGBA rgba3 = pObj->m_vList[n3].m_clr;
				FLOATCOLORRGBA rgba4 = pObj->m_vList[n4].m_clr;
			
				rgba.red = (rgba1.red + rgba2.red + rgba3.red + rgba4.red) / 4.0f;
				rgba.green = (rgba1.green + rgba2.green + rgba3.green + rgba4.green) / 4.0f;
				rgba.blue = (rgba1.blue + rgba2.blue +  rgba3.blue + rgba4.blue) / 4.0f;
				
				//透明度, 这里也简单地处理成同一值
				rgba.alpha = (rgba1.alpha + rgba2.alpha + rgba3.alpha + rgba4.alpha) / 4.0f;

			}
			//获取小面颜色
			else
				rgba = pObj->m_sList[i].m_clr;


			//细化四边形, 并完成绘制
			bt.Draw(pPtOnScrn[n1],  pPtOnScrn[n2],  pPtOnScrn[n3],  z1,  z2,  z3,  rgba,  rgba,  rgba,  pCB,  pZB);
			bt.Draw(pPtOnScrn[n1],  pPtOnScrn[n3],  pPtOnScrn[n4],  z1,  z3,  z4,  rgba,  rgba,  rgba,  pCB,  pZB);

		}
		
		}

}



//绘制实体模型, Gouraud模型
//pObj---------三维物体对象
//pPtOnScrn---最终透视到屏幕上的点
//pvInView----观察坐标系中的坐标
//pCB---------颜色缓冲
//pZB---------深度缓冲
void CBRender::Gouraud(CObject3d* pObj,  POINT* pPtOnScrn,  HOMOCOORD* pvInView,  CColorBuffer* pCB,  CZBuffer* pZB)
{
	//物体小面个数
	int nNumFacet = pObj->GetFacetListSize();
	
	//面绘制工具: 三角形基元
	CBTriangle bt;

	//绘制, 面循环
	for(int i = 0; i < nNumFacet; i++)
	{
		//获取小面的顶点数
		int nNumVertex = pObj->m_sList[i].m_avIndex.GetSize();
		if(nNumVertex == 3)
		{
			//获取顶点索引号
			int n1 = pObj->m_sList[i].m_avIndex[0];
			int n2 = pObj->m_sList[i].m_avIndex[1];
			int n3 = pObj->m_sList[i].m_avIndex[2];

			//获取顶点颜色
			FLOATCOLORRGBA rgba1 = pObj->m_vList[n1].m_clr;
			FLOATCOLORRGBA rgba2 = pObj->m_vList[n2].m_clr;
			FLOATCOLORRGBA rgba3 = pObj->m_vList[n3].m_clr;

			//顶点深度
			float z1 = pvInView[n1].z;
			float z2 = pvInView[n2].z;
			float z3 = pvInView[n3].z;

			//绘制
			bt.Draw(pPtOnScrn[n1],  pPtOnScrn[n2],  pPtOnScrn[n3], z1,  z2,  z3,  rgba1,  rgba2,  rgba3,  pCB,  pZB);

		}//end if (nNumVertex == 3)
		else if(nNumVertex == 4)
		{
			//获取顶点索引号
			int n1 = pObj->m_sList[i].m_avIndex[0];
			int n2 = pObj->m_sList[i].m_avIndex[1];
			int n3 = pObj->m_sList[i].m_avIndex[2];
			int n4 = pObj->m_sList[i].m_avIndex[3];

			//获取顶点颜色
			//获取顶点颜色
			FLOATCOLORRGBA rgba1 = pObj->m_vList[n1].m_clr;
			FLOATCOLORRGBA rgba2 = pObj->m_vList[n2].m_clr;
			FLOATCOLORRGBA rgba3 = pObj->m_vList[n3].m_clr;
			FLOATCOLORRGBA rgba4 = pObj->m_vList[n4].m_clr;

			//顶点深度
			float z1 = pvInView[n1].z;
			float z2 = pvInView[n2].z;
			float z3 = pvInView[n3].z;
			float z4 = pvInView[n4].z;

			//细化四边形, 并完成绘制
			bt.Draw(pPtOnScrn[n1],  pPtOnScrn[n2],  pPtOnScrn[n3],  z1,  z2,  z3,  rgba1,  rgba2,  rgba3,  pCB,  pZB);
			bt.Draw(pPtOnScrn[n1],  pPtOnScrn[n3],  pPtOnScrn[n4],  z1,  z3,  z4,  rgba1,  rgba3,  rgba4,  pCB,  pZB);

		}
	
	}
}

