/////////////////////////////////////////////////////////////////////////////////
//	
// LightObj.cpp: implementation of the CLightObj class.
#include "stdafx.h"
#include "LightObj.h"
#include "math.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLightObj::CLightObj()
{
	//缺省光源为一全向白色点光源
	m_clrAmb.red  = 0.0f;		m_clrAmb.green = 0.0f;
	m_clrAmb.blue = 0.0f;		m_clrAmb.alpha = 1.0f;

	m_clrDif.red  = 1.0f;		m_clrDif.green = 1.0f;
	m_clrDif.blue = 1.0f;		m_clrDif.alpha = 1.0f;

	m_clrSpe.red  = 1.0f;		m_clrSpe.green = 1.0f;
	m_clrSpe.blue = 1.0f;		m_clrSpe.alpha = 1.0f;
	
	m_hcPosition.x = 0.0f;		m_hcPosition.y = 0.0f;
	m_hcPosition.z = 8.0f;		m_hcPosition.w = 1.0f;

	m_spotDirection.x = 0.0f;	m_spotDirection.y = 0.0f;
	m_spotDirection.z = -1.0f;


	m_fSpotExp = 0.0f;
	m_fSpotCutoff = 180.0f;
	m_fAttCoef0 = 1.0f;
	m_fAttCoef1 = 0.0f;
	m_fAttCoef2 = 0.0f;
	m_bOnOff = TRUE;
}

CLightObj::CLightObj(const CLightObj& light)
{
	m_clrAmb = light.m_clrAmb;
	m_clrDif = light.m_clrDif;
	m_clrSpe = light.m_clrSpe;
	m_hcPosition = light.m_hcPosition;
	m_spotDirection = light.m_spotDirection;

	m_fSpotExp = light.m_fSpotExp;
	m_fSpotCutoff = light.m_fSpotCutoff;
	m_fAttCoef0 = light.m_fAttCoef0;
	m_fAttCoef1 = light.m_fAttCoef1;
	m_fAttCoef2 = light.m_fAttCoef2;
	m_bOnOff = light.m_bOnOff;
}

CLightObj::~CLightObj()
{}

//设置光源是否可以开启
//形式上统一, 第一个参数为G3D_LIGHT_ON_OFF有效
void CLightObj::Lightb(DWORD dwProperty,  BOOL bOnOff)
{
	if(dwProperty == G3D_LIGHT_ON_OFF) m_bOnOff = bOnOff;
}

//dwProperty----属性
//fParam------参数值, 标量
void CLightObj::Lightf(DWORD dwProperty,  float fParam)
{
	switch(dwProperty)
	{
		//聚光指数
		case G3D_SPOT_EXPONENT:
			//发散指数在[0, 128]之间
			m_fSpotExp = (fParam < 0.0f) ? 0.0f : ((fParam > 128.0f) ? 128.0f : fParam);
			break;
		//发散半角
		case G3D_SPOT_CUTOFF:
			//发散半角取 [0, 90] 或 180
			if(ABS(fParam - 180.0f) < 0.001f) m_fSpotCutoff = 180.0f;
			else
				m_fSpotCutoff = (fParam < 0.0f) ? 0.0f : ((fParam > 90.0f) ? 90.0f : fParam);
			break;
		//常数衰减因子
		case G3D_CONSTANT_ATTENUATION:
			m_fAttCoef0 = ABS(fParam);
			break;
		//线性衰减因子
		case G3D_LINEAR_ATTENUATION:
			m_fAttCoef1 = ABS(fParam);
			break;

		//二次衰减因子
		case G3D_QUADRATIC_ATTENUATION:
			m_fAttCoef2 = ABS(fParam);
			break;
	}
}

//参数设置, 向量值(一维数组)
//dwProperty----属性
//pfParams------参数值, 按 RGBA 顺序或 XYZW 顺序组织数据

void CLightObj::Lightfv(DWORD dwProperty,  const float* pfParams)
{
	ASSERT(pfParams);
	switch(dwProperty)
	{
		//环境光
		case G3D_AMBIENT:
			m_clrAmb.red   = pfParams[0];
			m_clrAmb.green = pfParams[1];
			m_clrAmb.blue  = pfParams[2];
			m_clrAmb.alpha = pfParams[3];
			break;
		//漫反射光
		case G3D_DIFFUSE:
			m_clrDif.red   = pfParams[0];
			m_clrDif.green = pfParams[1];
			m_clrDif.blue  = pfParams[2];
			m_clrDif.alpha = pfParams[3];
			break;
		//镜面高光
		case G3D_SPECULAR:
			m_clrSpe.red   = pfParams[0];
			m_clrSpe.green = pfParams[1];
			m_clrSpe.blue  = pfParams[2];
			m_clrSpe.alpha = pfParams[3];

			break;
		//光的位置
		case G3D_POSITION:
			m_hcPosition.x = pfParams[0];
			m_hcPosition.y = pfParams[1];
			m_hcPosition.z = pfParams[2];
			m_hcPosition.w = pfParams[3];
			break;

		//聚光照射方向(非齐次坐标)
		case G3D_SPOT_DIRECTION:
			
			//直接单位化
			float fMag = (float)sqrt(pfParams[0] * pfParams[0] + 
							pfParams[1] * pfParams[1] +
							pfParams[2] * pfParams[2]);
			
			//对于退化向量, 将照射方向移至 z 轴
			if(fMag < 0.0001f)
			{
				m_spotDirection.x = 0.0f;
				m_spotDirection.y = 0.0f;
				m_spotDirection.z = -1.0f;
			}
			else
			{
				m_spotDirection.x = pfParams[0] / fMag;
				m_spotDirection.y = pfParams[1] / fMag;
				m_spotDirection.z = pfParams[2] / fMag;
			}
			break;
	}
}

