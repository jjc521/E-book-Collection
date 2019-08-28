// Vertex3d.h: interface for the CVertex3d class.
#ifndef _CVERTEX3D_H
#define _CVERTEX3D_H

#ifndef _CSUBOBJ3D_H
#include "SubObject3d.h"
#endif

//has included afxcoll.h in the stdafx.h

class CVertex3d : public CSubObject3d
{
public:
	CVertex3d();
	CVertex3d(const CVertex3d& vSrc);
	virtual ~CVertex3d();

public:
	CVertex3d operator = (const CVertex3d& vSrc);

	//定义点的拓扑(共点的面)
	void DefineTopology(const int* pnInFacet, int nNumFacet);


public:
	
	//成员变量,即属性均在外部进行操作

	//顶点坐标:世界齐次坐标(HOMOCOORD)
	HOMOCOORD m_coord;

	//顶点法线(VECTOR3D)
	VECTOR3D m_normal;


	//第一, 事实上,共享小面个数一般不会太多,在当今内存较大的情况下,
	//      简单地定义一个足够大的常数数组,从而可减少高级数据结构因动态分配和移动带来的时间开销(overhead)
	
	//但是,这里仍将采用动态数据结构,可以自己设计一个模板动态数组,我们将直接采用Visual C++给我们提供的.

	//共享该顶点的小面索引数组
	CArray<int,int> m_asIndex;
	
};

#endif 
