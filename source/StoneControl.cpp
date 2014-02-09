#include "stdfx.h"
#include "StoneControl.h"
#include "Directx.h"
#include "Camera.h"
#include "Input.h"
#include "Timer.h"
#include "Game.h"
CStoneControl::CStoneControl(CEntityEx* tmpStone){
	stone = tmpStone;
	actor = NULL;
	init = false;
	pointMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pointMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	direction = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	camDirection = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	enable = true;
	status = CSS_NORMAL;
	if(stone->GetActor() != NULL){
		actor = stone->GetActor();
		// 		shape = actor->getShapes()[0]->isCapsule();
		// 		if(shape == NULL){
		// 			init = false;
		// 			LOGFATAL("CStoneControl: (CStoneControl) Nie mozna pobrac shape!");
		// 			return;
		// 		}
		// 		
		// 		actor->addForceAtLocalPos(NxVec3(10.0f, 0.0f, 0.0f), NxVec3(0.0f, 0.0f, 0.0f));
		// 		init = true;
	}
}
void CStoneControl::Stop(){
	status = CSS_STOP;
}
void CStoneControl::Update(){
	if(Game.GetStatus() != game) return;
	NxVec3 position = stone->GetPosition();
	D3DXVECTOR3 camPosition = Camera.GetPosition();
	
	D3DXVECTOR3 direction = camPosition - D3DXVECTOR3(position.x, position.y, position.z);
	direction = direction * (-1);
	direction.y = 0;
	
	D3DXVec3Normalize(&direction, &direction);
	D3DXVec3Normalize(&direction, &direction);
	if(status == CSS_STOP){
		actor->putToSleep();
		status = CSS_STARTING;
		return;
	}else if(status == CSS_STARTING){
		actor->addForceAtLocalPos(NxVec3(direction.x * 1.0f, direction.y, direction.z * 1.0f), NxVec3(0.0f, 0.0f, 0.0f));
		status = CSS_NORMAL;
		return;
	}
	if(enable == false) return;
	if(Input.ArrowUp()){
		actor->addForceAtLocalPos(NxVec3(direction.x * 150.0f, direction.y, direction.z * 150.0f), NxVec3(0.0f, 0.0f, 0.0f));
	}
	if(Input.ArrowDown()){
		actor->addForceAtLocalPos(NxVec3(direction.x * -150.0f, direction.y, direction.z * -150.0f), NxVec3(0.0f, 0.0f, 0.0f));
	}
	if(Input.ArrowLeft()){
		D3DXMATRIX tmpRot;
		D3DXVECTOR3 tmpDir;
		D3DXMatrixRotationAxis(&tmpRot, &(D3DXVECTOR3(0.0f, 1.0f, 0.0f)), D3DXToRadian(-90.0f));
		D3DXVec3TransformCoord(&tmpDir, &direction, &tmpRot);
		actor->addForceAtLocalPos(NxVec3(tmpDir.x * 150.0f, tmpDir.y, tmpDir.z * 150.0f), NxVec3(0.0f, 0.0f, 0.0f));
	}
	if(Input.ArrowRight()){
		D3DXMATRIX tmpRot;
		D3DXVECTOR3 tmpDir;
		D3DXMatrixRotationAxis(&tmpRot, &(D3DXVECTOR3(0.0f, 1.0f, 0.0f)), D3DXToRadian(90.0f));
		D3DXVec3TransformCoord(&tmpDir, &direction, &tmpRot);
		actor->addForceAtLocalPos(NxVec3(tmpDir.x * 150.0f, tmpDir.y, tmpDir.z * 150.0f), NxVec3(0.0f, 0.0f, 0.0f));
	}
}