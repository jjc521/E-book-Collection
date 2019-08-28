// FloatColor.h: interface for the CFloatColor class.
#ifndef _CFLOATCOLOR_H
#define _CFLOATCOLOR_H
#include "Grphcs.h"

class CFloatColor  
{
public:
	CFloatColor();
	CFloatColor(float red , float green, float blue, float alpha  = 1.0f);
	CFloatColor(const FLOATCOLORRGB& rgb);
	CFloatColor(const FLOATCOLORRGBA& rgba);
	virtual ~CFloatColor();

public:

	//设置颜色
	void Set(float red,float green,float blue,float alpha = 1.0f);

	//获取颜色
	FLOATCOLORRGB  GetRGB() const;
	FLOATCOLORRGBA GetRGBA() const;

	//重载 "=" 运算符
	inline CFloatColor operator = (const FLOATCOLORRGB& rgb);
	inline CFloatColor operator = (const CFloatColor& color);
	inline CFloatColor operator = (const FLOATCOLORRGBA& rgba);

	//重载 "+" 运算符
	inline CFloatColor operator + (const FLOATCOLORRGB& rgb);
	inline CFloatColor operator + (const CFloatColor& color);
	inline CFloatColor operator + (const FLOATCOLORRGBA& rgba);

	//重载 "+=" 运算符
	inline CFloatColor operator += (const FLOATCOLORRGB& rgb);
	inline CFloatColor operator += (const CFloatColor& color);
	inline CFloatColor operator += (const FLOATCOLORRGBA& rgba);

	//重载 "*" 运算符
	inline CFloatColor operator * (const FLOATCOLORRGB& rgb);
	inline CFloatColor operator * (const CFloatColor& color);
	inline CFloatColor operator * (const FLOATCOLORRGBA& rgba);
	inline CFloatColor operator * (float fc);

	//重载 "*=" 运算符
	inline CFloatColor operator *= (const FLOATCOLORRGB& rgb);
	inline CFloatColor operator *= (const CFloatColor& color);
	inline CFloatColor operator *= (const FLOATCOLORRGBA& rgba);
	inline CFloatColor operator *= (float fc);

	//颜色归一化处理
	inline CFloatColor Clamp();

public:

	//浮点颜色
	float  red, green, blue, alpha;

};
#endif 


//////////////////////////////////////////////////////////////////////////////////////////////
//
//					  运算符重载  
//
//////////////////////////////////////////////////////////////////////////////////////////////

//重载 "=" 运算符
inline CFloatColor CFloatColor::operator = (const CFloatColor& color)
{
	red = color.red;
	green = color.green;
	blue = color.blue;
	alpha = color.alpha;
	return *this;
}

//重载 "=" 运算符
inline CFloatColor CFloatColor::operator = (const FLOATCOLORRGB& rgb)
{
	red = rgb.red;
	green = rgb.green;
	blue = rgb.blue;
	alpha = 1.0f;
	return *this;
}

//重载 "=" 运算符,
inline CFloatColor CFloatColor::operator = (const FLOATCOLORRGBA& rgba)
{
	red = rgba.red;
	green = rgba.green;
	blue = rgba.blue;
	alpha = rgba.alpha;
	return *this;
}


//重载 "+" 运算符
inline CFloatColor CFloatColor::operator + (const CFloatColor& color)
{
	CFloatColor clr;
	clr.red =   red   + color.red;
	clr.green = green + color.green;
	clr.blue =  blue  + color.blue;

	//对于 alpha 分量,在这里,我们也简单地执行代数加法
	clr.alpha = alpha + color.alpha;
	return clr;
}

//重载 "+" 运算符
inline CFloatColor CFloatColor::operator + (const FLOATCOLORRGB& rgb)
{
	CFloatColor clr;
	clr.red =   red   + rgb.red;
	clr.green = green + rgb.green;
	clr.blue =  blue  + rgb.blue;

	//对于 alpha 分量,在这里,我们也简单地用1.0代替
	clr.alpha = 1.0f;
	return clr;
}

//重载 "+" 运算符,
inline CFloatColor CFloatColor::operator + (const FLOATCOLORRGBA& rgba)
{
	CFloatColor clr;
	clr.red =   red   + rgba.red;
	clr.green = green + rgba.green;
	clr.blue =  blue  + rgba.blue;
	clr.alpha = alpha + rgba.alpha;
	return clr;
}

//重载 "+=" 运算符
inline CFloatColor CFloatColor::operator += (const CFloatColor& color)
{
	red   += color.red;
	green += color.green;
	blue  += color.blue;
	alpha += color.alpha;
	return *this;
}

//重载 "+=" 运算符
inline CFloatColor CFloatColor::operator += (const FLOATCOLORRGB& rgb)
{
	red   += rgb.red;
	green += rgb.green;
	blue  += rgb.blue;
	alpha = 1.0f;
	return *this;
}

//重载 "+=" 运算符,
inline CFloatColor CFloatColor::operator += (const FLOATCOLORRGBA& rgba)
{
	red   += rgba.red;
	green += rgba.green;
	blue  += rgba.blue;
	alpha += rgba.alpha;
	return *this;
}

//重载 "*" 运算符
inline CFloatColor CFloatColor::operator * (const CFloatColor& color)
{
	CFloatColor clr;
	clr.red =   red   * color.red;
	clr.green = green * color.green;
	clr.blue =  blue  * color.blue;
	clr.alpha = alpha * color.alpha;
	return clr;
}

//重载 "*" 运算符
inline CFloatColor CFloatColor::operator * (const FLOATCOLORRGB& rgb)
{
	CFloatColor clr;
	clr.red =   red   * rgb.red;
	clr.green = green * rgb.green;
	clr.blue =  blue  * rgb.blue;

	//alpha 分量将保持不变
	clr.alpha = alpha; 
	return clr;
}

//重载 "*" 运算符,
inline CFloatColor CFloatColor::operator * (const FLOATCOLORRGBA& rgba)
{
	CFloatColor clr;
	clr.red =   red   * rgba.red;
	clr.green = green * rgba.green;
	clr.blue =  blue  * rgba.blue;
	clr.alpha = alpha * rgba.alpha;
	return clr;
}

//重载 "*" 运算符,
inline CFloatColor CFloatColor::operator * (float fc)
{
	CFloatColor clr;
	clr.red =   red   * fc;
	clr.green = green * fc;
	clr.blue =  blue  * fc;
	clr.alpha = alpha * fc;
	return clr;
}

//////////////////////
//重载 "*=" 运算符
inline CFloatColor CFloatColor::operator *= (const CFloatColor& color)
{
	red   *= color.red;
	green *= color.green;
	blue  *= color.blue;
	alpha *= color.alpha;
	return *this;
}

//重载 "*=" 运算符
inline CFloatColor CFloatColor::operator *= (const FLOATCOLORRGB& rgb)
{
	red   *= rgb.red;
	green *= rgb.green;
	blue  *= rgb.blue;
	return *this;
}

//重载 "*=" 运算符,
inline CFloatColor CFloatColor::operator *= (const FLOATCOLORRGBA& rgba)
{
	red   *= rgba.red;
	green *= rgba.green;
	blue  *= rgba.blue;
	alpha *= rgba.alpha;
	return *this;
}

//重载 "*=" 运算符,
inline CFloatColor CFloatColor::operator *= (float fc)
{
	red   *= fc;
	green *= fc;
	blue  *= fc;
	alpha *= fc;
	return *this;
}



//	颜色归一化处理
inline CFloatColor CFloatColor::Clamp()
{
	CFloatColor clr;
	clr.red = (red < 0.0f) ? 0.0f : ((red > 1.0f) ? 1.0f : red);
	clr.green = (green < 0.0f) ? 0.0f : ((green > 1.0f) ? 1.0f : green);
	clr.blue = (blue < 0.0f) ? 0.0f : ((blue > 1.0f) ? 1.0f : blue);
	clr.alpha = (alpha < 0.0f) ? 0.0f : ((alpha > 1.0f) ? 1.0f : alpha);
	return clr;
}