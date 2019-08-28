/////////////////////////////////////////////////////////////////////////////////
//	
// BTriangle.cpp: implementation of the CBTriangle class.
#include "stdafx.h"
#include "BTriangle.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBTriangle::CBTriangle()
{}

CBTriangle::~CBTriangle(){}

void CBTriangle::DealEdge(int x1, int y1, int x2, int y2, float z1, float z2, FLOATCOLORRGBA clr1, FLOATCOLORRGBA clr2, CColorBuffer* pCB, CZBuffer* pZB, int* pnCoord, FLOATCOLORRGBA* pColor, float* pfDepth, DWORD dwFeature)
{
	//各数组的长度应该是y坐标差的绝对值加1,
	ASSERT(pnCoord);
	ASSERT(pColor);
	ASSERT(pfDepth);

	//对于一条水平直线,则简单地返回第一个点的坐标和颜色
	//对于一条水平直线,我们不区分区域相对它的左右关系.
	if(y1 == y2)
	{
		pnCoord[0] = x1;
		pColor[0] = clr1;
		pfDepth[0] = z1;
		return;
	}

	//下面考查直线斜率不为0的情况:

	//两端点间的水平偏移量和垂直偏移量
	int nDx = x2 - x1;	
	int nDy = y2 - y1;

	//两端点间的水平距离和垂直距离
	int nIx = ABS(nDx);
	int nIy = ABS(nDy);

	//描点步数(增量总值)
	int nInc = MAX(nIx,nIy);
	
	//用于判断是否在nJudgeX,nJudgeY方向上向前进
	int nJudgeX = -nIy, nJudgeY = -nIx;

	//通过增量计算得到的当前点
	int x = x1, y = y1;

	//Bresenham算法
	int nTwoIx = 2 * nIx, nTwoIy = 2 * nIy;

	//直线当前点的颜色
	float fPlotR = clr1.red, fPlotG = clr1.green, fPlotB = clr1.blue; 
	float fPlotA = clr1.alpha;

	//颜色增量
	float fIncR = (clr2.red - fPlotR) / nInc;
	float fIncG = (clr2.green - fPlotG) / nInc;
	float fIncB = (clr2.blue - fPlotB) / nInc;
	float fIncA = (clr2.alpha - fPlotA) / nInc;

	//水平边界段起点和终点
	FLOATCOLORRGBA clrStart = {fPlotR,fPlotG,fPlotB,fPlotA};
	FLOATCOLORRGBA clrEnd = clrStart;

	//数组下标，水平边界段起点和终点的 x 坐标
	int nIndex = 0, nStartX = x1, nEndX = x1;
	
	//水平边界段起点和终点的 z 坐标,当前点的 z 坐标
	//以及 z 坐标增量
	float fStartZ = z1, fEndZ = z1, z = z1, fIncZ = (z2 - z1) / nInc; 

	
	//根据深度值绘制第一个点
	//缓冲区中的深度
	float zInBuffer = pZB->GetDepth(x1,y1);
	
	//如果当前点的z坐标小于深度缓冲区中的相同位置z的坐标
	if(z < zInBuffer)
	{
		//在颜色缓冲区中绘制第一个点
		pCB->SetPixel(x1, y1, fPlotR, fPlotG, fPlotB, fPlotA); 

		//重置深度缓冲区的值
		pZB->SetDepth(x1, y1, z);
	}

	//开始增量计算
	for(int i = 0;i <= nInc; i++)
	{
		nJudgeX += nTwoIx;
		nJudgeY += nTwoIy;

		//通过增量法计算的当前点是否属于直线上的点
		BOOL bRecord = FALSE;
		
		//当前点是否为直线上的点
		BOOL bPlot = FALSE;

		//先检测 y 方向
		if(nJudgeY >= 0)
		{
			bPlot = TRUE;
			bRecord = TRUE;
			nJudgeY -= nTwoIx;

			//将任意走向的直线统一起来
			if(nDy > 0)
			{
				nEndX = x;
				y++;
				//水平边界段终点的颜色
				clrEnd.red = fPlotR;
				clrEnd.green = fPlotG;
				clrEnd.blue = fPlotB;
				clrEnd.alpha = fPlotA;
				//水平边界段终点的深度(沿边进行插值计算而获得)
				fEndZ = z;
			}
			else if(nDy < 0)
			{
				nEndX = x;
				y--;
				//水平边界段终点的颜色
				clrEnd.red = fPlotR;
				clrEnd.green = fPlotG;
				clrEnd.blue = fPlotB;
				clrEnd.alpha = fPlotA;
				//水平边界段终点的深度(沿边进行插值计算而获得)
				fEndZ = z;
			}
		}//end if 

		//后检测 x 方向
		if(nJudgeX >= 0)
		{
			bPlot = TRUE;
			nJudgeX -= nTwoIy;

			//将任意走向的直线统一起来
			if(nDx > 0)x++;
			else if(nDx < 0)x--;
		}

		if(bPlot)
		{
			fPlotR += fIncR;
			fPlotG += fIncG;
			fPlotB += fIncB;
			fPlotA += fIncA;
			
			z += fIncZ;
			if(i < (nInc - 1))
			{
				//根据深度值绘制第一个点
				zInBuffer = pZB->GetDepth(x,y);
				
				//如果当前点的z坐标小于深度缓冲区中的相同位置z的坐标
				if(z < zInBuffer)
				{
					//在颜色缓冲区中绘制第一个点
					pCB->SetPixel(x, y, fPlotR, fPlotG, fPlotB, fPlotA); 

					//重置深度缓冲区的值
					pZB->SetDepth(x, y, z);
				
				}
			}

		}

		//如果当前点在直线上,则记录当前点
		if(bRecord)
		{
			//取最左边点,区域在左侧
			if(dwFeature == G3D_TRIANGLE_ON_LINE_LEFT)
			{
				//取x坐标最小者
				if(nStartX < nEndX)
				{
					pnCoord[nIndex] = nStartX;	
					pColor[nIndex] = clrStart;
					pfDepth[nIndex] = fStartZ;
				}
				else
				{
					pnCoord[nIndex] = nEndX;	
					pColor[nIndex] = clrEnd;
					pfDepth[nIndex] = fEndZ;
				}
			}//end if
				
			//取最右边点,区域在右侧
			else
			{
				//取x坐标最大者
				if(nStartX < nEndX)
				{
					pnCoord[nIndex] = nEndX;	
					pColor[nIndex] = clrEnd;
					pfDepth[nIndex] = fEndZ;
				}
				else
				{
					pnCoord[nIndex] = nStartX;	
					pColor[nIndex] = clrStart;
					pfDepth[nIndex] = fStartZ;
				}
			}//end else
			
			nIndex++;

			//下一个起点
			nStartX = x;
			
			//下一个起点的 z 坐标
			fStartZ = z;

			//下一个起点的颜色
			clrStart.red = fPlotR;
			clrStart.green = fPlotG;
			clrStart.blue = fPlotB;
			clrStart.alpha = fPlotA;
		}
	}

	//当斜率的很小时,y坐标增长缓慢,这时需要特别处理
	if(nIndex < (ABS(y2 - y1) + 1))
	{
		//取最左边点,区域在左侧
		if(dwFeature == G3D_TRIANGLE_ON_LINE_LEFT)
		{
			//取x坐标最小者
			if(nStartX < x2)
			{
				pnCoord[nIndex] = nStartX;	
				pColor[nIndex] = clrStart;
				pfDepth[nIndex] = fStartZ;
			}
			else
			{
				pnCoord[nIndex] = x2;
				pColor[nIndex] = clr2;
				pfDepth[nIndex] = z2;
			}

		}//end if
		//取最右边点,区域在右侧
		else
		{
			//取x坐标最大者
			if(nStartX < x2)
			{
				pnCoord[nIndex] = x2;	
				pColor[nIndex] = clr2;
				pfDepth[nIndex] = z2;
			}
			else
			{
				pnCoord[nIndex] = nStartX;	
				pColor[nIndex] = clrStart;
				pfDepth[nIndex] = fStartZ;
			}
		}//end else
	}//end if(nIndex < (ABS(y2 - y1) + 1))
}

void CBTriangle::Scan(int x1, int x2, int nScanLine, float z1, float z2, FLOATCOLORRGBA clr1, FLOATCOLORRGBA clr2, CColorBuffer* pCB, CZBuffer* pZB)
{
	//填充像素个数 
	int nFillPixels = ABS(x2 - x1);
	//如果为同一个点或距离相差为0,则返回;
	if(nFillPixels < 2) return;


	//颜色增量(颜色差值 / 份数)
	float fIncR = (clr2.red - clr1.red) / nFillPixels;
	float fIncG = (clr2.green - clr1.green) / nFillPixels;
	float fIncB = (clr2.blue - clr1.blue) / nFillPixels;
	float fIncA = (clr2.alpha - clr1.alpha) / nFillPixels;


	//当前颜色
	float fRed = clr1.red + fIncR;
	float fGreen = clr1.green + fIncG;
	float fBlue = clr1.blue + fIncB;
	float fAlpha = clr1.alpha + fIncA;

	//填充方向
	int nDirection = (x1 < x2) ? 1 : -1;

	//当前x坐标
	int x = x1 + nDirection;


	//当前 z 坐标, z坐标增量,
	//注意 我们并没有采用平面系数法计算深度
	float z = z1, fIncZ = (z2 - z1) / nFillPixels;
	z += fIncZ;

	nFillPixels--;
	//开始填充
	for(int i = 0; i < nFillPixels ; i++)
	{
		float zInBuffer = pZB->GetDepth(x,nScanLine);
				
		//如果当前点的z坐标小于深度缓冲区中的相同位置z的坐标
		if(z < zInBuffer)
		{
			//在颜色缓冲区中绘制第一个点
			pCB->SetPixel(x, nScanLine, fRed, fGreen, fBlue, fAlpha); 

			//重置深度缓冲区的值
			pZB->SetDepth(x, nScanLine, z);
		}

		//增量计算
		x += nDirection;
		z += fIncZ;
		fRed += fIncR;
		fGreen += fIncG;
		fBlue += fIncB;
		fAlpha += fIncA;
	}
} 

//扫描转换三角形

void CBTriangle::Draw(POINT pt1, POINT pt2, POINT pt3, float z1, float z2, float z3, FLOATCOLORRGBA clr1, FLOATCOLORRGBA clr2, FLOATCOLORRGBA clr3, CColorBuffer* pCB, CZBuffer* pZB)
{
	ASSERT(pCB);
	ASSERT(pZB);
	
	
	if((pt1.y == pt2.y) && (pt2.y == pt3.y))
	{
		//pt1位于中间(采用矢量点积进行判断)
		if((pt2.x - pt1.x) * (pt3.x - pt1.x) <= 0)
		{
			Scan(pt1.x, pt2.x, pt1.y, z1, z2, clr1, clr2, pCB, pZB);
			Scan(pt1.x, pt3.x, pt1.y, z1, z3, clr1, clr3, pCB, pZB);
		}
		//pt2位于中间
		else if((pt1.x - pt2.x) * (pt3.x - pt2.x) <= 0)
		{
			Scan(pt2.x, pt1.x, pt1.y, z2, z1, clr2, clr1, pCB, pZB);
			Scan(pt2.x, pt3.x, pt1.y, z2, z3, clr2, clr3, pCB, pZB);
		}
		//pt3位于中间
		else 
		{
			Scan(pt3.x, pt1.x, pt1.y, z3, z1, clr3, clr1, pCB, pZB);
			Scan(pt3.x, pt2.x, pt1.y, z3, z2, clr3, clr2, pCB, pZB);
		}

		//增加三个端点
		float zInBuffer = pZB->GetDepth(pt1.x, pt1.y);
				
		//如果当前点的z坐标小于深度缓冲区中的相同位置z的坐标
		if(z1 < zInBuffer)
		{
			//在颜色缓冲区中绘制第一个点
			pCB->SetPixel(pt1.x, pt1.y, clr1.red, clr1.green, clr1.blue, clr1.alpha);
			//重置深度缓冲区的值
			pZB->SetDepth(pt1.x, pt1.y, z1);
		}

		//
		zInBuffer = pZB->GetDepth(pt2.x, pt2.y);
				
		//如果当前点的z坐标小于深度缓冲区中的相同位置z的坐标
		if(z2 < zInBuffer)
		{
			//在颜色缓冲区中绘制第一个点
			pCB->SetPixel(pt2.x, pt2.y, clr2.red, clr2.green, clr2.blue, clr2.alpha);
			//重置深度缓冲区的值
			pZB->SetDepth(pt2.x, pt2.y, z2);
		}

		zInBuffer = pZB->GetDepth(pt3.x, pt3.y);
				
		//如果当前点的z坐标小于深度缓冲区中的相同位置z的坐标
		if(z3 < zInBuffer)
		{
			//在颜色缓冲区中绘制第一个点
			pCB->SetPixel(pt3.x, pt3.y, clr3.red, clr3.green, clr3.blue, clr3.alpha);
			//重置深度缓冲区的值
			pZB->SetDepth(pt3.x, pt3.y, z3);
		}

		return;
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////

	POINT point1 = pt1, point2 = pt2, point3 = pt3;
	FLOATCOLORRGBA color1 = clr1, color2 = clr2, color3 = clr3;
	float fz1 = z1, fz2 = z2, fz3 = z3;

	//point1记录y坐标最小者
	if(point1.y > point2.y)
	{
		point1 = pt2;
		point2 = pt1;

		color1 = clr2;
		color2 = clr1;

		fz1 = z2;
		fz2 = z1;
	}
	if(point1.y > point3.y) 
	{
		POINT ptTemp = point1;
		FLOATCOLORRGBA clrTemp = color1;
		float zTemp = fz1;
		point1 = point3;
		color1 = color3;
		fz1 = fz3;

		point3 = ptTemp;
		color3 = clrTemp;
		fz3 = zTemp;
	}
	//point2记录y坐标最大者
	if(point2.y < point3.y)
	{
		POINT ptTemp = point2;
		FLOATCOLORRGBA clrTemp = color2;
		float zTemp = fz2;
		point2 = point3;
		color2 = color3;
		fz2 = fz3;

		point3 = ptTemp;
		color3 = clrTemp;
		fz3 = zTemp;
	}


	//获取边界点的 x 坐标,计算边界颜色
	//12 --- 1 to 2, 13 ---- 1 to 3,  32 ---- 3 to 2
	//y坐标之间的距离
	int nDy12 = (point2.y - point1.y) + 1;
	int nDy13 = (point3.y - point1.y) + 1;
	int nDy32 = (point2.y - point3.y) + 1;
	//获取扫描线的 x 坐标
	int* pnEdge12 = new int[nDy12];
	int* pnEdge13 = new int[nDy13];
	int* pnEdge32 = new int[nDy32];
		
	//获取边界颜色
	//注意,这里支持透明计算,因而颜色用三个分量
	FLOATCOLORRGBA* pClrEdge12 = new FLOATCOLORRGBA[nDy12];
	FLOATCOLORRGBA* pClrEdge13 = new FLOATCOLORRGBA[nDy13];
	FLOATCOLORRGBA* pClrEdge32 = new FLOATCOLORRGBA[nDy32];

	//记录边界深度
	float* pfzEdge12 = new float[nDy12];
	float* pfzEdge13 = new float[nDy13];
	float* pfzEdge32 = new float[nDy32];


	//获取边界及其颜色

	//计算矢量叉积(只需要计算Z分量),以判断三角形的位置关系
	int nDelta = ((point3.x - point1.x) * (point2.y - point3.y)
				 - (point2.x - point3.x) * (point3.y - point1.y));

	if(nDelta > 0)
	{
		DealEdge(point1.x, point1.y, point2.x, point2.y, fz1, fz2, color1, color2, pCB, pZB, pnEdge12, pClrEdge12, pfzEdge12); 
		DealEdge(point1.x, point1.y, point3.x, point3.y, fz1, fz3, color1, color3, pCB, pZB, pnEdge13, pClrEdge13, pfzEdge13, G3D_TRIANGLE_ON_LINE_LEFT); 
		DealEdge(point3.x, point3.y, point2.x, point2.y, fz3, fz2, color3, color2, pCB, pZB, pnEdge32, pClrEdge32, pfzEdge32, G3D_TRIANGLE_ON_LINE_LEFT); 
	}
	else
	{
		DealEdge(point1.x, point1.y, point2.x, point2.y, fz1, fz2, color1, color2, pCB, pZB, pnEdge12, pClrEdge12, pfzEdge12, G3D_TRIANGLE_ON_LINE_LEFT); 
		DealEdge(point1.x, point1.y, point3.x, point3.y, fz1, fz3, color1, color3, pCB, pZB, pnEdge13, pClrEdge13, pfzEdge13);
		DealEdge(point3.x, point3.y, point2.x, point2.y, fz3, fz2, color3, color2, pCB, pZB, pnEdge32, pClrEdge32, pfzEdge32);
	}

	//绘制最后一个点
	//CPLine基元与Windows绘制直线的方式是一致的,即不绘制最后一个点

	float zInBuffer = pZB->GetDepth(point2.x, point2.y);
			
	//如果当前点的z坐标小于深度缓冲区中的相同位置z的坐标
	if(fz2 < zInBuffer)
	{
		//在颜色缓冲区中绘制第一个点
		pCB->SetPixel(point2.x, point2.y, color2.red, color2.green, color2.blue, color2.alpha);
		//重置深度缓冲区的值
		pZB->SetDepth(point2.x, point2.y, fz2);
	}
	//第三个顶点
	if(point3.y == point2.y)
	{
		zInBuffer = pZB->GetDepth(point3.x, point3.y);
				
		//如果当前点的z坐标小于深度缓冲区中的相同位置z的坐标
		if(fz3 < zInBuffer)
		{
			//在颜色缓冲区中绘制第一个点
			pCB->SetPixel(point3.x, point3.y, color3.red, color3.green, color3.blue, color3.alpha);
			//重置深度缓冲区的值
			pZB->SetDepth(point3.x, point3.y, fz3);
		}	
	}

	
	int y, nPlumbScan = 0;
	if(point1.y < point3.y)
	{
		for(y = point1.y; y < point3.y; y++)
		{
			//一条扫描线的x坐标
			int	x12 = pnEdge12[nPlumbScan];
			int	x13 = pnEdge13[nPlumbScan];
			
			//一条扫描线的深度变化
			float z12 = pfzEdge12[nPlumbScan];
			float z13 = pfzEdge13[nPlumbScan];

			//颜色
			FLOATCOLORRGBA clrEdge12 = pClrEdge12[nPlumbScan];
			FLOATCOLORRGBA clrEdge13 = pClrEdge13[nPlumbScan];
			
			//填充
			Scan(x12, x13, y, z12, z13, clrEdge12,clrEdge13, pCB, pZB);

			nPlumbScan++;
		}//end for y
	
	}
	
	int nPlumbScan32 = 0;
	for(y = point3.y; y <= point2.y; y++)
	{
		//一条扫描线的x坐标
		int	x12 = pnEdge12[nPlumbScan];
		int	x32 = pnEdge32[nPlumbScan32];

		//一条扫描线的深度变化
		float z12 = pfzEdge12[nPlumbScan];
		float z32 = pfzEdge32[nPlumbScan32];

		//颜色
		FLOATCOLORRGBA clrEdge12 = pClrEdge12[nPlumbScan];
		FLOATCOLORRGBA clrEdge32 = pClrEdge32[nPlumbScan32];

		//填充
		Scan(x12, x32, y, z12, z32, clrEdge12,clrEdge32, pCB, pZB);

		nPlumbScan++;
		nPlumbScan32++;

	}//end for y

	delete[] pnEdge12;
	delete[] pnEdge13;
	delete[] pnEdge32;
	delete[] pClrEdge12;
	delete[] pClrEdge13;
	delete[] pClrEdge32;
	delete[] pfzEdge12;
	delete[] pfzEdge13;
	delete[] pfzEdge32;
}

