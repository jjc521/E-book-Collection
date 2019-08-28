// ColorBuffer.h: interface for the CColorBuffer class.

//软件方法操作颜色缓冲区

#ifndef _CCOLORBUFFER_H
#define _CCOLORBUFFER_H
#include "Grphcs.h"
#include "Img.h"

class CColorBuffer  
{
public:
	CColorBuffer(int nWidth, int nHeight);
	virtual ~CColorBuffer();

public:

	//获取颜色缓冲区宽度
	int GetWidth() const;
	//获取颜色缓冲区高度
	int GetHeight() const;
	//获取颜色缓冲区指针
	BYTE* GetColorPtr() const;

	//将指定的颜色设置为背景色
	void SetBkColor(BYTE r, BYTE g, BYTE b, BYTE a);
	
	//将一个与颜色缓冲区等大小的图像设置为背景
	void SetBkImage(const BYTE* pbyImage, int nWidth, int nHeight);

	//设置一个点的颜色
	void SetPixel(int x, int y, float r, float g, float b , float a = 1.0f);

	void SetPixel(int x, int y, BYTE r, BYTE g, BYTE b , BYTE a = 255);
	
	//获取颜色
	PIXELCOLORRGBA GetPixel(int x, int y) const;

	//由颜色缓冲区的数据创建一个内存位图对象(句柄)
	HBITMAP CColorBuffer::CreateDdb(HDC hDC);

	//将颜色缓冲区的内容交换到前台(即输出颜色缓冲区)
	void CColorBuffer::SwapBuffer(CDC* pDC);


private:
	//颜色缓冲区大小
	int m_nWidth;
	int m_nHeight;
	
	//颜色缓冲区
	BYTE* m_pbyColor;

};

#endif 
