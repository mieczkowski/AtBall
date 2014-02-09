#pragma once
#include "stdfx.h"
class NxActor;
class CTrigger{
public:
	CTrigger(string n, D3DXVECTOR3 pos, D3DXVECTOR3 dim);
	~CTrigger();
	void Enable();
	void Disable();
protected:
	D3DXVECTOR3 position, dimension;
	string name;
	NxActor* actor;
};
