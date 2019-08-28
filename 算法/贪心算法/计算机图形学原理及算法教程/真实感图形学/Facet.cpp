/////////////////////////////////////////////////////////////////////////////////
//	
// Facet.cpp: implementation of the CFacet class.

#include "stdafx.h"
#include "Facet.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFacet::CFacet()
{
	//小面法线:指向Z轴
	m_normal.x = m_normal.y = 0.0f; m_normal.z = 1.0f;
	
	//为了便于操作, 设置大小为0
	m_avIndex.SetSize(0);
}

CFacet::CFacet(const CFacet& fctSrc)
{
	m_clr = fctSrc.m_clr;
	m_normal = fctSrc.m_normal;
	m_bVisibility = fctSrc.m_bVisibility;

	m_avIndex.SetSize(fctSrc.m_avIndex.GetSize());
	m_avIndex.Copy(fctSrc.m_avIndex);
	m_avIndex.FreeExtra();
	
}

CFacet::~CFacet()
{
	m_avIndex.RemoveAll();
}

//重载 " = " 运算符 
CFacet CFacet::operator = (const CFacet& fctSrc)
{
	m_clr = fctSrc.m_clr;
	m_normal = fctSrc.m_normal;
	m_bVisibility = fctSrc.m_bVisibility;

	m_avIndex.SetSize(fctSrc.m_avIndex.GetSize());
	m_avIndex.Copy(fctSrc.m_avIndex);
	m_avIndex.FreeExtra();

	return *this;
}

//定义小面的拓扑(点序号)
//pnVertex-----组成小面的顶点序号数组
//nNumVertex----顶点个数
void CFacet::DefineTopology(const int* pnVertex,  int nNumVertex)
{
	ASSERT(nNumVertex > 2);
	m_avIndex.SetSize(nNumVertex);
	for(int i = 0; i < nNumVertex; i++)
		m_avIndex[i] = pnVertex[i];
	m_avIndex.FreeExtra();
}


