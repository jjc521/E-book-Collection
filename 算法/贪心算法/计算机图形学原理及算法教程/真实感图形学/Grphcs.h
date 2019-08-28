//								Grphcs.h    
//该头文件定义图像处理宏:

#ifndef __grphcs_h_
#ifndef __GRPHCS_H__

#define __grphcs_h_
#define __GRPHCS_H__

#ifdef __cplusplus
extern "C" {
#endif

#define		PIE		3.14159265358979323846
#define		GRAPHICS_DESIGN_VERSION_1_0			1

//工业颜色模型


#define		G3D_PIXEL_COLOR_RGB						0X00000000
#define		G3D_PIXEL_COLOR_RGBA					0X00000001
#define		G3D_PIXEL_COLOR_INDEX					0X00000002

//直线与三角形填充区域的位置关系,注意我们只区分左右关系,不区分上下关系
//适用于扫描填充
#define		G3D_TRIANGLE_ON_LINE_RIGHT				0X00000100
#define		G3D_TRIANGLE_ON_LINE_LEFT				0X00000101

//矩阵乘法由于不满足交换律,所以在此定义左乘或右乘操作
#define		G3D_MATRIX_MULTIPLIER_PRECONCAT			0X00000200
#define		G3D_MATRIX_MULTIPLIER_POSTCONCAT		0X00000201


//物体着色模型
#define		G3D_RENDER_VERTICES						0X00000300
#define		G3D_RENDER_WIRE							0X00000301
#define		G3D_RENDER_WIRE_LIGHTED					0X00000302
#define		G3D_RENDER_FLAT							0X00000303
#define		G3D_RENDER_GOURAUD_SMOOTH				0X00000304


//材质和光源的基本属性:
#define		G3D_AMBIENT								0X00000400
#define		G3D_DIFFUSE								0X00000401
#define		G3D_SPECULAR							0X00000402

//光的位置
#define		G3D_POSITION							0X00000403

//聚光属性
#define		G3D_SPOT_DIRECTION						0X00000404
#define		G3D_SPOT_CUTOFF							0X00000405
#define		G3D_SPOT_EXPONENT						0X00000406

//光的衰减因子
#define		G3D_CONSTANT_ATTENUATION				0X00000407
#define		G3D_LINEAR_ATTENUATION					0X00000408
#define		G3D_QUADRATIC_ATTENUATION				0X00000409
#define		G3D_LIGHT_ON_OFF						0X0000040A

//材质专用
#define     G3D_AMBIENT_AND_DIFFUSE					0X00000501
#define     G3D_EMISSION							0X00000502
#define     G3D_SHININESS							0X00000503


//光照模型
//全局环境光
#define		G3D_LIGHT_MODEL_AMBIENT					0X00000600
//近视点与无穷远视点
#define     G3D_LIGHT_MODEL_LOCAL_VIEWER			0X00000601
//双面光照
#define		G3D_LIGHT_MODEL_TWO_SIDE				0X00000602

//指定面是前面、后面，还是双面
#define		G3D_FRONT								0X00000700	
#define		G3D_BACK								0X00000701
#define		G3D_FRONT_AND_BACK						0X00000702

//深度测试条件
#define		G3D_LESS								0X00000800
#define		G3D_LEQUAL								0X00000801
#define		G3D_EQUAL								0X00000802
#define		G3D_GEQUAL								0X00000803
#define		G3D_GREATER								0X00000804
#define		G3D_NOTEQUAL							0X00000805
#define		G3D_NEVER								0X00000806
#define		G3D_ALWAYS								0X00000807





////////////////////////////////////////////////////////////////////////////////

//*******************		结构定义       *********************

////////////////////////////////////////////////////////////////////////////////

//浮点颜色:RGB
typedef struct tagFLOATCOLORRGB
{
	float red;
	float green;
	float blue;
}FLOATCOLORRGB;

//浮点颜色:RGBA
typedef struct tagFLOATCOLORRGBA
{
	float red;
	float green;
	float blue;
	float alpha;
}FLOATCOLORRGBA;


//三维自由向量
typedef struct tagVECTOR3D
{
	float x;
	float y;
	float z;
}VECTOR3D;

//三维顶点坐标
typedef struct tagVERTEX3D
{
	float x;
	float y;
	float z;
}VERTEX3D;


//齐次坐标(Homogeneous Coordinate)
typedef struct tagHOMOCOORD
{
	float x;
	float y;
	float z;
	float w;
}HOMOCOORD;


//简单的透视投影,不作规格化设备坐标变换,不作观察剪切

//简单取景器(基于观察坐标)
typedef struct tagVIEWFINDER
{
	float     fDistView;		//	视距,视点到投影屏幕之间的距离
	float	  xScale;			//	进行视口变换时,宽度缩放比例
	float     yScale;			//	进行视口变换时,高度缩放比例
	POINT	  ptCenter;			//	视心,世界坐标系坐标原点投影到屏幕上的位置
}VIEWFINDER;


//截断函数
#define BOUND(x,a,b) (((x) < (a)) ? (a) : (((x) > (b)) ? (b) : (x)))

//绝对值函数
#define ABS(x)	(((x) < 0) ? -(x) : (((x) > 0) ? (x) : 0))

#define MAX(a,b)	(((a) > (b)) ? (a) : (b))
#define MIN(a,b)	(((a) < (b)) ? (a) : (b)) 

#ifdef __cplusplus
}
#endif

#endif /* __GRPHCS_H__ */
#endif /* __grphcs_h_ */