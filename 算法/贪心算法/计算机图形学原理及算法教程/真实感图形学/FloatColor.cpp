/////////////////////////////////////////////////////////////////////////////////
//	
// FloatColor.cpp: implementation of the CFloatColor class.
#include "stdafx.h"
#include "FloatColor.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFloatColor::CFloatColor() : red(0.0f), green(0.0f), blue(0.0f), alpha(1.0f)
{}

CFloatColor::CFloatColor(float red ,  float green,  float blue,  float alpha ) 
{
	this->red = red;
	this->green = green;
	this->blue = blue;
	this->alpha = alpha;
}

CFloatColor::CFloatColor(const FLOATCOLORRGB& rgb)
{
	red = rgb.red;
	green = rgb.green;
	blue = rgb.blue;
	alpha = 1.0f;		
}

CFloatColor::CFloatColor(const FLOATCOLORRGBA& rgba)
{
	red = rgba.red;
	green = rgba.green;
	blue = rgba.blue;
	alpha = rgba.alpha;
}

CFloatColor::~CFloatColor()
{}

//////////////////////////////////////////////////////////////////////////////////////////////
//
//					  设置与获取颜色
//
//////////////////////////////////////////////////////////////////////////////////////////////

//设置颜色
void CFloatColor::Set(float red, float green, float blue, float alpha)
{
	this->red = red;
	this->green = green;
	this->blue = blue;
	this->alpha = alpha;
}

//获取颜色, 不含透明信息alpha
FLOATCOLORRGB CFloatColor::GetRGB() const
{
	FLOATCOLORRGB rgb;
	rgb.red = red;
	rgb.green = green;
	rgb.blue = blue;
	return rgb;
}

//获取颜色, 含透明信息alpha
FLOATCOLORRGBA CFloatColor::GetRGBA() const
{
	FLOATCOLORRGBA rgba;
	rgba.red = red;
	rgba.green = green;
	rgba.blue = blue;
	rgba.alpha = alpha;
	return rgba;
}



