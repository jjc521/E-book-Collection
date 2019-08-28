// Material.h: interface for the CMaterial class.
#ifndef _CMATERIAL_H
#define _CMATERIAL_H
#include "Grphcs.h"

class CMaterial  
{
public:
	CMaterial();
	CMaterial(const CMaterial& material);
	virtual ~CMaterial();

public:

	//设置光亮度
	void Materialf(DWORD dwFace, DWORD dwProperty, float fParam);
	void Materialfv(DWORD dwFace, DWORD dwProperty, const float* pfParams);
public:
	//材质对环境光的反射率(reflectivity)
	FLOATCOLORRGBA m_refAmb;
	//材质对漫反射光的反射率
	FLOATCOLORRGBA m_refDif;
	//材质对镜面高光的反射率
	FLOATCOLORRGBA m_refSpe;
	//材质的自体辐射光色(Emission)
	FLOATCOLORRGBA m_clrEmi;
	
	//材质亮度（高光指数）
	float m_fShininess;
	//面的类型,前面,后面,还是前后两面(双面)
	DWORD m_dwFaceType;

};

#endif 
