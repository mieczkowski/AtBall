#include "Trigger.h"
#include "Physx.h"
#include "Scene.h"
CTrigger::CTrigger(string n, D3DXVECTOR3 pos, D3DXVECTOR3 dim){
	position = pos;
	dimension = dim;
	name = n;
	actor = NULL;
	Enable();
}
CTrigger::~CTrigger(){
	Disable();
}
void CTrigger::Enable(){
	if(actor) return;
	NxBoxShapeDesc boxDesc;    
	boxDesc.dimensions = NxVec3(dimension.x, dimension.y, dimension.z);    
	boxDesc.shapeFlags |= NX_TRIGGER_ON_ENTER; 
	NxActorDesc actorDesc;    
	actorDesc.shapes.pushBack(&boxDesc);
	actorDesc.globalPose.t = NxVec3(position.x, position.y, position.z);
	actorDesc.name = name.c_str();
	actor = Scene.GetPhysxScene()->createActor(actorDesc);
}
void CTrigger::Disable(){
	if(actor){
		Scene.GetPhysxScene()->releaseActor(*actor);
		actor = NULL;
	}
}
