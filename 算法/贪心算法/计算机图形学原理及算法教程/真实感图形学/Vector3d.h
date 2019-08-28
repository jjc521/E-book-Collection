// Vector3d.h: interface for the CVector3d class.
//三维自由向量

#ifndef _CVECTOR3D_H
#define _CVECTOR3D_H
#include "Grphcs.h"
#include "math.h"

class CVector3d  
{
public:
	CVector3d();
	CVector3d(float x,float y,float z);
	CVector3d(const VECTOR3D& vector);
	virtual ~CVector3d();

public:
	//为了符合习惯,我们不采有匈牙利命名法
	float x,y,z;

public:
	//设置与获取函数
	void Set(float x,float y,float z);
	VECTOR3D Get() const;

public:
	//运算符重载(=)
	inline CVector3d operator = (const CVector3d& vector);
	inline CVector3d operator = (const VECTOR3D& vector);
	
	//运算符重载(+),返回另一个CVector3d
	inline CVector3d operator + (const CVector3d& vector);
	inline CVector3d operator + (const VECTOR3D& vector);		//交换律不成立(结构没有重载 "+")

	//运算符重载(+=)
	inline CVector3d operator += (const CVector3d& vector);
	inline CVector3d operator += (const VECTOR3D& vector);		

	//运算符重载(-),参数为减数,返回另一个CVector3d
	inline CVector3d operator - (const CVector3d& vector);
	inline CVector3d operator - (const VECTOR3D& vector);		
	
	//运算符重载(-),参数为减数
	inline CVector3d operator -= (const CVector3d& vector);
	inline CVector3d operator -= (const VECTOR3D& vector);		

	//运算符重载(*),参数为乘数,返回另一个CVector3d
	//向量叉积
	inline CVector3d operator * (const CVector3d& vector);
	inline CVector3d operator * (const VECTOR3D& vector);		
	//标量与向量积
	inline CVector3d operator * (float fs);

	//运算符重载(*),参数为乘数,返回另一个CVector3d
	//向量叉积
	inline CVector3d operator *= (const CVector3d& vector);
	inline CVector3d operator *= (const VECTOR3D& vector);		
	//标量与向量积
	inline CVector3d operator *= (float fs);

	//对于"/"运算符,没有必要重载

public:
	//向量点积
	inline float Dot(const CVector3d& vector);
	inline float Dot(const VECTOR3D& vector);
	inline float Dot(float x,float y, float z);

	//向量的模
	inline float Mag();
	inline float MagSquared();

	//向量矢径端点之间的距离
	inline float Dist(const CVector3d& vector);
	inline float Dist(const VECTOR3D& vector);
	inline float Dist(float x,float y,float z);

	//向量单位化
	inline CVector3d Unit();
	inline void Unitize();
	
public:

	//将this向量缩放
	void Scale(CVector3d vector);
	void Scale(VECTOR3D vector);
	void Scale(float x, float y, float z);

	//将this向量绕三轴旋转,fTheta为角度单位
	void RotateX(float fTheta);
	void RotateY(float fTheta);
	void RotateZ(float fTheta);

	//将this向量绕任意轴旋转,fTheta为角度单位
	void Rotate(float fTheta, CVector3d axis);
	void Rotate(float fTheta, VECTOR3D axis);
	//(x,y,z)为旋转轴向量
	void Rotate(float fTheta, float x, float y, float z);

	//计算小面法线
	VECTOR3D Noraml(const VERTEX3D& v1, const VERTEX3D& v2, const VERTEX3D& v3);
	VECTOR3D Noraml(const HOMOCOORD& v1, const HOMOCOORD& v2, const HOMOCOORD& v3);

};
#endif 

//////////////////////////////////////////////////////////////////////////////////////////////
//
//					  运算符重载  
//
//////////////////////////////////////////////////////////////////////////////////////////////

//运算符重载(=)
//参数为CVector3d对象
inline CVector3d CVector3d::operator = (const CVector3d& vector)
{
	x = vector.x;
	y = vector.y;
	z = vector.z;
	return *this;
}

//运算符重载(=)
//参数为VECTOR3D结构
inline CVector3d CVector3d::operator = (const VECTOR3D& vector)
{
	x = vector.x;
	y = vector.y;
	z = vector.z;
	return *this;
}

//运算符重载(+)
//参数为CVector3d对象,返回另一个CVector3d对象
inline CVector3d CVector3d::operator + (const CVector3d& vector)
{
	CVector3d v;
	v.x = x + vector.x;
	v.y = y + vector.y;
	v.z = z + vector.z;
	return v;
}


//运算符重载(+)
//参数为VECTOR3D结构,返回另一个CVector3d对象
inline CVector3d CVector3d::operator + (const VECTOR3D& vector)
{
	CVector3d v;
	v.x = x + vector.x;
	v.y = y + vector.y;
	v.z = z + vector.z;
	return v;
}


//运算符重载(+=)
//参数为CVector3d对象
inline CVector3d CVector3d::operator += (const CVector3d& vector)
{
	x += vector.x;
	y += vector.y;
	z += vector.z;
	return *this;
}

//运算符重载(+=)
//参数为VECTOR3D结构
inline CVector3d CVector3d::operator += (const VECTOR3D& vector)
{
	x += vector.x;
	y += vector.y;
	z += vector.z;
	return *this;
}

//运算符重载(-)
//参数为CVector3d对象,为减数,返回另一个CVector3d对象
inline CVector3d CVector3d::operator - (const CVector3d& vector)
{
	CVector3d v;
	v.x = x - vector.x;
	v.y = y - vector.y;
	v.z = z - vector.z;
	return v;
}

//运算符重载(-)
//参数为VECTOR3D结构,为减数,返回另一个CVector3d对象
inline CVector3d CVector3d::operator - (const VECTOR3D& vector)
{
	CVector3d v;
	v.x = x - vector.x;
	v.y = y - vector.y;
	v.z = z - vector.z;
	return v;
}

//运算符重载(-=)
//参数为CVector3d对象,为减数
inline CVector3d CVector3d::operator -= (const CVector3d& vector)
{
	x -= vector.x;
	y -= vector.y;
	z -= vector.z;
	return *this;
}

//运算符重载(-=)
//参数为VECTOR3D结构,为减数
inline CVector3d CVector3d::operator -= (const VECTOR3D& vector)
{
	x -= vector.x;
	y -= vector.y;
	z -= vector.z;
	return *this;
}

//运算符重载(*),作向量叉积
//参数为CVector3d对象,为乘数,返回另一个CVector3d对象
inline CVector3d CVector3d::operator * (const CVector3d& vector)
{
	CVector3d v;
	v.x = (y * vector.z - z * vector.y);
	v.y = (z * vector.x - x * vector.z);
	v.z = (x * vector.y - y * vector.x);
	return v;
}

//运算符重载(*),作向量叉积
//参数为VECTOR3D结构,为乘数,返回另一个CVector3d对象
inline CVector3d CVector3d::operator * (const VECTOR3D& vector)
{
	CVector3d v;
	v.x = (y * vector.z - z * vector.y);
	v.y = (z * vector.x - x * vector.z);
	v.z = (x * vector.y - y * vector.x);
	return v;
}

//运算符重载(*),标量与向量之积
//参数为浮点标量,返回另一个CVector3d对象
inline CVector3d CVector3d::operator * (float fs)
{
	CVector3d v;
	v.x = x * fs;
	v.y = y * fs;
	v.z = z * fs;
	return v;
}

//运算符重载(*=),作向量叉积
//参数为CVector3d对象,为乘数,
inline CVector3d CVector3d::operator *= (const CVector3d& vector)
{
	float xx = (y * vector.z - z * vector.y);
	float yy = (z * vector.x - x * vector.z);
	float zz = (x * vector.y - y * vector.x);
	x = xx;
	y = yy;
	z = zz;
	return *this;
}

//运算符重载(*=),作向量叉积
//参数为VECTOR3D结构,为乘数
inline CVector3d CVector3d::operator *= (const VECTOR3D& vector)
{
	float xx = (y * vector.z - z * vector.y);
	float yy = (z * vector.x - x * vector.z);
	float zz = (x * vector.y - y * vector.x);
	x = xx;
	y = yy;
	z = zz;
	return *this;
}

//运算符重载(*),标量与向量之积
//参数为浮点标量
inline CVector3d CVector3d::operator *= (float fs)
{
	x *= fs;
	y *= fs;
	z *= fs;
	return *this;
}

//////////////////////////////////////////////////////////////////////////////////////////////
//
//					  其它基本运算  
//
//////////////////////////////////////////////////////////////////////////////////////////////

//向量内积
inline float CVector3d::Dot(const CVector3d& vector)
{
	return (x * vector.x + y * vector.y + z * vector.z);
}

//向量内积
inline float CVector3d::Dot(const VECTOR3D& vector)
{
	return (x * vector.x + y * vector.y + z * vector.z);
}

//向量内积
inline float CVector3d::Dot(float x,float y, float z)
{
	return (this->x * x + this->y * y + this->z * z);
}

//向量的模
inline float CVector3d::Mag()
{
	return (float)(sqrt(x * x + y * y + z * z));
}

//向量模的平方
inline float CVector3d::MagSquared()
{
	return (x * x + y * y + z * z);
}

//两向量矢量端点之间的距离
inline float CVector3d::Dist(const CVector3d& vector)
{
	return (*this - vector).Mag();
}

//两向量矢量端点之间的距离
inline float CVector3d::Dist(const VECTOR3D& vector)
{
	return (*this - vector).Mag();
}

//两向量矢量端点之间的距离
inline float CVector3d::Dist(float x,float y,float z)
{
	return (float)sqrt((this->x - x) * (this->x - x) + (this->y - y) * (this->y - y) + (this->z - z) * (this->z - z)); 
}

//向量单位化
//向量单位化,返回一个单位向量
inline CVector3d CVector3d::Unit()
{
	CVector3d vector;
	float fMag = (float)sqrt(x * x + y * y + z * z);
	if(fMag < 0.0001f)fMag = 1.0f;
	vector.x = x / fMag;
	vector.y = y / fMag;
	vector.z = z / fMag;
	return vector;
}

//自身单位化
inline void CVector3d::Unitize()
{
	float fMag = (float)sqrt(x * x + y * y + z * z);
	if(fMag < 0.0001f)fMag = 1.0f;
	x /= fMag;
	y /= fMag;
	z /= fMag;
}


