#pragma once
#include "stdfx.h"
class CMesh;
class CFrustrumShape{
public:
	CFrustrumShape(void){}
	~CFrustrumShape(void){}
public :
	virtual bool Compute(CMesh* mesh, D3DXVECTOR3 scale)=0;
	virtual bool InFrustum(D3DXVECTOR3 objectPosition)=0;
	virtual float GetRadius(void);
	virtual D3DXVECTOR3 GetCenter(void);
	virtual D3DXVECTOR3 GetMinPoint(void);
	virtual D3DXVECTOR3 GetMaxPoint(void);
};

class CFrustrumSphere : public CFrustrumShape{
public:
	CFrustrumSphere(void){}
	~CFrustrumSphere(void){}
public:
	bool Compute(CMesh* mesh, D3DXVECTOR3 scale);
	bool InFrustum(D3DXVECTOR3 objectPosition);
	D3DXVECTOR3 GetCenter(void);
	float GetRadius(void);
private:
	D3DXVECTOR3 center;
	float radius;
};

class CFrustrumBox : public CFrustrumShape
{
public:
	CFrustrumBox(void){}
	~CFrustrumBox(void){}
public:
	bool Compute(CMesh* mesh, D3DXVECTOR3 scale);
	bool InFrustum(D3DXVECTOR3 objectPosition);
	D3DXVECTOR3 GetMinPoint(void);
	D3DXVECTOR3 GetMaxPoint(void);
private:
	D3DXVECTOR3 pMin;
	D3DXVECTOR3 pMax;
};