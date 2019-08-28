// Sphere.cpp: implementation of the CVirtualSphere class.

#include "stdafx.h"
#include "Sphere.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSphere::CSphere(int nRadius)
{
	m_nRadius = nRadius;
	if(m_nRadius < 1) m_nRadius = 1;
	m_byRed = 192;
	m_byGreen = 192;
	m_byBlue = 192;

	m_nDifPrecision = 8;
	m_nSpePrecision = 4;

}

CSphere::~CSphere()
{

}

//设置虚拟球的主体颜色
void CSphere::SetColor(BYTE byRed, BYTE byGreen, BYTE byBlue)
{
	m_byRed = byRed;
	m_byGreen = byGreen;
	m_byBlue = byBlue;
}

//设置扩散区域和高光区域的逼近精度
//nDifPrecision-----漫反射区域绘制次数
//nSpePrecision-----高光区域绘制次数
//二者可以决定漫反射区域和高光区域所占有的比例
void CSphere::SetPrecision(int nDifPrecision, int nSpePrecision)
{
	m_nDifPrecision = nDifPrecision;
	m_nSpePrecision = nSpePrecision;
	if(m_nDifPrecision < 1) m_nDifPrecision = 1;
	if(m_nSpePrecision < 1) m_nDifPrecision = 1;
}

//绘制
//(x,y)------左上角位置
void CSphere::Draw(CDC* pDC, int x ,int y)
{
	pDC->SelectStockObject(NULL_PEN);
	//漫反射光逼近次数
	int nDifTimes = min(m_nDifPrecision, m_nRadius);
	
	//分母
	int nDenominator = (7 * nDifTimes);

	//绘制漫反射区域
	for(int i = 0; i < nDifTimes; i++)
	{
		//颜色
		BYTE byRed = (BYTE)((i * m_byRed * 4) / nDenominator + 3 * (int)m_byRed / 7);
		BYTE byGreen = (BYTE)((i * m_byGreen * 4) / nDenominator + 3 * (int)m_byGreen / 7);
		BYTE byBlue = (BYTE)((i * m_byBlue * 4) / nDenominator + 3 * (int)m_byBlue / 7);

		//画刷
		CBrush brush;
		brush.CreateSolidBrush(RGB(byRed, byGreen, byBlue));
		CBrush* pOldBrush = pDC->SelectObject(&brush);
		
		//左上角坐标
		int xLT = x + i;
		int yLT = y + (i * 2) / 5;
		
		//大小
		int nSize = m_nRadius - (5 * i) / 4 + 1;

		//右下角坐标
		int xRB = xLT + nSize;
		int yRB = yLT + nSize;


		//绘制
		pDC->Ellipse(xLT, yLT, xRB, yRB);
		
		pDC->SelectObject(pOldBrush);
		brush.DeleteObject();
	}

	//绘制高光区域
	
	//高光逼近次数
	int nSpeTimes = min(m_nSpePrecision, (m_nRadius - nDifTimes));
	if(nSpeTimes < 1) return;
	
	//暂时变量,分母
	nDenominator = (2 * nSpeTimes);

	
	//绘制高光区域
	for(i = 0; i < nSpeTimes; i++)
	{
		int nIndex = i + nDifTimes;
		//颜色
		BYTE byRed = (BYTE)(m_byRed + ((255 - m_byRed) * i) / nDenominator);
		BYTE byGreen = (BYTE)(m_byGreen + ((255 - m_byGreen) * i) / nDenominator);
		BYTE byBlue = (BYTE)(m_byBlue + ((255 - m_byBlue) * i) / nDenominator);

		//画刷
		CBrush brush;
		brush.CreateSolidBrush(RGB(byRed, byGreen, byBlue));
		CBrush* pOldBrush = pDC->SelectObject(&brush);
		
		//左上角坐标
		int xLT = x + nIndex;
		int yLT = y + (nIndex * 2) / 5;
		
		//大小
		int nSize = m_nRadius - (5 * nIndex) / 4 + 1;

		int xRB = xLT + nSize;
		int yRB = yLT + nSize;


		//绘制
		pDC->Ellipse(xLT, yLT, xRB, yRB);
		
		pDC->SelectObject(pOldBrush);
		brush.DeleteObject();
	}

}
