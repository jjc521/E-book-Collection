// Edge.h: interface for the CEdge class.
#ifndef _CEDGE_H
#define _CEDGE_H

#ifndef _CSUBOBJ3D_H
#include "SubObject3d.h"
#endif

//has included afxcoll.h in the stdafx.h

class CEdge  : public CSubObject3d
{
public:
	CEdge();
	CEdge(const CEdge& eSrc);
	virtual ~CEdge();

public:
	
	//重载 " = " 运算符
	CEdge operator = (const CEdge& eSrc);

	//定义边
	void DefineEdge(int nStart, int nEnd);
	
	//定义拓扑(共边的面)
	void DefineTopology(const int* pnInFacet, int nNumFacet); 

public:

	//边的起点索引号和终点索引号
	int m_nStart, m_nEnd;
	
	//共享该边的小面索引数组
	CArray<int,int> m_asIndex;

};

#endif 
