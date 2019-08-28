/////////////////////////////////////////////////////////////////////////////////
//	
// BLine.cpp: implementation of the CBLine class.
#include "stdafx.h"
#include "BLine.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBLine::CBLine()
{
}

CBLine::~CBLine()
{
}

//绘制一条直线,直线的宽度为1,直线的颜色由直线两个端点的颜色共同决定
//注意,浮点颜色的有效值为[0,1]区间内的浮点小数
//与Windows相对应,该算法也不包含最后一个点(x2,y2)
//z1,z2为当前点的深度值
//pCB,pZB分别为颜色缓冲和深度缓冲
//注意,从(x1,y1)--(x2,y2)与(x2,y2)--(x1,y1)略有些许不同.
//评价:该函数绘制的直线(像素位置)与Windows的LineTo()函数绘制的结果是完全一致的
void CBLine::Draw(int x1,int y1,  int x2, int y2, float z1, float z2, FLOATCOLORRGBA clr1, FLOATCOLORRGBA clr2, CColorBuffer* pCB, CZBuffer* pZB)
{
	//两端点间的水平偏移量和垂直偏移量
	int nDx = x2 - x1;	
	int nDy = y2 - y1;

	//两端点间的水平距离和垂直距离
	int nIx = ABS(nDx);
	int nIy = ABS(nDy);

	//描点步数(增量总值)
	int nInc = MAX(nIx,nIy);

	//直线当前点的颜色
	float fPlotR = clr1.red, fPlotG = clr1.green, fPlotB = clr1.blue, fPlotA = clr1.alpha; 

	////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////
	//主要考察区,开始
	
	//缓冲区中的深度
	float zInBuffer = pZB->GetDepth(x1,y1);
	//当前深度
	float z = z1;
	
	//如果当前点的z坐标小于深度缓冲区中的相同位置z的坐标
	if(z < zInBuffer)
	{
		//在颜色缓冲区中绘制第一个点
		pCB->SetPixel(x1, y1, fPlotR, fPlotG, fPlotB, fPlotA); 

		//重置深度缓冲区的值
		pZB->SetDepth(x1, y1, z);
	
	}
	
	if(nInc < 2) return;

	//沿直线的深度增量
	float fIncZ = (z2 - z1) / nInc;

	//结束	
	////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////


	//用于判断是否在nJudgeX,nJudgeY方向上向前进
	int nJudgeX = -nIy, nJudgeY = -nIx;

	//通过增量计算得到的当前点
	int x = x1, y = y1;
	
	//开始进行增量计算
	//采用Bresenham算法.在这里,我们将算法进行改进,
	//使其对于任意斜率的直线都能绘制,而且绘制方向始终为从起点绘制到终点

	//与Windows相对应,该算法也不包含最后一个点(x2,y2)
	nInc--;

	//注意,整数乘2在计算机中采用移位实现
	//Bresenham算法
	int nTwoIx = 2 * nIx, nTwoIy = 2 * nIy;

	//颜色增量
	float fIncR = (clr2.red - fPlotR) / nInc;
	float fIncG = (clr2.green - fPlotG) / nInc;
	float fIncB = (clr2.blue - fPlotB) / nInc;
	float fIncA = (clr2.alpha - fPlotA) / nInc;


	//开始增量计算
	for(int i = 0;i < nInc; i++)
	{
		nJudgeX += nTwoIx;
		nJudgeY += nTwoIy;

		//通过增量法计算的当前点是否属于直线上的点
		BOOL bPlot = FALSE;

		//检测 nJudgeX 方向
		if(nJudgeX >= 0)
		{
			bPlot = TRUE;
			nJudgeX -= nTwoIy;

			//将任意走向的直线统一起来
			if(nDx > 0)x++;
			else if(nDx < 0)x--;
		}

		//检测 nJudgeY 方向
		if(nJudgeY >= 0)
		{
			bPlot = TRUE;
			nJudgeY -= nTwoIx;

			//将任意走向的直线统一起来
			if(nDy > 0)y++;
			else if(nDy < 0)y--;
		}
		//如果当前点在直线上
		if(bPlot)
		{
			fPlotR += fIncR;
			fPlotG += fIncG;
			fPlotB += fIncB;
			fPlotA += fIncA;
			
			////////////////////////////////////////////////////////////////////////
			////////////////////////////////////////////////////////////////////////
			//主要考察区,开始

			z += fIncZ; 
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
}


void CBLine::Draw(POINT pt1, POINT pt2, float z1, float z2, FLOATCOLORRGBA clr1, FLOATCOLORRGBA clr2, CColorBuffer* pCB, CZBuffer* pZB)
{
	Draw(pt1.x, pt1.y, pt2.x, pt2.y, z1, z2, clr1, clr2, pCB, pZB);
}