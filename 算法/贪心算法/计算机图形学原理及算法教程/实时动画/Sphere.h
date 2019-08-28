// Sphere.h: interface for the CVirtualSphere class.

#ifndef _CVSPHERE_H
#define _CVSPHERE_H

class CSphere  
{
public:
	CSphere(int nRadius);
	virtual ~CSphere();

public:

	void SetColor(BYTE byRed, BYTE byGreen, BYTE byBlue);
	void SetPrecision(int nDifPrecision, int nSpePrecision);
	void Draw(CDC* pDC, int x, int y);

private:

	//半径
	int m_nRadius;

	//主体颜色
	BYTE m_byRed, m_byGreen, m_byBlue;
	
	//精细程度

	//扩散色区域的逼近次数
	int m_nDifPrecision;

	//高光区域的逼近次数
	int m_nSpePrecision;

};

#endif 
