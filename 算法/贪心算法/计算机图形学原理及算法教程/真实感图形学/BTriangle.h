// BTriangle.h: interface for the CBTriangle class.
//基于Z缓冲区的三角形扫描转换

#ifndef _CBTRIANGLE_H
#define _CBTRIANGLE_H

#include "ColorBuffer.h"
#include "ZBuffer.h"

class CBTriangle  
{
public:
	CBTriangle();
	virtual ~CBTriangle();

public:
	//采用Gouraud明暗着色方法填充三角形
	void Draw(POINT pt1, POINT pt2, POINT pt3, float z1, float z2, float z3, FLOATCOLORRGBA clr1, FLOATCOLORRGBA clr2, FLOATCOLORRGBA clr3, CColorBuffer* pCB, CZBuffer* pZB);

private:

	//绘制并获取边信息:
	void DealEdge(int x1, int y1, int x2, int y2, float z1, float z2, FLOATCOLORRGBA clr1, FLOATCOLORRGBA clr2, CColorBuffer* pCB, CZBuffer* pZB, int* pnCoord, FLOATCOLORRGBA* pColor, float* pfDepth,DWORD dwFeature = G3D_TRIANGLE_ON_LINE_RIGHT);
	//处理扫描线
	void Scan(int x1, int x2, int nScanLine, float z1, float z2, FLOATCOLORRGBA clr1, FLOATCOLORRGBA clr2, CColorBuffer* pCB, CZBuffer* pZB);
};

#endif 
