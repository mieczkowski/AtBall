#include "ForceField.h"
#include "Physx.h"
#include "Scene.h"
#include "Directx.h"
#include "Entity.h"
#include "Logger.h"

CForceField::CForceField(NxActor* tmpactor, const D3DXVECTOR3& tmpModelDirection, 
						 float tmpforce, const D3DXVECTOR3& tmpscale){
	modelDirection = tmpModelDirection;
	scale = tmpscale;
	forceValue = tmpforce;
	forcefield = NULL;
	kernel = NULL;
	shape = NULL;
	actor = NULL;
	Enable(tmpactor);
}
void CForceField::Enable(NxActor* tmpactor){
	if(forcefield) return;
	D3DXVec3Normalize(&modelDirection, &modelDirection);
	float dimensionX = scale.x + modelDirection.x * forceValue * 0.004f * scale.x;
	float dimensionY = scale.y + modelDirection.y * forceValue * 0.004f * scale.x;
	float dimensionZ = scale.z + modelDirection.z * forceValue * 0.004f * scale.x;
	NxVec3 dimension = NxVec3(dimensionX, dimensionY, dimensionZ);
	NxVec3 actorPosition = tmpactor->getGlobalPosition();
	float positionX = actorPosition.x + modelDirection.x * (dimensionX);
	float positionY = actorPosition.y + modelDirection.y * (dimensionY);
	float positionZ = actorPosition.z + modelDirection.z * (dimensionZ);
	NxVec3 position = NxVec3(positionX, positionY, positionZ);
	NxVec3 force = NxVec3(modelDirection.x * forceValue, modelDirection.y * forceValue, modelDirection.z * forceValue);
	
	NxForceFieldLinearKernelDesc linearKernelDesc;
	linearKernelDesc.constant = force;
	linearKernelDesc.velocityTarget = force;

	kernel = Scene.GetPhysxScene()->createForceFieldLinearKernel(linearKernelDesc);

	NxBoxShapeDesc bDesc;
	bDesc.dimensions = dimension;
	bDesc.mass = dimension.x * dimension.y * dimension.z;
	bDesc.shapeFlags |= NX_SF_DISABLE_COLLISION;

	NxActorDesc actorDesc;
	actorDesc.globalPose.t = position;
	actorDesc.density = 10.0f;
	actorDesc.shapes.push_back(&bDesc);
	actor = Scene.GetPhysxScene()->createActor(actorDesc);

	NxForceFieldDesc fieldDesc;
	fieldDesc.kernel = kernel;
	fieldDesc.actor = actor;

	forcefield = Scene.GetPhysxScene()->createForceField(fieldDesc);

	NxBoxForceFieldShapeDesc boxDesc;
	boxDesc.dimensions = dimension;

	shape = forcefield->getIncludeShapeGroup().createShape(boxDesc);
}
void CForceField::Disable(){
	if(!forcefield) return;
	//Scene.GetPhysxScene()->releaseForceFieldLinearKernel(*kernel);
	Scene.GetPhysxScene()->releaseForceField(*forcefield);
	kernel = NULL;
	forcefield = NULL;
	shape = NULL;
	actor = NULL;
}
CForceField::~CForceField(){
	if(forcefield)
	Scene.GetPhysxScene()->releaseForceField(*forcefield);
}

