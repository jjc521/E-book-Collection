/////////////////////////////////////////////////////////////////////////////////
//	
// Edge.cpp: implementation of the CEdge class.
//
////////////////////////////////////////////////////////////////////////////////
// 版权所有(2002)
// Copyright(2002)
// 编写者: 向世明
// Author: Xiang Shiming


#include "stdafx.h"
#include "Edge.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CEdge::CEdge() : m_nStart(0),  m_nEnd(0)
{
	m_asIndex.SetSize(0);
}

//复制构造函数
CEdge::CEdge(const CEdge& eSrc)
{
	m_nStart = eSrc.m_nStart;
	m_nEnd = eSrc.m_nEnd;

	m_clr = eSrc.m_clr;
	m_bVisibility = eSrc.m_bVisibility;

	m_asIndex.SetSize(eSrc.m_asIndex.GetSize());
	m_asIndex.Copy(eSrc.m_asIndex);
	m_asIndex.FreeExtra();
}

CEdge::~CEdge()
{
	m_asIndex.RemoveAll();	
}

//重载运算符 "=" 
CEdge CEdge::operator = (const CEdge& eSrc)
{
	m_nStart = eSrc.m_nStart;
	m_nEnd = eSrc.m_nEnd;

	m_clr = eSrc.m_clr;
	m_bVisibility = eSrc.m_bVisibility;

	m_asIndex.SetSize(eSrc.m_asIndex.GetSize());
	m_asIndex.Copy(eSrc.m_asIndex);
	m_asIndex.FreeExtra();

	return *this;
}

//定义边
//nStart----起点序号
//nEnd------终点序号
void CEdge::DefineEdge(int nStart,  int nEnd)
{
	m_nStart = nStart;
	m_nEnd = nEnd;
} 

//定义边的拓扑(共边的面)
//pnInFacet-----该边所在的小面序号数组, 
//nNumFacet-----共该边的小面个数
void CEdge::DefineTopology(const int* pnInFacet,  int nNumFacet)
{
	ASSERT(nNumFacet >= 0);
	m_asIndex.SetSize(nNumFacet);
	for(int i = 0; i < nNumFacet; i++)
		m_asIndex[i] = pnInFacet[i];
	m_asIndex.FreeExtra();
}