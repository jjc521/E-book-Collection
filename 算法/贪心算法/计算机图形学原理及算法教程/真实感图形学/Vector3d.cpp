// Vector3d.cpp: implementation of the CVector3d class.
#include "stdafx.h"
#include "Vector3d.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//缺省构造函数
CVector3d::CVector3d() : x(0.0f), y(0.0f), z(1.0f)
{}

//重载构造函数
CVector3d::CVector3d(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

CVector3d::CVector3d(const VECTOR3D& vector)
{
	x = vector.x;
	y = vector.y;
	z = vector.z;
}


CVector3d::~CVector3d()
{}

//////////////////////////////////////////////////////////////////////////////////////////////
//
//					  设置与获取  
//
//////////////////////////////////////////////////////////////////////////////////////////////

//设置, 由于具有"="重载功能, 所有设置函数只需要如下参数形式
void CVector3d::Set(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

//获取
VECTOR3D CVector3d::Get() const
{
	VECTOR3D vector;
	vector.x = x;
	vector.y = y;
	vector.z = z;
	return vector;
}


///////////////////////////   变换   ////////////////////////////////

//向量缩放
//用vector来缩放this向量
void CVector3d::Scale(CVector3d vector)
{
	x *= vector.x;
	y *= vector.y;
	z *= vector.z;
}

//向量缩放
//用vector来缩放this向量
void CVector3d::Scale(VECTOR3D vector)
{
	x *= vector.x;
	y *= vector.y;
	z *= vector.z;
}

//向量缩放
//用x, y, z来缩放this向量
void CVector3d::Scale(float x,  float y,  float z)
{
	this->x *=  x;
	this->y *=  y;
	this->z *=  z;
}

//将this向量进行旋转
//绕轴x旋转, fTheta为角度单位
void CVector3d::RotateX(float fTheta)
{
	//将角度转化为弧度
	float fRad = (float)((fTheta * PIE) / 180.0);	
	float yy = (float)(y * cos(fRad) - z * sin(fRad));
	float zz = (float)(y * sin(fRad) + z * cos(fRad));
	y = yy;
	z = zz;
}

//将this向量进行旋转
//绕轴y旋转, fTheta为角度单位
void CVector3d::RotateY(float fTheta)
{
	//将角度转化为弧度
	float fRad = (float)((fTheta * PIE) / 180.0);	
	float xx = (float)(x * cos(fRad) + z * sin(fRad));
	float zz = (float)(-x * sin(fRad) + z * cos(fRad));
	x = xx;
	z = zz;
}

//将this向量进行旋转
//绕轴y旋转, fTheta为角度单位
void CVector3d::RotateZ(float fTheta)
{
	//将角度转化为弧度
	float fRad = (float)((fTheta * PIE) / 180.0);	
	float xx = (float)(x * cos(fRad) - y * sin(fRad));
	float yy = (float)(x * sin(fRad) + y * cos(fRad));
	x = xx;
	y = yy;
}

//绕任意轴旋转, fTheta为角度, 
//必须指出, 这里的轴为一个自由向量, 自由向量都可以从坐标原点画出
void CVector3d::Rotate(float fTheta,  CVector3d axis)
{
	//单位化
	axis.Unitize();

	//旋转轴的方向数
	float fx = axis.x,  fy = axis.y,  fz = axis.z;
	
	//将角度转化为弧度
	float fRad = (float)((fTheta * PIE) / 180.0);

	//角度的正弦和余弦
	float c = (float)cos(fRad);
	float s = (float)sin(fRad);


	//多次变换的合成,参考相应的计算机图形学书籍,
	//变换的具体过程请参考:
	//<计算机图形学>(第三版),孙家广,清华大学出版社
	
	//下面是最后的结果
	float xx = (fx * fx * (1.0f - c) + c)      * x +
	           (fx * fy * (1.0f - c) - fz * s) * y +
	           (fx * fz * (1.0f - c) + fy * s) * z;

	float yy = (fy * fx * (1.0f - c) + fz * s) * x +
	           (fy * fy * (1.0f - c) + c)      * y +
               (fy * fz * (1.0f - c) - fx * s) * z;

	float zz = (fz * fx * (1.0f - c) - fy * s) * x + 
	           (fz * fy * (1.0f - c) + fx * s) * y +
	           (fz * fz * (1.0f - c) + c)      * z;

	//返回最后结果
	x = xx;
	y = yy;
	z = zz;
}

//绕任意轴旋转, fTheta为角度, 
//必须指出, 这里的轴为一个自由向量, 自由向量都可以从坐标原点画出
void CVector3d::Rotate(float fTheta,  VECTOR3D axis)
{
	CVector3d vector = axis;
	this->Rotate(fTheta, vector);
}

//(x, y, z)为旋转轴向量
void CVector3d::Rotate(float fTheta,  float x, float y, float z)
{
	CVector3d vector(x, y, z);
	this->Rotate(fTheta, vector);
}

//////////////////////////////////////////////////////////////////////////////////////////////
//
//					  计算小面法线
//
//////////////////////////////////////////////////////////////////////////////////////////////


//计算小面法线
VECTOR3D CVector3d::Noraml(const VERTEX3D& v1,  const VERTEX3D& v2,  const VERTEX3D& v3)
{
	//右手规则
	CVector3d vector1((v2.x - v1.x),  (v2.y - v1.y),  (v2.z - v1.z)); 
	CVector3d vector2((v3.x - v1.x),  (v3.y - v1.y),  (v3.z - v1.z)); 
	CVector3d noraml = vector1 * vector2;
	VECTOR3D n = {noraml.x,  noraml.y,  noraml.z};
	return n;
} 

//计算小面法线
VECTOR3D CVector3d::Noraml(const HOMOCOORD& v1,  const HOMOCOORD& v2,  const HOMOCOORD& v3)
{
	//如果一个三角形中包含无穷远点, 则该三角形是一个畸形三角形, 
	float w1 = v1.w,  w2 = v2.w,  w3 = v3.w;
	if(ABS(w1) <= 0.00001f) w1 = 1.0f;
	if(ABS(w2) <= 0.00001f) w2 = 1.0f;
	if(ABS(w3) <= 0.00001f) w3 = 1.0f;

	float x1 = v1.x / w1,  y1 = v1.y / w1,  z1 = v1.z / w1;
	float x2 = v2.x / w2,  y2 = v2.y / w2,  z2 = v2.z / w2;
	float x3 = v3.x / w3,  y3 = v3.y / w3,  z3 = v3.z / w3;

	CVector3d vector1((x2 - x1),  (y2 - y1),  (z2 - z1)); 
	CVector3d vector2((x3 - x1),  (y3 - y1),  (z3 - z1)); 
	CVector3d noraml = vector1 * vector2;
	VECTOR3D n = {noraml.x,  noraml.y,  noraml.z};
	return n;
}


