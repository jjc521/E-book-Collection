/////////////////////////////////////////////////////////////////////////////////
//	
// Lighting.cpp: implementation of the CLighting class.
#include "stdafx.h"
#include "Lighting.h"

//#include "FloatColor.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLighting::CLighting()
{
	m_clrGlobalAmb.red  = 0.2f;		m_clrGlobalAmb.green = 0.2f;
	m_clrGlobalAmb.blue = 0.2f;		m_clrGlobalAmb.alpha = 1.0f;
	
	//缺省值: 无穷远视点模型
	m_bLocalViewer = FALSE;

	//缺省值:只照射前面
	m_bTwoSides = FALSE;
}

CLighting::~CLighting()
{
}

//设置光照模型
void CLighting::LightModelb(DWORD dwProperty,  BOOL bParam)
{
	if(dwProperty == G3D_LIGHT_MODEL_LOCAL_VIEWER)
		m_bLocalViewer = bParam;
	else if(dwProperty == G3D_LIGHT_MODEL_TWO_SIDE)
		m_bTwoSides = bParam;
}

//设置全局环境光
void CLighting::LightModelfv(DWORD dwProperty,  const float* pfParams)
{
	if(dwProperty == G3D_LIGHT_MODEL_AMBIENT)
	{
		m_clrGlobalAmb.red   = pfParams[0];
		m_clrGlobalAmb.green = pfParams[1];
		m_clrGlobalAmb.blue  = pfParams[2];
		m_clrGlobalAmb.alpha = pfParams[3];
	}
}

//光照计算
//pObj---------被光照的物体    (单个物体)
//material-----物体标准材质
//viewer-------视点, 用于光照计算, 被定义于世界坐标系
//lights-------多光源
//nNumLight----光源个数
void CLighting::Lighting(CObject3d* pObj,  const CMaterial& material,  VERTEX3D viewer,  const CLightObj* lights,  int nNumLight)
{
	//注:   该光照计算在世界坐标系中完成

	ASSERT(pObj);
	ASSERT(lights);

	//显式表示视点, 它被定义于世界坐标系
	float xViewer = viewer.x,   yViewer = viewer.y,   zViewer = viewer.z;

	//定义一个无穷远视点观察向量, 
	//
	CVector3d vLocalView(xViewer,  yViewer,  zViewer);

	//如果计算高光时采用无穷远视点, 则现在就单位化, 这将减少大量的计算
	
	if(!m_bLocalViewer)
		vLocalView.Unitize();

	
	//物体顶点个数
	int nNumVertex = pObj->GetVertexListSize();

	//开始计算
	// i 按物体顶点个数计算循环,  j 则按光源个数进行循环
	for(int i = 0; i < nNumVertex; i++)
	{
		
		//获取物体的第 i 个顶点:
		float xVertex = pObj->m_vList[i].m_coord.x;
		float yVertex = pObj->m_vList[i].m_coord.y;
		float zVertex = pObj->m_vList[i].m_coord.z;
		float wVertex = pObj->m_vList[i].m_coord.w;

		//将齐次坐标转化为真实坐标
		//无穷远点, 近似地用 0.0001 来代替(扩大齐次坐标10000倍的点来代替无穷远点的颜色)
		//不必考虑 wVertex 趋近于 0 时的符号
		if(ABS(wVertex) < 0.0001f)wVertex = 0.0001f;
		
		xVertex /= wVertex;
		yVertex /= wVertex;
		zVertex /= wVertex;

		//顶点最后的颜色
		//第一项, 物体辐射颜色, 这是直接贡献项
		float fLastR = material.m_clrEmi.red;
		float fLastG = material.m_clrEmi.green;
		float fLastB = material.m_clrEmi.blue;
		
		//全局环境光的贡献
		//全局环境光 * 材质对环境光的反射系数 ----- 
		//分量对应相乘后, 累积至最后的颜色之中.
		fLastR += (m_clrGlobalAmb.red * material.m_refAmb.red);
		fLastG += (m_clrGlobalAmb.green * material.m_refAmb.green);
		fLastB += (m_clrGlobalAmb.blue * material.m_refAmb.blue);

		//来自于光源的贡献
		float fr,  fg,  fb;

		for(int j = 0; j < nNumLight; j++)
		{
			//如果光源是开启的
			if(lights[j].m_bOnOff)
			{
				//其一, 计算衰减系数

				//衰减系数.等于1.0则不衰减
				float fAttenuCoef = 1.0f;
				
				//获取第 j 个光源位置
				float xLight = lights[j].m_hcPosition.x;
				float yLight = lights[j].m_hcPosition.y;
				float zLight = lights[j].m_hcPosition.z;
				float wLight = lights[j].m_hcPosition.w;


				//只有点光源我们才认为它是可衰减的, 此时, w = 1.0f.
				//如果光源是平行光源, 即定向光源, 则不衰减, 时时, w = 0.0f

				//定位光源
				if(ABS(wLight) > 0.0001f)
				{
					//真实位置, 保持齐次坐标分量不变
					xLight /= wLight;
					yLight /= wLight;
					zLight /= wLight;
					
					//常数衰减系数
					fAttenuCoef = lights[j].m_fAttCoef0;
					
					//一次衰减系数与二次衰减系数
					float fc1 = lights[j].m_fAttCoef1;
					float fc2 = lights[j].m_fAttCoef2;
					if((fc1 > 0.0001f) || (fc2 > 0.0001f))
					{
						//求顶点至光源的距离
						float fDist = (float)sqrt((xLight - xVertex) * (xLight - xVertex) +
										   (yLight - yVertex) * (yLight - yVertex) +
										   (zLight - zVertex) * (zLight - zVertex) );
					
						//加入一次和二次因子
						fAttenuCoef += (fc1 * fDist + fc2 * fDist * fDist);
					}
					
					if(fAttenuCoef < 0.0001f) fAttenuCoef = 0.0001f;
					fAttenuCoef = 1.0f / fAttenuCoef;

					//衰减系数不得大于1.0
					fAttenuCoef = MIN(1.0f,  fAttenuCoef);
				
				}
				
				//计算聚光因子

				//聚光因子, 一般点光源的聚光因子为 1.0f, (发散半角为180度)
				float fSpotFactor = 1.0f;
				
				//发散半角
				float fCutoff = lights[j].m_fSpotCutoff;

				//聚光产生的条件:第一, 光为定位光源; 第二, 光的发散半角小于或等于90度
				if((ABS(wLight) > 0.0001f) && (fCutoff < 90.0001f))
				{
					//光源的真实位置已经为(xLight,  yLight,  zLight), 
					//定向光源不产生聚光效果
					
					//向量: 聚光位置指向照射顶点
					CVector3d vLightToVertex((xVertex - xLight),  (yVertex - yLight),  (zVertex - zLight));
					
					//单位化
					vLightToVertex.Unitize();

					//聚光照射方向(已经是一个单位向量) 与 向量 vLightToVertex 夹角的余弦
					float fInsideCone = vLightToVertex.Dot(lights[j].m_spotDirection);

					//如果顶点位于光锥之外, 则不会有聚光光线照射到物体上
					if(fInsideCone < (float)cos((fCutoff * PIE) / 180.0))
						fSpotFactor = 0.0f;
					else
					{
						//利用聚光指数进行计算
						fSpotFactor = (float)pow(fInsideCone,  lights[j].m_fSpotExp);
					}
				
				}//enf if ---- for calculating spot factor
				

				// 计算来自光源的贡献(现在已经有足够的条件了)
				
				//加入环境反射部分:
				fr = material.m_refAmb.red * lights[j].m_clrAmb.red;
				fg = material.m_refAmb.green * lights[j].m_clrAmb.green;
				fb = material.m_refAmb.blue * lights[j].m_clrAmb.blue;

				//其次, 计算漫反射部分
				
				//顶点指向光源的向量
				CVector3d vVertexToLight((xLight - xVertex),  (yLight - yVertex),  (zLight - zVertex)); 
				
				//如果光源为平行光源(定位光源)
				if((ABS(wLight) <= 0.0001f))
				{
					//光源的位置就是照射方向, 因而顶点至光源的向量就是光源位置向量的相反向量
					vVertexToLight.x = -xLight;
					vVertexToLight.y = -yLight;
					vVertexToLight.z = -zLight;
				}
				
				//单位化
				vVertexToLight.Unitize();

				//顶点法线向量与 vVertexToLight 向量的夹角的余弦
				//顶点法线应是单位向量, 这在建模时已经或必须保证的
				float fCos = vVertexToLight.Dot(pObj->m_vList[i].m_normal);
				
				fCos = (fCos < 0.0f) ? 0.0f : fCos;

				//加入漫反射部分的贡献
				fr += (material.m_refDif.red * lights[j].m_clrDif.red * fCos);
				fg += (material.m_refDif.green * lights[j].m_clrDif.green * fCos);
				fb += (material.m_refDif.blue * lights[j].m_clrDif.blue * fCos);

				// 计算高光部分

				//如果顶点法线与顶点至光源的向量夹角大于90度, 则没有高光产生
				//否则就产生
				if(fCos > 0.0f)
				{
					//计算顶点指向视点的单位向量:
					CVector3d vVertexToViewer;
					
					//无穷远视点模型
					if(!m_bLocalViewer)
					{
						vVertexToViewer = vLocalView;
					}
					//局部视点模型
					else
					{
						vVertexToViewer.x = (xViewer - xVertex);
						vVertexToViewer.y = (yViewer - yVertex);
						vVertexToViewer.z = (zViewer - zVertex);
						//单位化:
						vVertexToViewer.Unitize();
					}
					
					//加上顶点指向光源的单位向量:
					vVertexToViewer += vVertexToLight;
					
					//再次单位化:
					vVertexToViewer.Unitize();

					//光度因子基数:与顶点法线作点积
					float fShine = vVertexToViewer.Dot(pObj->m_vList[i].m_normal);
					fShine = (fShine < 0.0f) ? 0.0f : fShine;
					float fShineFactor = (float)pow(fShine,  material.m_fShininess);
					
					//加入高光部分的贡献
					fr += (material.m_refSpe.red * lights[j].m_clrSpe.red * fShineFactor);
					fg += (material.m_refSpe.green * lights[j].m_clrSpe.green * fShineFactor);
					fb += (material.m_refSpe.blue * lights[j].m_clrSpe.blue * fShineFactor);
				}// end if(fCos > 0.0f)
				
				//最后乘以衰减和聚光因子，第 j 个光对物体的第个顶点的照射:
				fr *= (fAttenuCoef * fSpotFactor);
				fg *= (fAttenuCoef * fSpotFactor);
				fb *= (fAttenuCoef * fSpotFactor);

				//累加至最后颜色:
				fLastR += fr;
				fLastG += fg;
				fLastB += fb;
			}// end if(lights[0].m_bOnOff)
		}//end j (number of lights)
		
		//作颜色归一化处理:
		fLastR = (fLastR < 0.0f) ? 0.0f : ((fLastR > 1.0f) ? 1.0f : fLastR);
		fLastG = (fLastG < 0.0f) ? 0.0f : ((fLastG > 1.0f) ? 1.0f : fLastG);
		fLastB = (fLastB < 0.0f) ? 0.0f : ((fLastB > 1.0f) ? 1.0f : fLastB);

		//颜色赋值:
		pObj->m_vList[i].m_clr.red = fLastR;
		pObj->m_vList[i].m_clr.green = fLastG;
		pObj->m_vList[i].m_clr.blue = fLastB;

		//对于alpha, 这里简单地用材质漫反射属性来代替
		pObj->m_vList[i].m_clr.alpha = material.m_refDif.alpha;

	}

}