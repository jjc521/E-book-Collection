// SubObject3d.h: interface for the CSubObject3d class.

#ifndef _CSUBOBJ3D_H
#define _CSUBOBJ3D_H
#include "Grphcs.h"

class CSubObject3d 
{
public:
	CSubObject3d();
	virtual ~CSubObject3d();

public:

	//次物体颜色:浮点颜色,RGBA颜色模型
	FLOATCOLORRGBA m_clr;

	//顶点可见性
	BOOL m_bVisibility;
	
	//关于次物体的操作
	//本书不涉及这部分内容
	//and so on
};

#endif 
