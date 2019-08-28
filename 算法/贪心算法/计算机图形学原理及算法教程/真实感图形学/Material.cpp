/////////////////////////////////////////////////////////////////////////////////
//	
// Material.cpp: implementation of the CMaterial class.
#include "stdafx.h"
#include "Material.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMaterial::CMaterial()
{
	//缺省材质
	m_refAmb.red  = 0.2f;		m_refAmb.green = 0.2f;
	m_refAmb.blue = 0.2f;		m_refAmb.alpha = 1.0f;

	m_refDif.red  = 0.8f;		m_refDif.green = 0.8f;
	m_refDif.blue = 0.8f;		m_refDif.alpha = 1.0f;

	m_refSpe.red  = 0.0f;		m_refSpe.green = 0.0f;
	m_refSpe.blue = 0.0f;		m_refSpe.alpha = 1.0f;

	m_clrEmi.red =  0.0f;		m_clrEmi.green = 0.0f;
	m_clrEmi.blue = 0.0f;		m_clrEmi.alpha = 1.0f;

	m_fShininess = 128.0f;
	m_dwFaceType = G3D_FRONT;
}

CMaterial::CMaterial(const CMaterial& material)
{
	m_refAmb = material.m_refAmb;
	m_refDif = material.m_refDif;
	m_refSpe = material.m_refSpe;
	m_clrEmi = material.m_clrEmi;
	m_fShininess = material.m_fShininess;
	m_dwFaceType = material.m_dwFaceType;
}

CMaterial::~CMaterial()
{

}

//设置光亮度
//dwFace-------光照面, 取枚举值
//dwProperty---属性, 取 G3D_SHININESS 为有效
//fParam-------具体参数值
void CMaterial::Materialf(DWORD dwFace,  DWORD dwProperty,  float fParam)
{
	if(dwProperty == G3D_SHININESS)
	{
		m_dwFaceType = dwFace;
		m_fShininess = (fParam < 0.0f) ? 0.0f : ((fParam > 128.0f) ? 128.0f : fParam);
	}
}

//设置向量参数
//dwFace-------光照面, 取枚举值
//dwProperty---属性, 
//pfParams-----具体参数值
void CMaterial::Materialfv(DWORD dwFace,  DWORD dwProperty,  const float* pfParams)
{
	ASSERT(pfParams);
	m_dwFaceType = dwFace;
	switch(dwProperty)
	{
		//环境光反射系数
		case G3D_AMBIENT:
			m_refAmb.red   = pfParams[0];
			m_refAmb.green = pfParams[1];
			m_refAmb.blue  = pfParams[2];
			m_refAmb.alpha = pfParams[3];
			break;
		//漫反射光反射系数
		case G3D_DIFFUSE:
			m_refDif.red   = pfParams[0];
			m_refDif.green = pfParams[1];
			m_refDif.blue  = pfParams[2];
			m_refDif.alpha = pfParams[3];
			break;
		//镜面高光反射系数
		case G3D_SPECULAR:
			m_refSpe.red   = pfParams[0];
			m_refSpe.green = pfParams[1];
			m_refSpe.blue  = pfParams[2];
			m_refSpe.alpha = pfParams[3];
			break;

		//环境和漫反射系数相同
		case G3D_AMBIENT_AND_DIFFUSE:
			m_refAmb.red   = pfParams[0];
			m_refAmb.green = pfParams[1];
			m_refAmb.blue  = pfParams[2];
			m_refAmb.alpha = pfParams[3];

			m_refDif.red   = pfParams[0];
			m_refDif.green = pfParams[1];
			m_refDif.blue  = pfParams[2];
			m_refDif.alpha = pfParams[3];
			break;
		//自体辐射光色
		case G3D_EMISSION:	
			m_clrEmi.red   = pfParams[0];
			m_clrEmi.green = pfParams[1];
			m_clrEmi.blue  = pfParams[2];
			m_clrEmi.alpha = pfParams[3];
			break;
	}
}
