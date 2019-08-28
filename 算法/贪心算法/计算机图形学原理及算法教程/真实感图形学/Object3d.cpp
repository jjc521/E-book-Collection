	
// Object3d.cpp: implementation of the CObject3d class.

#include "stdafx.h"
#include "Object3d.h"

//////////////////////////////////////////////////////////////////////////////////////////////
//
//					    缺省坐标系
//		
//				X----水平自左向右 [-1.0, 1.0]
//				Y----垂直自下而上 [-1.0, 1.0]
//				Z----水平由里向外 [-1.0, 1.0]
//
//////////////////////////////////////////////////////////////////////////////////////////////
//构造函数
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC(CObject3d, CObject)
CObject3d::CObject3d() : m_bAutoColor(TRUE)
{
	m_vList.SetSize(0);
	m_eList.SetSize(0);
	m_sList.SetSize(0);
	m_mGeomTrans.Identity();
}

CObject3d::~CObject3d()
{
	if(m_vList.GetSize() > 0) m_vList.RemoveAll();
	if(m_eList.GetSize() > 0) m_eList.RemoveAll();
	if(m_sList.GetSize() > 0) m_sList.RemoveAll();
}

//////////////////////////////////////////////////////////////////////////////////////////////
//
//			  获取几何顶点表、边表、面表的大小
//
//////////////////////////////////////////////////////////////////////////////////////////////

//获取顶点表的大小
int CObject3d::GetVertexListSize() const
{
	return m_vList.GetSize();
}

//获取边表大小
int CObject3d::GetEdgeListSize() const
{
	return m_eList.GetSize();
}

//获取面表大小
int CObject3d::GetFacetListSize() const
{
	return m_sList.GetSize();
}


//////////////////////////////////////////////////////////////////////////////////////////////
//
//					  设置和获取自动颜色属性
//
//////////////////////////////////////////////////////////////////////////////////////////////


//设置和获取自动颜色属性
//该设置只影响平面明暗着色模式下的刻面模型绘制和线框模型绘制
void CObject3d::SetAutoColorProperty(BOOL bAutoColor)
{
	m_bAutoColor = bAutoColor;
}
	
//获取自动颜色属性
BOOL CObject3d::GetAutoColorProperty() const
{
	return m_bAutoColor;
}


//////////////////////////////////////////////////////////////////////////////////////////////
//
//					  设置顶点、边、小面颜色  
//
//////////////////////////////////////////////////////////////////////////////////////////////

//设置顶点颜色
//nIndex----顶点号
//rgba------颜色
void CObject3d::SetVertexColor(int nIndex,  const FLOATCOLORRGBA& rgba)
{
	m_vList[nIndex].m_clr = rgba;
}

//设置顶点颜色
//nIndex----顶点号
//rgba------颜色
void CObject3d::SetVertexColor(int nIndex,  const FLOATCOLORRGB& rgb)
{
	m_vList[nIndex].m_clr.red = rgb.red;
	m_vList[nIndex].m_clr.green = rgb.green;
	m_vList[nIndex].m_clr.blue = rgb.blue;
	m_vList[nIndex].m_clr.alpha = 1.0f;	
}

//设置顶点颜色
//nIndex----顶点号
//(fRed, fGreen, fBlue, fAlpha)----颜色
void CObject3d::SetVertexColor(int nIndex,  float fRed,  float fGreen,  float fBlue,  float fAlpha)
{
	m_vList[nIndex].m_clr.red = fRed;
	m_vList[nIndex].m_clr.green = fGreen;
	m_vList[nIndex].m_clr.blue = fBlue;
	m_vList[nIndex].m_clr.alpha = fAlpha;
}


//设置边颜色
//nIndex----边号
//rgba------颜色
void CObject3d::SetEdgeColor(int nIndex,  const FLOATCOLORRGBA& rgba)
{
	m_eList[nIndex].m_clr = rgba;
}

//设置边颜色
//nIndex----边号
//rgba------颜色
void CObject3d::SetEdgeColor(int nIndex,  const FLOATCOLORRGB& rgb)
{
	m_eList[nIndex].m_clr.red = rgb.red;
	m_eList[nIndex].m_clr.green = rgb.green;
	m_eList[nIndex].m_clr.blue = rgb.blue;
	m_eList[nIndex].m_clr.alpha = 1.0f;	
}

//设置边颜色
//nIndex----边号
//(fRed, fGreen, fBlue, fAlpha)----颜色
void CObject3d::SetEdgeColor(int nIndex,  float fRed,  float fGreen,  float fBlue,  float fAlpha)
{
	m_eList[nIndex].m_clr.red = fRed;
	m_eList[nIndex].m_clr.green = fGreen;
	m_eList[nIndex].m_clr.blue = fBlue;
	m_eList[nIndex].m_clr.alpha = fAlpha;
}

//设置小面颜色
//nIndex----面号
//rgba------颜色
void CObject3d::SetFacetColor(int nIndex,  const FLOATCOLORRGBA& rgba)
{
	m_sList[nIndex].m_clr = rgba;
}

//设置小面颜色
//nIndex----小面号
//rgba------颜色
void CObject3d::SetFacetColor(int nIndex,  const FLOATCOLORRGB& rgb)
{
	m_sList[nIndex].m_clr.red = rgb.red;
	m_sList[nIndex].m_clr.green = rgb.green;
	m_sList[nIndex].m_clr.blue = rgb.blue;
	m_sList[nIndex].m_clr.alpha = 1.0f;	
}


//设置小面颜色
//nIndex----小面号
//(fRed, fGreen, fBlue, fAlpha)----颜色
void CObject3d::SetFacetColor(int nIndex,  float fRed,  float fGreen,  float fBlue,  float fAlpha)
{
	m_sList[nIndex].m_clr.red = fRed;
	m_sList[nIndex].m_clr.green = fGreen;
	m_sList[nIndex].m_clr.blue = fBlue;
	m_sList[nIndex].m_clr.alpha = fAlpha;
}

//////////////////////////////////////////////////////////////////////////////////////////////
//
//					  设置顶点、小面法线
//
//////////////////////////////////////////////////////////////////////////////////////////////

//设置顶点法线
//nIndex------索引号
//normal------法线
void CObject3d::SetVertexNormal(int nIndex,  const VECTOR3D& normal)
{
	m_vList[nIndex].m_normal = normal;
}

//设置顶点法线
//nIndex------索引号
//normal------法线
void CObject3d::SetVertexNormal(int nIndex,  float x,  float y,  float z)
{
	m_vList[nIndex].m_normal.x = x;
	m_vList[nIndex].m_normal.y = y;
	m_vList[nIndex].m_normal.z = z;
}

//设置小面法线
//nIndex------索引号
//normal------法线
void CObject3d::SetFacetNormal(int nIndex,  const VECTOR3D& normal)
{
	m_sList[nIndex].m_normal = normal;
}

//设置小面法线
//nIndex------索引号
//normal------法线
void CObject3d::SetFacetNormal(int nIndex,  float x,  float y,  float z)
{
	m_sList[nIndex].m_normal.x = x;
	m_sList[nIndex].m_normal.y = y;
	m_sList[nIndex].m_normal.z = z;
}

//////////////////////////////////////////////////////////////////////////////////////////////
//
//					  计算顶点、小面法线
//
//////////////////////////////////////////////////////////////////////////////////////////////

//计算小面法线
VECTOR3D CObject3d::CalcSingleFacetNoraml(const HOMOCOORD& v1,  const HOMOCOORD& v2,  const HOMOCOORD& v3)
{
	//如果一个三角形中包含无穷远点, 则该三角形是一个畸形三角形, 
	float w1 = v1.w,  w2 = v2.w,  w3 = v3.w;
	if(ABS(w1) <= 0.00001f) w1 = 1.0f;
	if(ABS(w2) <= 0.00001f) w2 = 1.0f;
	if(ABS(w3) <= 0.00001f) w3 = 1.0f;

	float x1 = v1.x / w1,  y1 = v1.y / w1,  z1 = v1.z / w1;
	float x2 = v2.x / w2,  y2 = v2.y / w2,  z2 = v2.z / w2;
	float x3 = v3.x / w3,  y3 = v3.y / w3,  z3 = v3.z / w3;

	CVector3d vector1((x2 - x1),  (y2 - y1),  (z2 - z1)); 
	CVector3d vector2((x3 - x1),  (y3 - y1),  (z3 - z1)); 
	CVector3d noraml = vector1 * vector2;
	VECTOR3D n = {noraml.x,  noraml.y,  noraml.z};
	return n;
}

//计算面的法线(由顶点计算)
void CObject3d::CalcFacetNormals()
{
	//获取小面个数
	int nNumFacet = m_sList.GetSize();

	//面循环
	for(int i = 0; i < nNumFacet; i++)
	{
		//一个面至少应有三个顶点			
		ASSERT(m_sList[i].m_avIndex.GetSize() > 2);
		
		//获取顶点索引号
		int n1 = m_sList[i].m_avIndex[0];
		int n2 = m_sList[i].m_avIndex[1];
		int n3 = m_sList[i].m_avIndex[2];
		m_sList[i].m_normal = this->CalcSingleFacetNoraml(m_vList[n1].m_coord,  m_vList[n2].m_coord,  m_vList[n3].m_coord);
	}
}

//计算顶点的平均法线(面的法线计算)
//顶点的平均法线为与该顶点相连的面的法线的平均值
void CObject3d::EvenVertexNormals()
{
	//获取顶点个数
	int nNumVertex = m_vList.GetSize();
	
	//顶点循环
	for(int i = 0; i < nNumVertex; i++)
	{
		//获取当前顶点所在小面的序号
		int nNumInFacet = m_vList[i].m_asIndex.GetSize();
		if(nNumInFacet > 0)
		{
			//小面法线
			CVector3d nv(0.0f, 0.0f, 0.0f);
			for(int j = 0; j < nNumInFacet; j++)
			{
				//小面号
				int n = m_vList[i].m_asIndex[j];
				
				//法线相加
				nv += m_sList[n].m_normal;
			}// end for j
			
			//顶点的最后法线
			nv.Unitize();
			
			//赋值(公有成员)
			m_vList[i].m_normal.x = nv.x;
			m_vList[i].m_normal.y = nv.y;
			m_vList[i].m_normal.z = nv.z;

		}//end if

	}//end  for i
}	


//////////////////////////////////////////////////////////////////////////////////////////////
//
//					  几何变换  
//
//////////////////////////////////////////////////////////////////////////////////////////////

//变换(累积变换)
void CObject3d::Transform(CMatrix3d m)
{
	//获取顶点个数
	int nNumVertex = m_vList.GetSize();
	for(int i = 0; i < nNumVertex; i++)
		m_vList[i].m_coord = m.Transform(m_vList[i].m_coord);

	//将 m 累积到 m_mGeomTrans ,  从而记录复合变换的结果
	m_mGeomTrans.Multiply(m, G3D_MATRIX_MULTIPLIER_POSTCONCAT);
}

//变换法线, m为已经的变换矩阵, 适用于刚体运动
void CObject3d::TransVertexNormals(CMatrix3d m)
{
	//获取顶点个数
	int nNumVertex = m_vList.GetSize();
	for(int i = 0; i < nNumVertex; i++)
		m_vList[i].m_normal = m.Transform(m_vList[i].m_normal);
}

//变换法线, m为已经的变换矩阵, 适用于刚体运动
void CObject3d::TransFacetNormals(CMatrix3d m)
{
	//获取小面个数
	int nNumFacet = m_sList.GetSize();
	for(int i = 0; i < nNumFacet; i++)
		m_sList[i].m_normal = m.Transform(m_sList[i].m_normal);
}


//获取位置
CMatrix3d  CObject3d::GetPosition() const 
{
	return m_mGeomTrans;
}




//////////////////////////////////////////////////////////////////////////////////////////////
//
//					  其它编辑顶点表、边表、面表的操作（略）  
//
//////////////////////////////////////////////////////////////////////////////////////////////
