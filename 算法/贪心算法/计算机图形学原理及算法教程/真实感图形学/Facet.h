// Facet.h: interface for the CFacet class.
#ifndef _CFACET_H
#define _CFACET_H

#ifndef _CSUBOBJ3D_H
#include "SubObject3d.h"
#endif

//has included afxcoll.h in the stdafx.h

class CFacet : public CSubObject3d
{
public:
	CFacet();
	CFacet(const CFacet& fctSrc);
	virtual ~CFacet();

public:
	CFacet operator = (const CFacet& fctSrc);

	//定义小面的拓扑(点序号)
	void DefineTopology(const int* pnVertex, int nNumVertex);

public:
	
	//小面法线:
	VECTOR3D m_normal;

	//在图形处理中,小面一般为三角形或四边形

	//小面顶点序号
	CArray<int,int> m_avIndex;

};

#endif
