/////////////////////////////////////////////////////////////////////////////////
//	
// Matrix3d.cpp: implementation of the CMatrix3d class.
//

#include "stdafx.h"
#include "Matrix3d.h"
#include "math.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMatrix3d::CMatrix3d()
{
	Identity();
}

CMatrix3d::~CMatrix3d()
{}

//单位矩阵
void CMatrix3d::Identity()
{
	a[0][0] = 1.0f;	a[0][1] = 0.0f; a[0][2] = 0.0f;  a[0][3] = 0.0f;
	a[1][0] = 0.0f;	a[1][1] = 1.0f; a[1][2] = 0.0f;  a[1][3] = 0.0f;
	a[2][0] = 0.0f;	a[2][1] = 0.0f; a[2][2] = 1.0f;  a[2][3] = 0.0f;
	a[3][0] = 0.0f;	a[3][1] = 0.0f; a[3][2] = 0.0f;  a[3][3] = 1.0f;
}

//////////////////////////////////////////////////////////////////////////////////////////////
//
//					  运算符重载  
//
//////////////////////////////////////////////////////////////////////////////////////////////

//重载"="运算符(置换)
CMatrix3d CMatrix3d::operator = (const CMatrix3d& m)
{
	for(int i = 0; i < 4; i++)
	for(int j = 0; j < 4; j++)
		a[i][j] = m.a[i][j];
	return *this;
}

//重载"=="运算符
BOOL CMatrix3d::operator == (const CMatrix3d& m)
{
	for(int i = 0; i < 4; i++)
	for(int j = 0; j < 4; j++)
		if(ABS(a[i][j] - m.a[i][j]) > 0.0001f)
			return FALSE;
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////////////////////////
//
//					  设置与获取 
//
//////////////////////////////////////////////////////////////////////////////////////////////

//设置变换矩阵(置换)
void CMatrix3d::Set(const float* pfMatrix)
{
	for(int i = 0;i < 4;i++)
	for(int j = 0;j < 4;j++)
		a[i][j] = pfMatrix[ (4 * i + j) ];
}

//获取变换矩阵
void CMatrix3d::Get(float* pfMatrix) const
{
	ASSERT(pfMatrix);
	for(int i = 0;i < 4;i++)
	for(int j = 0;j < 4;j++)
		pfMatrix[ (4 * i + j) ]	 = a[i][j];
}

//////////////////////////////////////////////////////////////////////////////////////////////
//
//				  计算机图形学几何线性变换
//
//////////////////////////////////////////////////////////////////////////////////////////////

//齐次坐标变换矩阵

//平移变换, 平移量(x, y, z)
void CMatrix3d::Translate(float x, float y,  float z)
{
	a[3][0] += x;
	a[3][1] += y;
	a[3][2] += z;
}

//缩放变换
//fsx, fsy, fsz----为缩放因子
//在应用时, 要特别注意, 它只改变主对角线上的元素
//因而, 多用于第一次变换
void CMatrix3d::Scale(float fs)
{
	a[0][0] *= fs;
	a[1][1] *= fs;
	a[2][2] *= fs;
}

//缩放变换
//fsx, fsy, fsz----为缩放因子
//在应用时, 要特别注意, 它只改变主对角线上的元素
//因而, 多用于第一次变换
void CMatrix3d::Scale(float fsx, float fsy, float fsz)
{
	a[0][0] *= fsx;
	a[1][1] *= fsy;
	a[2][2] *= fsz;
}

//缩放变换
//fsx, fsy, fsz----为缩放因子
//x, y, z为缩放变换的参考点, 缺省设置为世界坐标系的坐标原点
void CMatrix3d::Scale(float fsx, float fsy, float fsz, float x, float y, float z)
{
	CMatrix3d m;
	m.a[0][0] = fsx;
	m.a[1][1] = fsy;
	m.a[2][2] = fsz;
	m.a[3][0] = (1- fsx) * x;
	m.a[3][1] = (1- fsy) * y;
	m.a[3][2] = (1- fsz) * z;
	
	//矩阵右乘
	this->Multiply(m, G3D_MATRIX_MULTIPLIER_POSTCONCAT);
}

//绕 x 轴旋转
//fTheta为角度单位, 参考点为坐标原点
void CMatrix3d::RotateX(float fTheta)
{
	//将角度转化为弧度
	float fRad = (float)((fTheta * PIE) / 180.0);
	CMatrix3d m;
	m.a[1][1] = (float)cos(fRad);
	m.a[1][2] = (float)sin(fRad);
	m.a[2][1] = -m.a[1][2];
	m.a[2][2] = m.a[1][1];
	//矩阵右乘
	this->Multiply(m, G3D_MATRIX_MULTIPLIER_POSTCONCAT);
}

//绕 x 轴旋转
//fTheta为角度单位, 参考点为坐标(x, y, z)
void CMatrix3d::RotateX(float fTheta,  float x,  float y,  float z)
{
	//矩阵乘法满足结合律
	this->Translate(-x,  -y,  -z);
	this->RotateX(fTheta);
	this->Translate(x,  y,  z);
}

//绕 y 轴旋转
//fTheta为角度单位, 参考点为坐标原点
void CMatrix3d::RotateY(float fTheta)
{
	//将角度转化为弧度
	float fRad = (float)((fTheta * PIE) / 180.0);
	CMatrix3d m;
	m.a[0][0] = (float)cos(fRad);
	m.a[2][0] = (float)sin(fRad);
	m.a[0][2] = -m.a[2][0];
	m.a[2][2] = m.a[0][0];
	//矩阵右乘
	this->Multiply(m, G3D_MATRIX_MULTIPLIER_POSTCONCAT);
}

//绕 y 轴旋转
//fTheta为角度单位, 参考点为坐标(x, y, z)
void CMatrix3d::RotateY(float fTheta,  float x,  float y,  float z)
{
	this->Translate(-x,  -y,  -z);
	this->RotateY(fTheta);
	this->Translate(x,  y,  z);
}

//绕 z 轴旋转
//fTheta为角度单位, 参考点为坐标原点
void CMatrix3d::RotateZ(float fTheta)
{
	//将角度转化为弧度
	float fRad = (float)((fTheta * PIE) / 180.0);
	CMatrix3d m;
	m.a[0][0] = (float)cos(fRad);
	m.a[0][1] = (float)sin(fRad);
	m.a[1][0] = -m.a[0][1];
	m.a[1][1] = m.a[0][0];
	//矩阵右乘
	this->Multiply(m, G3D_MATRIX_MULTIPLIER_POSTCONCAT);
}

//绕 z 轴旋转
//fTheta为角度单位, 参考点为坐标(x, y, z)
void CMatrix3d::RotateZ(float fTheta,  float x,  float y,  float z)
{
	this->Translate(-x,  -y,  -z);
	this->RotateZ(fTheta);
	this->Translate(x,  y,  z);
}

//绕任意轴(x, y, z)旋转角度fTheta, 轴过坐标原点
void CMatrix3d::Rotate(float fTheta,  float x,  float y,  float z)
{
	//将轴单位化
	float fMag = (float)sqrt(x * x + y * y + z * z);
	if(fMag < 0.0001f)
	{
		//轴变成坐标原点, 返回, 该次变换不对物体的几何位置产生影响
		return;
	}
	
	//旋转轴的方向数,单位向量
	float fx = (x / fMag),  fy = (y / fMag),  fz = (z / fMag);

	//将角度转化为弧度
	float fRad = (float)((fTheta * PIE) / 180.0);


	//角度的正弦和余弦
	float c = (float)cos(fRad);
	float s = (float)sin(fRad);

	//变换矩阵m
	CMatrix3d m;

	//多次变换的合成,参考相应的计算机图形学书籍
	m.a[0][0] = fx * fx * (1.0f - c) + c;
	m.a[0][1] = fx * fy * (1.0f - c) - fz * s;
	m.a[0][2] = fx * fz * (1.0f - c) + fy * s;

	m.a[1][0] = fy * fx * (1.0f - c) + fz * s;
	m.a[1][1] = fy * fy * (1.0f - c) + c;
	m.a[1][2] = fy * fz * (1.0f - c) - fx * s;

	m.a[2][0] = fz * fx * (1.0f - c) - fy * s;
	m.a[2][1] = fz * fy * (1.0f - c) + fx * s;
	m.a[2][2] = fz * fz * (1.0f - c) + c;

	
	//与原有变换进行合成
	this->Multiply(m, G3D_MATRIX_MULTIPLIER_POSTCONCAT);
}

//旋转, 轴由方向axis和点ptOn定义
void CMatrix3d::Rotate(float fTheta,  VECTOR3D axis, VERTEX3D ptOn)
{
	this->Translate(-ptOn.x,  -ptOn.y,  -ptOn.z);
	this->Rotate(fTheta,  axis.x,  axis.y,  axis.z);
	this->Translate(ptOn.x,  ptOn.y,  ptOn.z);
}

//相对 x 轴错切, 相对点为坐标原点
//使用公式: x1 = x0 , y1 = y0 + a * x0,  z1 = z0 + b * x0
void CMatrix3d::SkewX(float fsy,  float fsz)
{
	CMatrix3d m;
	m.a[0][1] = fsy; m.a[0][2] = fsz;
	this->Multiply(m, G3D_MATRIX_MULTIPLIER_POSTCONCAT);
}

//相对 x 轴错切, 相对点为(x, y, z)
void CMatrix3d::SkewX(float fsy,  float fsz,  float x,  float y,  float z)
{
	this->Translate(-x,  -y,  -z);
	this->SkewX(fsy, fsz);
	this->Translate(x,  y,  z);
}

//相对 y 轴错切, 相对点为坐标原点
//使用公式: x1 = x0 + a * y0,  y1 = y0,  z1 = z0 + b * y0
void CMatrix3d::SkewY(float fsx,  float fsz)
{
	CMatrix3d m;
	m.a[1][0] = fsx; m.a[1][2] = fsz;
	this->Multiply(m, G3D_MATRIX_MULTIPLIER_POSTCONCAT);
}

//相对 y 轴错切, 相对点为(x, y, z)
void CMatrix3d::SkewY(float fsx,  float fsz,  float x,  float y,  float z)
{
	this->Translate(-x,  -y,  -z);
	this->SkewY(fsx, fsz);
	this->Translate(x,  y,  z);
}

//相对 z 轴错切, 相对点为坐标原点
//使用公式: x1 = x0 + a * z0,  y1 = y0 + b * z0,  z1 = z0
void CMatrix3d::SkewZ(float fsx,  float fsy)
{
	CMatrix3d m;
	m.a[2][0] = fsx; m.a[2][1] = fsy;
	this->Multiply(m, G3D_MATRIX_MULTIPLIER_POSTCONCAT);
}

//相对 z 轴错切, 相对点为(x, y, z)
void CMatrix3d::SkewZ(float fsx,  float fsy,  float x,  float y,  float z)
{
	this->Translate(-x,  -y,  -z);
	this->SkewZ(fsx, fsy);
	this->Translate(x,  y,  z);
}

//沿xoy平面作对称变换(即反射变换)
void CMatrix3d::ReflexXOY()
{
	a[0][2] = -a[0][2];
	a[1][2] = -a[1][2];
	a[2][2] = -a[2][2];
	a[3][2] = -a[3][2];
}

//沿yoz平面作对称变换(即反射变换)
void CMatrix3d::ReflexYOZ()
{
	a[0][0] = -a[0][0];
	a[1][0] = -a[1][0];
	a[2][0] = -a[2][0];
	a[3][0] = -a[3][0];
}

//沿zox平面作对称变换(即反射变换)
void CMatrix3d::ReflexZOX()
{
	a[0][1] = -a[0][1];
	a[1][1] = -a[1][1];
	a[2][1] = -a[2][1];
	a[3][1] = -a[3][1];
}

//沿 x 轴反射
void CMatrix3d::ReflexX()
{
	//第二列
	a[0][1] = -a[0][1];		a[1][1] = -a[1][1];
	a[2][1] = -a[2][1];		a[3][1] = -a[3][1];

	//第三列
	a[0][2] = -a[0][2];		a[1][2] = -a[1][2];
	a[2][2] = -a[2][2];		a[3][2] = -a[3][2];
}

//沿 y 轴反射
void CMatrix3d::ReflexY()
{
	//第一列
	a[0][0] = -a[0][0];		a[1][0] = -a[1][0];
	a[2][0] = -a[2][0];		a[3][0] = -a[3][0];

	//第三列
	a[0][2] = -a[0][2];		a[1][2] = -a[1][2];
	a[2][2] = -a[2][2];		a[3][2] = -a[3][2];
}

//沿 z 轴反射
void CMatrix3d::ReflexZ()
{
	//第一列
	a[0][0] = -a[0][0];		a[1][0] = -a[1][0];
	a[2][0] = -a[2][0];		a[3][0] = -a[3][0];

	//第二列
	a[0][1] = -a[0][1];		a[1][1] = -a[1][1];
	a[2][1] = -a[2][1];		a[3][1] = -a[3][1];
}

//沿原点反射
void CMatrix3d::ReflexO()
{
	//第一列
	a[0][0] = -a[0][0];		a[1][0] = -a[1][0];
	a[2][0] = -a[2][0];		a[3][0] = -a[3][0];

	//第二列
	a[0][1] = -a[0][1];		a[1][1] = -a[1][1];
	a[2][1] = -a[2][1];		a[3][1] = -a[3][1];

	//第三列
	a[0][2] = -a[0][2];		a[1][2] = -a[1][2];
	a[2][2] = -a[2][2];		a[3][2] = -a[3][2];
}


//////////////////////////////////////////////////////////////////////////////////////////////
//
//					  执行变换
//
//////////////////////////////////////////////////////////////////////////////////////////////

//执行变换, 参数为三维顶点:齐次坐标
//必须指出, 当对一个 w = 1.0f 的真实点进行变换时, 它将有可以转化为 w != 1.0f 的点.
//在应用的时候, 这一点必须要清楚.
//幸运的是, 我们大部分时间是在几何变换中处理Transform()函数, 
//并且, 这些点的齐次坐标均表示为 (z, y, z, 1.0f).
HOMOCOORD CMatrix3d::Transform(float x,  float y,  float z,  float w)
{

	//几何顶点
	HOMOCOORD hc;
	hc.x = x * a[0][0] + y * a[1][0] + z * a[2][0] + w * a[3][0];
	hc.y = x * a[0][1] + y * a[1][1] + z * a[2][1] + w * a[3][1];
	hc.z = x * a[0][2] + y * a[1][2] + z * a[2][2] + w * a[3][2];
	hc.w = x * a[0][3] + y * a[1][3] + z * a[2][3] + w * a[3][3];
	return hc;
}

//执行变换, 参数为三维顶点 HOMOCOORD
HOMOCOORD CMatrix3d::Transform(HOMOCOORD vertex)
{
	//几何顶点
	HOMOCOORD hc;
	hc.x = vertex.x * a[0][0] + vertex.y * a[1][0] + vertex.z * a[2][0] + vertex.w * a[3][0];
	hc.y = vertex.x * a[0][1] + vertex.y * a[1][1] + vertex.z * a[2][1] + vertex.w * a[3][1];
	hc.z = vertex.x * a[0][2] + vertex.y * a[1][2] + vertex.z * a[2][2] + vertex.w * a[3][2];
	hc.w = vertex.x * a[0][3] + vertex.y * a[1][3] + vertex.z * a[2][3] + vertex.w * a[3][3];
	return hc;
}

//变换法线, 当前矩阵用作法线方位矩阵
VECTOR3D CMatrix3d::Transform(VECTOR3D vector)
{
	//法线
	VECTOR3D v;
	v.x = vector.x * a[0][0] + vector.y * a[1][0] + vector.z * a[2][0];
	v.y = vector.x * a[0][1] + vector.y * a[1][1] + vector.z * a[2][1];
	v.z = vector.x * a[0][2] + vector.y * a[1][2] + vector.z * a[2][2];
	return v;
}



//////////////////////////////////////////////////////////////////////////////////////////////
//
//					世界坐标到观察坐标的变换矩阵
//
//////////////////////////////////////////////////////////////////////////////////////////////

//(x, y, z)为世界坐标系下定义的视点
//观察中心为坐标原点,上向量为(0,1,0)
void CMatrix3d::Watch(float x,  float y,  float z)
{
	//坐标系的变换过程分如下五步:
	//第一, 将用户坐标系平移至视点;
	//第二, 将平移后的新坐标系绕 X' 轴旋转90度;
	//第三, 再将新坐标系绕 Y' 轴旋转角度 theta . sin(theta) = -x / sqrt( x * x + y * y); 
	//第四, 再将新坐标系绕 X' 轴旋转角度 alpha . sin(alpha) = c / mag(a, b, c)
	//第五, 将右手坐标系变为左手坐标系, Z 轴反向


	//计算两个关键量
	float fv = (float)sqrt(x * x + y * y);
	float fu = (float)sqrt(x * x + y * y + z * z);
	
	//视点自动向后移动两个单位(退至缺省坐标系统之外);
	if(fu < 0.00001)fu = 2.0f;


	//观察变换在几何变换完成之后进行
	//观察变换矩阵, 我们直接写出观察变换的结果, 这样可减少运算
	CMatrix3d mv;

	//如果视点位于 z 轴上
	if(fv <= 0.00001f)
	{

		//此时, 投影平面平行于 xoy 平面, 投影方向为沿 z 轴正向指向负向(世界坐标系)
		mv.a[2][2] = -1;
		mv.a[3][2] = fu;

		//评论:
		//这样处理与下面的次将要处理的情况是不连续的
		//这种情况就是(fv > 0.00001f)

		/*
		mv.a[0][0] = -1.0f;   mv.a[0][1] = 0.0;       mv.a[0][2] = -x / fu;
		mv.a[1][0] = 0.0f;    mv.a[1][1] = -1.0f;     mv.a[1][2] = -y / fu;
		mv.a[2][1] = fv / fu; mv.a[2][2] = -z / fu;
		mv.a[3][2] = fu;
		*/
	}
	else
	{
		//处理一般情形
		mv.a[0][0] = -y / fv; mv.a[0][1] = -(x * z) / (fu * fv); mv.a[0][2] = -x / fu;
		mv.a[1][0] = x / fv;  mv.a[1][1] = -(y * z) / (fu * fv); mv.a[1][2] = -y / fu;
		mv.a[2][1] = fv / fu; mv.a[2][2] = -z / fu;
		mv.a[3][2] = fu;

		//评论:
		//这是一般情况下的透视变换, 该变换可能会引起位置发生改变, 
		//比如, 一根立着的柱子, 可能会被放倒.
	}

	//评论:

	//在编程方法上,我们采用了矩阵累积乘法法则.
	//我们分两种情况进行了讨论,
	//事实上,也可以采用一个变换矩阵,请读者自己完成。

	this->Multiply(mv, G3D_MATRIX_MULTIPLIER_POSTCONCAT);
}


//////////////////////////////////////////////////////////////////////////////////////////////
//
//					  矩阵乘法
//
//////////////////////////////////////////////////////////////////////////////////////////////

//矩阵乘法
void CMatrix3d::Multiply(CMatrix3d m, DWORD dwMultiplier)
{
	//A * B
	CMatrix3d A, B;
	
	if(dwMultiplier == G3D_MATRIX_MULTIPLIER_PRECONCAT)
	{
		A = m;
		B = *this;
	}
	else if(dwMultiplier == G3D_MATRIX_MULTIPLIER_POSTCONCAT)
	{
		A = *this;
		B = m;
	}


	//展开计算, 不用循环, 以减少加法运算次数
	a[0][0] = A.a[0][0] * B.a[0][0] + A.a[0][1] * B.a[1][0] + A.a[0][2] * B.a[2][0] + A.a[0][3] * B.a[3][0];
	a[0][1] = A.a[0][0] * B.a[0][1] + A.a[0][1] * B.a[1][1] + A.a[0][2] * B.a[2][1] + A.a[0][3] * B.a[3][1];
	a[0][2] = A.a[0][0] * B.a[0][2] + A.a[0][1] * B.a[1][2] + A.a[0][2] * B.a[2][2] + A.a[0][3] * B.a[3][2];
	a[0][3] = A.a[0][0] * B.a[0][3] + A.a[0][1] * B.a[1][3] + A.a[0][2] * B.a[2][3] + A.a[0][3] * B.a[3][3];

	a[1][0] = A.a[1][0] * B.a[0][0] + A.a[1][1] * B.a[1][0] + A.a[1][2] * B.a[2][0] + A.a[1][3] * B.a[3][0];
	a[1][1] = A.a[1][0] * B.a[0][1] + A.a[1][1] * B.a[1][1] + A.a[1][2] * B.a[2][1] + A.a[1][3] * B.a[3][1];
	a[1][2] = A.a[1][0] * B.a[0][2] + A.a[1][1] * B.a[1][2] + A.a[1][2] * B.a[2][2] + A.a[1][3] * B.a[3][2];
	a[1][3] = A.a[1][0] * B.a[0][3] + A.a[1][1] * B.a[1][3] + A.a[1][2] * B.a[2][3] + A.a[1][3] * B.a[3][3];

	a[2][0] = A.a[2][0] * B.a[0][0] + A.a[2][1] * B.a[1][0] + A.a[2][2] * B.a[2][0] + A.a[2][3] * B.a[3][0];
	a[2][1] = A.a[2][0] * B.a[0][1] + A.a[2][1] * B.a[1][1] + A.a[2][2] * B.a[2][1] + A.a[2][3] * B.a[3][1];
	a[2][2] = A.a[2][0] * B.a[0][2] + A.a[2][1] * B.a[1][2] + A.a[2][2] * B.a[2][2] + A.a[2][3] * B.a[3][2];
	a[2][3] = A.a[2][0] * B.a[0][3] + A.a[2][1] * B.a[1][3] + A.a[2][2] * B.a[2][3] + A.a[2][3] * B.a[3][3];

	a[3][0] = A.a[3][0] * B.a[0][0] + A.a[3][1] * B.a[1][0] + A.a[3][2] * B.a[2][0] + A.a[3][3] * B.a[3][0];
	a[3][1] = A.a[3][0] * B.a[0][1] + A.a[3][1] * B.a[1][1] + A.a[3][2] * B.a[2][1] + A.a[3][3] * B.a[3][1];
	a[3][2] = A.a[3][0] * B.a[0][2] + A.a[3][1] * B.a[1][2] + A.a[3][2] * B.a[2][2] + A.a[3][3] * B.a[3][2];
	a[3][3] = A.a[3][0] * B.a[0][3] + A.a[3][1] * B.a[1][3] + A.a[3][2] * B.a[2][3] + A.a[3][3] * B.a[3][3];

	/*
	//用循环缩写
	for(int i = 0; i < 4; i++)
	for(int j = 0; j < 4; j++)
	{
		a[i][j] = 0.0f;
		for(int k = 0; k < 4; k++)
			a[i][j] += (A.a[i][k] * B.a[k][j]);
	}
	*/
}


