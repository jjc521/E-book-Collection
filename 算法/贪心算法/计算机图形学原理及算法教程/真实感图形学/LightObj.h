// LightObj.h: interface for the CLightObj class.
#ifndef _CLIGHTOBJ_H
#define _CLIGHTOBJ_H
#include "Grphcs.h"

class CLightObj  
{
public:
	CLightObj();
	CLightObj(const CLightObj& light);
	virtual ~CLightObj();

public:
	//光是否为开启状态
	void Lightb(DWORD dwProperty, BOOL bOnOff);
	//设置标量参数
	void Lightf(DWORD dwProperty, float fParam);
	//设置向量参数
	void Lightfv(DWORD dwProperty, const float* pfParams);

public:

	//光的环境颜色
	FLOATCOLORRGBA m_clrAmb;
	//光的漫反射颜色
	FLOATCOLORRGBA m_clrDif;
	//光的镜面高光颜色
	FLOATCOLORRGBA m_clrSpe;

	//光源位置
	HOMOCOORD m_hcPosition;
	
	//聚光照射方向: 
	VECTOR3D  m_spotDirection;
	
	//聚光指数
	float m_fSpotExp;

	//聚光发散半角
	float m_fSpotCutoff;
	
	//常数衰减系数
	float m_fAttCoef0;
	//线性衰减系数
	float m_fAttCoef1;
	//二次衰减系数
	float m_fAttCoef2;

	//光是否开启
	BOOL m_bOnOff;

};

#endif 
