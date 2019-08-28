/////////////////////////////////////////////////////////////////////////////////
//	
// Object3d.h: interface for the CObject3d class.

//三维物体,定义或变换于世界坐标系

#ifndef _COBJECT3D_H
#define _COBJECT3D_H
#include "Vertex3d.h"
#include "Edge.h"
#include "Facet.h"
#include "Matrix3d.h"
#include "Vector3d.h"

class CObject3d : public CObject 
{
DECLARE_DYNAMIC(CObject3d)
public:
	CObject3d();
	virtual ~CObject3d();
	

public:

	//设置自动颜色属性
	void SetAutoColorProperty(BOOL bAutoColor);

	//获取自动颜色属性
	BOOL GetAutoColorProperty() const;

	//获取顶点表的大小
	int GetVertexListSize() const;
	//获取边表大小
	int GetEdgeListSize() const;
	//获取面表大小
	int GetFacetListSize() const;

	//设置顶点颜色
	void SetVertexColor(int nIndex, const FLOATCOLORRGBA& rgba);
	void SetVertexColor(int nIndex, const FLOATCOLORRGB& rgb);
	void SetVertexColor(int nIndex, float fRed, float fGreen, float fBlue, float fAlpha = 1.0f);

	//设置边颜色
	void SetEdgeColor(int nIndex, const FLOATCOLORRGBA& rgba);
	void SetEdgeColor(int nIndex, const FLOATCOLORRGB& rgb);
	void SetEdgeColor(int nIndex, float fRed, float fGreen, float fBlue, float fAlpha = 1.0f);
	
	//设置小面颜色
	void SetFacetColor(int nIndex, const FLOATCOLORRGBA& rgba);
	void SetFacetColor(int nIndex, const FLOATCOLORRGB& rgb);
	void SetFacetColor(int nIndex, float fRed, float fGreen, float fBlue, float fAlpha = 1.0f);


	//几何变换(世界坐标系,顶点)
	void Transform(CMatrix3d m);

	//变换法线,适用于刚体运动
	void TransVertexNormals(CMatrix3d m);
	void TransFacetNormals(CMatrix3d m);


	//获取相对位置
	CMatrix3d GetPosition() const;

	//设置顶点法线
	void SetVertexNormal(int nIndex, const VECTOR3D& normal);
	void SetVertexNormal(int nIndex, float x, float y, float z);

	//设置小面法线
	void SetFacetNormal(int nIndex, const VECTOR3D& normal);
	void SetFacetNormal(int nIndex, float x, float y, float z);

	//计算小面法线
	VECTOR3D CalcSingleFacetNoraml(const HOMOCOORD& v1, const HOMOCOORD& v2, const HOMOCOORD& v3);
	//计算面的法线(由顶点计算)
	void CalcFacetNormals();


	//计算顶点的平均法线(由面的法线计算)
	void EvenVertexNormals();
	


public:

	//需要应用该类的数据的类有: CPRender等,可以设置这些类为该类的友好类,然后增加保护措施和提供访问数据的机制.
	//为了方便访问,我们简单地设置它们为公有成员变量

	//顶点表
	CArray<CVertex3d,CVertex3d> m_vList;

	//边表
	CArray<CEdge,CEdge> m_eList;

	//面表
	CArray<CFacet,CFacet> m_sList;

protected:

	//变换矩阵
	CMatrix3d m_mGeomTrans;

	BOOL m_bAutoColor;
};

#endif 

