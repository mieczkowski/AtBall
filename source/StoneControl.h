#pragma once
#include "Updateable.h"
#include "stdfx.h"
#include "Physx.h"
#include "Entity.h"
enum ControlStopStatus{
	CSS_NORMAL, CSS_STOP, CSS_STARTING
};
class CStoneControl : public IUpdateable{
public:
	CStoneControl(CEntityEx* tmpStone);
	void Update();
	void Stop();
protected:
	ControlStopStatus status;
	CEntityEx* stone;
	NxActor* actor;
	float localYMax, localYMin; //lokalne punkty Y kamienia (stala wartosc)
	D3DXVECTOR3 pointMin, pointMax; //punkty kamienia w przestrzeni globalnej (wyliczane)
	D3DXVECTOR3 direction, camDirection; //kierunek kamienia, wyliczany w zaleznosci od directionUp (kierunek w przod lub tyl)
	NxCapsuleShape* shape;
	bool init; //jesli wszystko ok (aktor ustawiony i punkty) to mozna uaktualniac
};
