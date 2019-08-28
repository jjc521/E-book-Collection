
// Vertex3d.cpp: implementation of the CVertex3d class.
#include "stdafx.h"
#include "Vertex3d.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CVertex3d::CVertex3d()
{
	//顶点坐标:坐标原点
	m_coord.x = m_coord.y = m_coord.z = 0.0f; m_coord.w = 1.0f;

	//顶点法线:指向Z轴
	m_normal.x = m_normal.y = 0.0f; m_normal.z = 1.0f;

	//一个顶点, 可能是一个孤立点, 因而可能没有面享用它, 从而初始化为:
	m_asIndex.SetSize(0);
}

//复制构造函数
CVertex3d::CVertex3d(const CVertex3d& vSrc)
{
	m_coord = vSrc.m_coord;
	m_clr = vSrc.m_clr;
	m_normal = vSrc.m_normal;
	m_bVisibility = vSrc.m_bVisibility;

	m_asIndex.SetSize(vSrc.m_asIndex.GetSize());
	m_asIndex.Copy(vSrc.m_asIndex);
	m_asIndex.FreeExtra();
}

CVertex3d::~CVertex3d()
{
	m_asIndex.RemoveAll();	
}


//重载 "=" 运算符
CVertex3d CVertex3d::operator = (const CVertex3d& vSrc)
{
	m_coord = vSrc.m_coord;
	m_clr = vSrc.m_clr;
	m_normal = vSrc.m_normal;
	m_bVisibility = vSrc.m_bVisibility;

	m_asIndex.SetSize(vSrc.m_asIndex.GetSize());
	m_asIndex.Copy(vSrc.m_asIndex);
	m_asIndex.FreeExtra();

	return *this;
}

//定义点的拓扑(共点的面)
//pnInFacet-----该点所在的小面序号数组, 
//nNumFacet-----共该点的小面个数
void CVertex3d::DefineTopology(const int* pnInFacet,  int nNumFacet)
{
	ASSERT(nNumFacet >= 0);
	m_asIndex.SetSize(nNumFacet);
	for(int i = 0; i < nNumFacet; i++)
		m_asIndex[i] = pnInFacet[i];
	m_asIndex.FreeExtra();
}
