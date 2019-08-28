// ZBuffer.h: interface for the CZBuffer class.

//32位深度缓冲

#ifndef _CZBUFFER_H
#define _CZBUFFER_H 

class CZBuffer  
{
public:
	CZBuffer(int nWidth, int nHeight);
	virtual ~CZBuffer();


public:

	//获取深度缓冲区宽度
	int GetWidth() const;
	//获取深度缓冲区高度
	int GetHeight() const;
	//获取深度缓冲区指针
	float* GetDepthPtr() const;

	//初始化深度
	void InitAllDepth(float fDepth);

	//设置深度值
	void SetDepth(int x, int y, float fDepth);

	//获取深度值
	float GetDepth(int x, int y) const;


private:
	
	//宽度
	int	m_nWidth;
	//高度
	int m_nHeight;

	//深度值
	float* m_pfDepth;
};
#endif 
