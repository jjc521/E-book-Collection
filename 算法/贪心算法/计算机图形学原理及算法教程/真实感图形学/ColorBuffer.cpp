/////////////////////////////////////////////////////////////////////////////////
//	
// ColorBuffer.cpp: implementation of the CColorBuffer class.
#include "stdafx.h"
#include "ColorBuffer.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CColorBuffer::CColorBuffer(int nWidth,  int nHeight)
{

	m_nWidth = (nWidth < 0) ? 0 : nWidth;
	m_nHeight = (nHeight < 0) ? 0 : nHeight;

	//申请全局内存(z-buffer的缺点)
	//并将颜色清成黑色
	m_pbyColor = new BYTE[m_nWidth * m_nHeight * 4];
	
	if(m_pbyColor == NULL)
	{
		AfxMessageBox("内存分配失败!");
		exit(1);
	}
	memset(m_pbyColor,  0,  m_nWidth * m_nHeight * 4);
 
}

CColorBuffer::~CColorBuffer()
{
	if(m_pbyColor)
	{
		delete[] m_pbyColor;
		m_pbyColor = NULL;
	}
}


//查询函数

//获取颜色缓冲区宽度
int CColorBuffer::GetWidth() const
{
	return m_nWidth;
}

//获取颜色缓冲区高度
int CColorBuffer::GetHeight() const
{
	return m_nHeight;
}

//获取颜色缓冲区指针
BYTE* CColorBuffer::GetColorPtr() const
{
	return m_pbyColor;
}

//设置背景颜色

//将指定的颜色设置为背景色
//单一颜色(r, g, b, a)
void CColorBuffer::SetBkColor(BYTE r,  BYTE g,  BYTE b,  BYTE a)
{
	//蓝, 绿, 红, alpha
	BYTE* pbyColor = m_pbyColor;
	for(int i = 0; i < m_nWidth; i++)
	{
		*pbyColor++ = b;
		*pbyColor++ = g;
		*pbyColor++ = r;
		*pbyColor++ = a;
	}

	//内存之间拷贝, 拷贝剩下的 (m_nHeight - 1)行.
	DWORD dwScanLength = 4 * (DWORD)m_nWidth;
	for(i = 1; i < m_nHeight; i++)
	{
		//指向一行开始的位置
		pbyColor = m_pbyColor + (i * dwScanLength);
		//从第一行拷贝至第 i 行:
		memcpy(pbyColor,  m_pbyColor,  dwScanLength);
	}
}

//设置为一个指定的背景图像
//使用时的警告:图像必须与颜色缓冲区尺寸完全相同!
void CColorBuffer::SetBkImage(const BYTE* pbyImage,  int nWidth,  int nHeight)
{
	ASSERT(pbyImage);
	if((nWidth != m_nWidth) || (nHeight != m_nHeight))
	{
		::AfxMessageBox("图像尺寸与颜色缓冲区大小不匹配");
		return;
	}

	::CopyMemory(m_pbyColor,  pbyImage,  m_nWidth * m_nHeight * 4);
}


//设置一个点的颜色
//这是z-buffer算法关于颜色缓冲区的主要操作
void CColorBuffer::SetPixel(int x,  int y,  float r,  float g,  float b , float a)
{
	if((x < 0) || (y < 0) || (x >= m_nWidth) || (y >= m_nHeight))return;

	DWORD dwIndex = y * m_nWidth * 4 + 4 * x;

	BYTE byRed = (BYTE)(r * 255.0f);
	BYTE byGreen = (BYTE)(g * 255.0f);
	BYTE byBlue = (BYTE)(b * 255.0f);
	BYTE byAlpha = (BYTE)(a * 255.0f);
	BYTE* pbyColor = (m_pbyColor + dwIndex);
	*pbyColor++ = byBlue;
	*pbyColor++ = byGreen;
	*pbyColor++ = byRed;
	*pbyColor++ = byAlpha;
}


void CColorBuffer::SetPixel(int x,  int y,  BYTE r,  BYTE g,  BYTE b ,  BYTE a)
{
	if((x < 0) || (y < 0) || (x >= m_nWidth) || (y >= m_nHeight))return;

	DWORD dwIndex = y * m_nWidth * 4 + 4 * x;

	BYTE* pbyColor = m_pbyColor + dwIndex;

	//蓝、绿、红、Alpha
	*pbyColor++ = b;
	*pbyColor++ = g;
	*pbyColor++ = r;
	*pbyColor++ = a;
} 

//获取颜色
PIXELCOLORRGBA CColorBuffer::GetPixel(int x,  int y) const
{
	PIXELCOLORRGBA rgba = {0,  0,  0,  0};
	
	if((x < 0) || (y < 0) || (x >= m_nWidth) || (y >= m_nHeight))
		return rgba;

	DWORD dwIndex = y * m_nWidth * 4 + 4 * x;

	BYTE* pbyColor = m_pbyColor + dwIndex;

	
	//蓝、绿、红、Alpha
	rgba.blue = *pbyColor++;
	rgba.green = *pbyColor++;
	rgba.red = *pbyColor++;
	rgba.alpha = *pbyColor++;
	return rgba;
}

//由颜色缓冲区中的数据直接创建一个DDB对象, 即HBITMAP对象
HBITMAP CColorBuffer::CreateDdb(HDC hDC)
{
	// 创建一个BITMAPV4HEADER结构

	//分配内存:
	BYTE* pbyBits = new BYTE[sizeof(BITMAPV4HEADER)];
	if(pbyBits == NULL) return NULL;
	//指向像素数据的指针, 
	BITMAPV4HEADER* pbmih = (BITMAPV4HEADER*)pbyBits;
	
	pbmih->bV4Size = sizeof(BITMAPV4HEADER);	//108
	pbmih->bV4Width = (LONG)m_nWidth;
	pbmih->bV4Height = (LONG)(-m_nHeight);
	pbmih->bV4Planes = 1;
	pbmih->bV4BitCount = 32;

    pbmih->bV4V4Compression = BI_RGB;    
	pbmih->bV4SizeImage = 0;
	pbmih->bV4XPelsPerMeter = 0;    
	pbmih->bV4YPelsPerMeter = 0;
	pbmih->bV4ClrUsed = 0;    
	pbmih->bV4ClrImportant = 0;
 
	//第二步, 创建一个DDB
	HBITMAP hBitmap = ::CreateDIBitmap(hDC, (BITMAPINFOHEADER*)pbmih, CBM_INIT, m_pbyColor, (BITMAPINFO*)pbmih, DIB_RGB_COLORS);

	delete[] pbyBits;
	return hBitmap;
}

//将颜色缓冲区的内容交换到前台(即输出颜色缓冲区)
void CColorBuffer::SwapBuffer(CDC* pDC)
{
	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	HBITMAP hBitmap = CreateDdb(pDC->m_hDC);
	HBITMAP hOldBitmap = (HBITMAP)memDC.SelectObject(hBitmap);
	pDC->BitBlt(0, 0, m_nWidth, m_nHeight, &memDC, 0, 0, SRCCOPY);
	::DeleteObject(hBitmap);
	memDC.SelectObject(hOldBitmap);
}