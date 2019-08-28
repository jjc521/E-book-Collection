// ViewFinder.h: interface for the CViewFinder class.

#ifndef _CVIEWFINDER_H
#define _CVIEWFINDER_H
#include "Grphcs.h"

class CViewFinder  
{
public:
	CViewFinder(VIEWFINDER viewFinder);
	virtual ~CViewFinder();

public:

	//将观察坐标系下的点变换到屏幕坐标系,vertex----观察坐标系下的点
	POINT Perspective(VERTEX3D vertex);

	//将观察坐标系下的点变换到屏幕坐标系,vertex----观察坐标系下的点
	POINT Perspective(HOMOCOORD vertex);

private:
	//取景参数
	VIEWFINDER m_viewFinder;
};

#endif 
