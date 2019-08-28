// BLine.h: interface for the CBLine class.
//基于 z-buffer 和 color-buffer 的 Bresenham 直线生成算法

#ifndef _CBLINE_H
#define _CBLINE_H

#include "ColorBuffer.h"
#include "ZBuffer.h"

class CBLine  
{
public:
	CBLine();
	virtual ~CBLine();

public:
	void Draw(int x1,int y1, int x2, int y2, float z1, float z2, FLOATCOLORRGBA clr1, FLOATCOLORRGBA clr2, CColorBuffer* pCB, CZBuffer* pZB);
	void Draw(POINT pt1, POINT pt2, float z1, float z2, FLOATCOLORRGBA clr1, FLOATCOLORRGBA clr2, CColorBuffer* pCB, CZBuffer* pZB);
};

#endif 
