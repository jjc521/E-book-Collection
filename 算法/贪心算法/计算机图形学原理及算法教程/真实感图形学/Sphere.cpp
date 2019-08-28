/////////////////////////////////////////////////////////////////////////////////
//	
// Sphere.cpp: implementation of the CSphere class.
#include "stdafx.h"
#include "Sphere.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNAMIC(CSphere, CObject3d)

CSphere::CSphere()
{
	//空球
}

CSphere::CSphere(float fRadius,  int nSlices,  int nStacks)
{
	m_fRadius = ABS(fRadius);
	m_nSlices = nSlices;
	m_nStacks = nStacks;

	//最少不得小于8, 否则不象个球
	if(m_nSlices < 8) m_nSlices = 8;
	if(m_nStacks < 8) m_nStacks = 8;

	//初始化动态数组的大小.
	m_vList.SetSize(m_nSlices * (m_nStacks - 1) + 2);
	m_eList.SetSize(m_nSlices * (2 * m_nStacks - 1));
	m_sList.SetSize(m_nSlices * m_nStacks);

	InitVertices();
	InitFacets();
	InitEdges();

}

//复制构造函数
CSphere::CSphere(const CSphere& sphere)
{
	
	//复制经过编辑后的立方体
	//编辑是指对几何拓扑的修改
	int nNumVertex = sphere.GetVertexListSize();
	int nNumEdge = sphere.GetEdgeListSize();
	int nNumFacet = sphere.GetFacetListSize();

	//避免复制空对象
	ASSERT(nNumVertex > 2);
	ASSERT(nNumEdge > 2);
	ASSERT(nNumFacet > 0);

	m_vList.SetSize(nNumVertex);
	m_eList.SetSize(nNumEdge);
	m_sList.SetSize(nNumFacet);

	m_vList.Copy(sphere.m_vList);
	m_eList.Copy(sphere.m_eList);
	m_sList.Copy(sphere.m_sList);

	m_vList.FreeExtra();
	m_eList.FreeExtra();
	m_sList.FreeExtra();

	m_mGeomTrans = sphere.m_mGeomTrans;
	m_bAutoColor = sphere.m_bAutoColor;

	m_fRadius = sphere.m_fRadius;
	m_nSlices = sphere.m_nSlices;
	m_nStacks = sphere.m_nStacks;
}

CSphere::~CSphere()
{
	m_vList.RemoveAll();
	m_eList.RemoveAll();
	m_sList.RemoveAll();
}

//克隆
CSphere* CSphere::Clone()
{
	CSphere* pSphereCloned = new CSphere();
	
	//克隆几何及属性
	//几何元素个数
	int nNumVertex = GetVertexListSize();
	int nNumEdge = GetEdgeListSize();
	int nNumFacet = GetFacetListSize();

	//避免克隆空对象
	ASSERT(nNumVertex > 2);
	ASSERT(nNumEdge > 2);
	ASSERT(nNumFacet > 0);

	pSphereCloned->m_vList.SetSize(nNumVertex);
	pSphereCloned->m_eList.SetSize(nNumEdge);
	pSphereCloned->m_sList.SetSize(nNumFacet);

	pSphereCloned->m_vList.Copy(m_vList);
	pSphereCloned->m_eList.Copy(m_eList);
	pSphereCloned->m_sList.Copy(m_sList);

	pSphereCloned->m_mGeomTrans = m_mGeomTrans;
	pSphereCloned->m_bAutoColor = m_bAutoColor;
	pSphereCloned->m_fRadius = m_fRadius;
	pSphereCloned->m_nSlices = m_nSlices;
	pSphereCloned->m_nStacks = m_nStacks;
	
	return pSphereCloned;
}


//初始化顶点的几何(坐标和法线)
void CSphere::InitVertices()
{
	//处理方式, 
	//第一, 纬度自北极向南极递增, 并不象地理划分那样分北纬和南纬
	//第二, 经度从y轴正向开始, 按逆时针方向增加, 不区分东经和西经.

	//纬度递增量, 弧度表示
	float fStepLttd = (float) (PIE / m_nStacks);

	//经度递增量, 弧度表示
	float fStepLngtd = (float) (2.0 * PIE / m_nSlices);

	//纬度
	float fLatitude = fStepLttd;

	//第一步, 处理北极点

	//分三个内容:其一, 坐标; 其二, 法线; 其三, 顶点所在的小面序号
	
	m_vList[0].m_coord.x = 0.0f;
	m_vList[0].m_coord.y = 0.0f;
	m_vList[0].m_coord.z = m_fRadius;
	
	//法线与缺省值相同

	//i按纬度循环,  j按经度循环

	//顶点所在的小面(动态数组)
	for(int j = 0; j < m_nSlices; j++)
		m_vList[0].m_asIndex.Add(j);


	//第二步, 处理经纬线上的点
	for(int i = 0; i < (m_nStacks - 1); i++)
	{
		//内部将按经度循环

		//当前点所在的经度位置(弧度), 与 x 轴夹角
		//初始化为 -1.5* PIE;
		float fLongitude = -4.712389f;

		//法线 z 分量
		float zn = (float)cos(fLatitude);

		//坐标 z 分量
		float z = m_fRadius * zn;

		//按经度循环
		for(j = 0; j < m_nSlices; j++)
		{
			//法线 x, y 分量
			float xn = (float)(sin(fLatitude) * cos(fLongitude));
			float yn = (float)(sin(fLatitude) * sin(fLongitude));
			
			//坐标分量: x,  y
			float x = m_fRadius * xn,   y = m_fRadius * yn;
			
			//其一, 填写坐标分量

			//顶点序号
			int nIndex = i * m_nSlices + j + 1;

			m_vList[nIndex].m_coord.x = x;
			m_vList[nIndex].m_coord.y = y;
			m_vList[nIndex].m_coord.z = z;

			//其二, 填写法线分量
			m_vList[nIndex].m_normal.x = xn;
			m_vList[nIndex].m_normal.y = yn;
			m_vList[nIndex].m_normal.z = zn;

			//其三, 顶点所在的小面
			if(j == 0)
			{
				int anInFacets[4] = {
					i * m_nSlices,            (i + 1) * m_nSlices, 
					(i + 1) * m_nSlices - 1,  (i + 2) * m_nSlices - 1};

				m_vList[nIndex].DefineTopology(anInFacets,  4);
			}
			else
			{
				int anInFacets[4] = {
					i * m_nSlices + j - 1,  (i + 1) * m_nSlices + j - 1, 
					i * m_nSlices + j,      (i + 1) * m_nSlices + j};

				m_vList[nIndex].DefineTopology(anInFacets,  4);
			}//end j > 0

			//下一经线
			fLongitude += fStepLngtd;

		}//end for j

		//下一纬线
		fLatitude += fStepLttd;
	}//end for i

	//第三步, 处理南极点
	
	int nIndex = m_nSlices * (m_nStacks - 1) + 1;
	
	//其一, 坐标
	m_vList[nIndex].m_coord.x = 0.0f;
	m_vList[nIndex].m_coord.y = 0.0f;
	m_vList[nIndex].m_coord.z = -m_fRadius;

	//其二, 法线
	m_vList[nIndex].m_normal.x = 0.0f;
	m_vList[nIndex].m_normal.y = 0.0f;
	m_vList[nIndex].m_normal.z = -1.0f;

	//其三, 所在小面

	//小面基数
	int nFacetBase = m_nSlices * (m_nStacks - 1);
	
	//小面序号:
	for(j = 0; j < m_nSlices; j++)
		m_vList[nIndex].m_asIndex.Add(nFacetBase + j);
}

//初始化小面几何(坐标)
void CSphere::InitFacets()
{
	//i按纬度循环,  j按经度循环
	
	//首先处理位于北极圈内的面:
	for(int j = 0; j < (m_nSlices - 1); j++)
	{
		m_sList[j].m_avIndex.Add(0);
		m_sList[j].m_avIndex.Add(j + 1);
		m_sList[j].m_avIndex.Add(j + 2);
	}

	m_sList[j].m_avIndex.Add(0);
	m_sList[j].m_avIndex.Add(m_nSlices);
	m_sList[j].m_avIndex.Add(1);


	//第二, 处理除两极以外的小面
	for(int i = 0; i < (m_nStacks - 2); i++)
	{
		//小面位于两纬线之间, 
		//上纬线(投影)与 y 轴交点序号
		int nIndexUp = i * m_nSlices + 1;
		
		//下纬线(投影)与 y 轴交点序号
		int nIndexDown = nIndexUp + m_nSlices;

		//按经区循环
		for(j = 0; j < (m_nSlices - 1); j++)
		{
			int anVertices[4] =  {
				nIndexUp + j,        nIndexDown + j, 
				nIndexDown + j + 1,  nIndexUp + j + 1};
			m_sList[nIndexDown + j - 1].DefineTopology(anVertices,  4);
		}//end for j

		//j = m_nSlices - 1
		m_sList[nIndexDown + j - 1].m_avIndex.Add(nIndexUp + j);
		m_sList[nIndexDown + j - 1].m_avIndex.Add(nIndexDown + j);
		m_sList[nIndexDown + j - 1].m_avIndex.Add(nIndexDown);
		m_sList[nIndexDown + j - 1].m_avIndex.Add(nIndexUp);
	}//end for i;

	//最后处理南极圈内的小面

	//小面序号基数
	int nIndexFacet = (m_nStacks - 1) * m_nSlices;

	//顶点序号基数
	int nIndexVertex = m_nSlices * (m_nStacks - 2) + 1;

	for(j = 0; j < m_nSlices - 1; j++)
	{
		m_sList[nIndexFacet + j].m_avIndex.Add(nIndexVertex	+ j);
		m_sList[nIndexFacet + j].m_avIndex.Add(nIndexFacet	+ 1);
		m_sList[nIndexFacet + j].m_avIndex.Add(nIndexVertex	+ j + 1);
	}


	//最后还在一个小面
	m_sList[nIndexFacet + j].m_avIndex.Add(nIndexVertex	+ j);
	m_sList[nIndexFacet + j].m_avIndex.Add(nIndexFacet	+ 1);
	m_sList[nIndexFacet + j].m_avIndex.Add(nIndexVertex);

}

//初始化边
void CSphere::InitEdges()
{
	//i按纬度循环,  j按经度循环	

	//第一步, 首先处理经线上的边, 然后处理纬线上的边

	
	//其一, 处理第一条经线边

	m_eList[0].DefineEdge(0, 1);
	m_eList[0].m_asIndex.Add(0);
	m_eList[0].m_asIndex.Add(m_nSlices - 1);
	
	for(int i = 1; i < (m_nStacks - 1); i++)
	{
		m_eList[i].DefineEdge((i - 1) * m_nSlices + 1, 
							  i * m_nSlices + 1);
		m_eList[i].m_asIndex.Add(i * m_nSlices);
		m_eList[i].m_asIndex.Add((i + 1) * m_nSlices - 1);
	}


	i--;	//i = m_nStack - 2;

	m_eList[m_nStacks - 1].DefineEdge(i * m_nSlices + 1,  
									 m_nSlices * (m_nStacks - 1) + 1 );
	m_eList[m_nStacks - 1].m_asIndex.Add(m_nSlices * (m_nStacks - 1));
	m_eList[m_nStacks - 1].m_asIndex.Add(m_nSlices * m_nStacks - 1);


	//其二, 处理其它经线上的边
	for(int j = 1; j < m_nSlices; j++)
	{

		int nIndex = j * m_nStacks;
		m_eList[nIndex].DefineEdge(0,  (j + 1));
		m_eList[nIndex].m_asIndex.Add(j - 1);
		m_eList[nIndex].m_asIndex.Add(j);

		//除两极内的经线边
		for(i = 1; i < (m_nStacks - 1); i++)
		{
			m_eList[nIndex + i].DefineEdge((i - 1) * m_nSlices + j + 1, 
										   i * m_nSlices + j + 1);
			m_eList[nIndex + i].m_asIndex.Add(i * m_nSlices + j - 1);
			m_eList[nIndex + i].m_asIndex.Add(i * m_nSlices + j);
		}

		//位于南极内的边
		m_eList[nIndex + i].DefineEdge((m_nStacks - 2) * m_nSlices + j + 1, 
								       m_nSlices * (m_nStacks - 1) + 1);
		m_eList[nIndex + i].m_asIndex.Add(m_nSlices * (m_nStacks - 1) + j - 1);
		m_eList[nIndex + i].m_asIndex.Add(m_nSlices * (m_nStacks - 1) + j);
	}//end for j

	//纬线边基数
	int neBase = m_nStacks * m_nSlices;
	for(i = 0; i < (m_nStacks - 1); i++)
	{
		//顶点索引 (起始值 - 1)
		int nvBase = i * m_nSlices;

		//同一条纬线上的边
		int nIndex = neBase + nvBase;
		for(j = 0; j < (m_nSlices - 1); j++)
		{
			m_eList[nIndex + j].DefineEdge(nvBase + j + 1,  nvBase + j + 2);
			m_eList[nIndex + j].m_asIndex.Add(nvBase + j);
			m_eList[nIndex + j].m_asIndex.Add(nvBase + m_nSlices + j);
		}

		//j = m_nSlices - 1;
		m_eList[nIndex + j].DefineEdge(nvBase + j + 1,  nvBase + 1);
		m_eList[nIndex + j].m_asIndex.Add(nvBase + m_nSlices - 1);
		m_eList[nIndex + j].m_asIndex.Add(nvBase + 2 * m_nSlices - 1);

	}//end for i(2nd)
}
