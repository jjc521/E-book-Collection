	
// Sphere.h: interface for the CSphere class.

#ifndef _CSPHERE_H
#define _CSPHERE_H

#ifndef _COBJECT3D_H
#include "Object3d.h"
#endif

class CSphere  : public CObject3d
{
DECLARE_DYNAMIC(CSphere)

public:

	//空球
	CSphere();

	CSphere(float fRadius, int nSlices, int nStacks);
	CSphere(const CSphere& sphere);
	virtual ~CSphere();

public:
	CSphere* Clone();

private:
	//初始化顶点的几何,包括坐标和法线
	void InitVertices();
	
	//初始化小面几何
	void InitFacets();

	//初始化边
	void InitEdges();

private:

	//球的半径
	float m_fRadius;

	//球的经度区域个数,简称经区数, (经线条数与它相等)
	int m_nSlices;

	//球的纬度带状区域条数,简称纬带数, (纬线条数比它少 1)
	int m_nStacks;

};

#endif 
