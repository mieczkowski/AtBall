#pragma once
#include "stdfx.h"
class NxForceFieldLinearKernel;
class NxForceField;
class NxForceFieldShape;
class NxActor;
class CForceField{
public:
	CForceField(NxActor* tmpactor, const D3DXVECTOR3& tmpModelDirection, 
		float tmpforce,const D3DXVECTOR3& tmpscale);
	void Enable(NxActor* tmpactor);
	void Disable();
	~CForceField();
protected:
	NxForceFieldLinearKernel* kernel;
	NxForceField* forcefield;
	NxForceFieldShape* shape;
	NxActor* actor;
	
	D3DXVECTOR3 modelDirection;
	float forceValue;
	D3DXVECTOR3 scale;
};
