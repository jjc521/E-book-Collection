// Matrix3d.h: interface for the CMatrix3d class.

//三维变换矩阵(几何变换和观察变换)

#ifndef _CMATRIX3D_H
#define _CMATRIX3D_H
#include "Grphcs.h"

class CMatrix3d  
{
public:
	CMatrix3d();
	virtual ~CMatrix3d();

public:
	CMatrix3d operator = (const CMatrix3d& m);
	BOOL operator == (const CMatrix3d& m);

public:
	//获取与设置
	void Set(const float* pfMatrix);
	void Get(float* pfMatrix) const;

	//单位化
	void Identity();

	//平移
	void Translate(float x,float y, float z);

	//缩放变换
	//缩放参考点为原点
	void Scale(float fs);
	void Scale(float fsx,float fsy,float fsz);
	//缩放参考点为(x,y,z)
	void Scale(float fsx,float fsy,float fsz,float x,float y,float z);

	//绕 x 轴旋转
	void RotateX(float fTheta);
	void RotateX(float fTheta, float x, float y, float z);

	//绕 y 轴旋转
	void RotateY(float fTheta);
	void RotateY(float fTheta, float x, float y, float z);

	//绕 z 轴旋转
	void RotateZ(float fTheta);
	void RotateZ(float fTheta, float x, float y, float z);

	//绕任意过原点的轴(x,y,z)旋转(轴过原点)
	void Rotate(float fTheta, float x, float y, float z);
	
	//绕指定的轴旋转
	void Rotate(float fTheta, VECTOR3D axis,VERTEX3D ptOn);

	//相对 x 轴错切
	void SkewX(float fsy, float fsz);
	void SkewX(float fsy, float fsz, float x, float y, float z);

	//相对 y 轴错切
	void SkewY(float fsx, float fsz);
	void SkewY(float fsx, float fsz, float x, float y, float z);

	//相对 z 轴错切
	void SkewZ(float fsx, float fsy);
	void SkewZ(float fsx, float fsy, float x, float y, float z);

	//沿坐标平面作对称变换(即反射变换)
	void ReflexXOY();
	void ReflexYOZ();
	void ReflexZOX();

	//沿坐标轴和坐标原点反射
	void ReflexX();
	void ReflexY();
	void ReflexZ();
	void ReflexO();

	//执行变换(顶点)
	HOMOCOORD	Transform(float x, float y, float z, float w = 1.0f);
	HOMOCOORD	Transform(HOMOCOORD vertex);
	
	//变换法线,当前矩阵用作法线方位矩阵
	VECTOR3D Transform(VECTOR3D vector);


	//世界坐标到观察坐标的变换矩阵
	void Watch(float x, float y, float z);

	//矩阵乘法
	void Multiply(CMatrix3d m,DWORD dwMultiplier);
	
public:
	
	//矩阵系数(4行4列)
	//为了符合习惯,我们不采有匈牙利命名法
	float a[4][4];
	//排列如下:
	//
	//		a00,  a01,  a02,  a03
	//		a10,  a11,  a12,  a13
	//		a20,  a21,  a22,  a23
	//		a30,  a31,  a32,  a33
	
	//变换公式:
	//设P为变换前的点,P1为变换后的点,A为变换矩阵,则
	//    
	//		P1 = P * A
	
};

#endif 
