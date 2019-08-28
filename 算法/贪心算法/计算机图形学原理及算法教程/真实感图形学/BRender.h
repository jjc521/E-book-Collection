// BRender.h: interface for the BRender class.
#ifndef _CBRENDER_H
#define _CBRENDER_H

#include "Object3d.h"
#include "ColorBuffer.h"
#include "ZBuffer.h"

class CBRender  
{
public:
	CBRender();
	virtual ~CBRender();

public:

	//着色
	void Render(CObject3d* pObj, VERTEX3D viewer, VIEWFINDER viewFinder, CColorBuffer* pCB, CZBuffer* pZB, DWORD dwRop);
private:

	//顶点模型
	void Vertexize(CObject3d* pObj, POINT* pPtOnScrn, HOMOCOORD* pvInView, CColorBuffer* pCB, CZBuffer* pZB);
	
	//线框模型
	void FlatWirize(CObject3d* pObj, POINT* pPtOnScrn, HOMOCOORD* pvInView, CColorBuffer* pCB, CZBuffer* pZB);
	void GouraudWirize(CObject3d* pObj, POINT* pPtOnScrn, HOMOCOORD* pvInView, CColorBuffer* pCB, CZBuffer* pZB);

	//实体模型
	void Flat(CObject3d* pObj, POINT* pPtOnScrn, HOMOCOORD* pvInView, CColorBuffer* pCB, CZBuffer* pZB);
	void Gouraud(CObject3d* pObj, POINT* pPtOnScrn, HOMOCOORD* pvInView, CColorBuffer* pCB, CZBuffer* pZB);

};

#endif
