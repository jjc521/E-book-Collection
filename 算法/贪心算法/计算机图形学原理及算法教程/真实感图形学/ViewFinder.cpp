// ViewFinder.cpp: implementation of the CViewFinder class.
#include "stdafx.h"
#include "ViewFinder.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CViewFinder::CViewFinder(VIEWFINDER viewFinder) : m_viewFinder(viewFinder)
{}

CViewFinder::~CViewFinder()
{}

//将观察坐标系下的点变换到屏幕坐标系
//事实上, 这个变换适合于视点在Z坐标上的情形
//vertex----观察坐标系下的点
POINT CViewFinder::Perspective(VERTEX3D vertex)
{
	float xe = vertex.x,  ye = vertex.y,  ze = vertex.z;

	//对于ze = 0.0f的情况, 这里只作简化处理:
	if(ABS(ze) < 0.00001f) ze = 1.0f;

	//屏幕上的点
	POINT pt;
	pt.x = (int)((xe * m_viewFinder.fDistView) / ze * m_viewFinder.xScale
				+ m_viewFinder.ptCenter.x);
	
	//右手平面直角坐标系变为左手直角坐标系
	pt.y = (int)((-ye * m_viewFinder.fDistView) / ze * m_viewFinder.yScale
				+ m_viewFinder.ptCenter.y);

	return pt;
}

//将观察坐标系下的点变换到屏幕坐标系
//vertex----观察坐标系下的点
POINT CViewFinder::Perspective(HOMOCOORD vertex)
{
	VERTEX3D v;
	float w = vertex.w;
	//对于一个无穷远点
	if(ABS(w) <= 0.00001f)
	{
		v.x = vertex.x;
		v.y = vertex.y;
		v.z = 1000000.0f;
	}
	else
	{
		v.x = vertex.x / w;
		v.y = vertex.y / w;
		v.z = vertex.z / w;
	}
	return (Perspective(v));
}
