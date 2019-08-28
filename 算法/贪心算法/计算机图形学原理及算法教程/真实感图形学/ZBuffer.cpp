// ZBuffer.cpp: implementation of the CZBuffer class.
#include "stdafx.h"
#include "ZBuffer.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CZBuffer::CZBuffer(int nWidth,  int nHeight)
{

	m_nWidth = (nWidth < 0) ? 0 : nWidth;
	m_nHeight = (nHeight < 0) ? 0 : nHeight;

	//申请全局内存(z-buffer的缺点)
	m_pfDepth = new float[m_nWidth * m_nHeight];
	
	if(m_pfDepth == NULL)
	{
		AfxMessageBox("内存分配失败!");
		exit(1);
	}
}

CZBuffer::~CZBuffer()
{
	if(m_pfDepth)
	{
		delete[] m_pfDepth;
		m_pfDepth = NULL;
	}
}

//获取深度缓冲区高度
int CZBuffer::GetWidth() const
{
	return m_nWidth;
}


//获取深度缓冲区高度
int CZBuffer::GetHeight() const
{
	return m_nHeight;
}

//获取深度缓冲区指针
float* CZBuffer::GetDepthPtr() const
{
	return m_pfDepth;
}

//初始化深度
void CZBuffer::InitAllDepth(float fDepth)
{
	int nSize = m_nWidth * m_nHeight;
	for(int i = 0; i < 	nSize; i++)
		m_pfDepth[i] = fDepth;
}

//设置深度值
void CZBuffer::SetDepth(int x,  int y,  float fDepth)
{
	if((x < 0) || (y < 0) || (x >= m_nWidth) || (y >= m_nHeight))return;
	int nIndex = y * m_nWidth + x;
	m_pfDepth[nIndex] = fDepth;

}

//获取深度值
float CZBuffer::GetDepth(int x,  int y) const
{
	if((x < 0) || (y < 0) || (x >= m_nWidth) || (y >= m_nHeight))
		return - 1.0f;
	int nIndex = y * m_nWidth + x;
	return m_pfDepth[nIndex];
}
