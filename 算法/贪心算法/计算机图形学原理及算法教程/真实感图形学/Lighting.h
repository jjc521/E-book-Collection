// Lighting.h: interface for the CLighting class.
#ifndef _CLIGHTING_H
#define _CLIGHTING_H

#include "LightObj.h"
#include "Material.h"
#include "Object3d.h"

class CLighting  
{
public:
	CLighting();
	virtual ~CLighting();

public:
	//设置光照模型
	void LightModelb(DWORD dwProperty, BOOL bParam);

	//设置全局环境光
	void LightModelfv(DWORD dwProperty, const float* pfParams);
public:

	//多光源照射系统
	void Lighting(CObject3d* pObj, const CMaterial& material, VERTEX3D viewer,const CLightObj* lights, int nNumLight);

public:

	//全局环境光
	FLOATCOLORRGBA m_clrGlobalAmb;

	//光局部视点
	BOOL m_bLocalViewer;

	//是否双面光照
	BOOL m_bTwoSides;
};

#endif 
