#include "Entity.h"
#include "Stream.h"
#include "Directx.h"
#include "Physx.h"
#include "Media.h"
#include "Mesh.h"
#include "Texture.h"
#include "Logger.h"
#include "FrustrumShapes.h"
#include "Camera.h"
#include "Scene.h"
#include "ForceField.h"
#include "Script.h"
#include "Trigger.h"
#include "Game.h"
CEntityEx::CEntityEx(string _name) : CEntity(_name){
	actor = NULL;
	dynamic = true;
	updateObject = NULL;
	physxShapeType = PX_NONE;
	forceField = NULL;
	bindObject = NULL;
	trigger = NULL;
	outOfScene = false;
	outOfScene2 = false;
	callbackProcedures[NX_NOTIFY_ON_START_TOUCH] = "";
	callbackProcedures[NX_NOTIFY_ON_TOUCH] = "";
	callbackProcedures[NX_NOTIFY_ON_END_TOUCH] = "";
	callbackProcedures[NX_NOTIFY_ON_IMPACT] = "";
	callbackProcedures[NX_NOTIFY_ON_START_TOUCH_FORCE_THRESHOLD] = "";
	callbackProcedures[NX_NOTIFY_ON_TOUCH_FORCE_THRESHOLD] = "";
	callbackProcedures[NX_NOTIFY_ON_END_TOUCH_FORCE_THRESHOLD] = "";
}

void CEntityEx::Clear(){
	Scene.GetPhysxScene()->releaseActor(*actor);
	SAFE_DELETE(updateObject);
}

void CEntityEx::Update(){
	if(!visible) return;
	if(Game.GetStatus() == game){
		NxVec3 tmpPos = actor->getGlobalPosition();
		position.x = tmpPos.x;
		position.y = tmpPos.y;
		position.z = tmpPos.z;
		if(updateObject != NULL){
			updateObject->Update();
		}
	}
	if(bindObject) bindObject->Update();
	if(position.y < -10.0f){
		if(outOfScene == false){
			Script.CallFunction(Game.GetActualLevel(), "outOfScene", name);
			outOfScene = true;
		}
	}
	if(position.y < -235.0f){
		if(outOfScene2 == false){
			Script.CallFunction(Game.GetActualLevel(), "outOfScene2", name);
			outOfScene2 = true;
		}
	}
}
D3DXMATRIX CEntityEx::GetMatrix(){	
	D3DXMatrixScaling(&matScale, scale.x, scale.y, scale.z);

	NxQuat quat = actor->getGlobalOrientationQuat();
	D3DXQUATERNION dxquat = D3DXQUATERNION(quat.x,quat.y,quat.z,quat.w);
	D3DXMatrixRotationQuaternion(&matRotate,&dxquat);

	if(bindObject){
		matRotate *= bindObject->GetRotationMatrix();
	}
	D3DXVECTOR3 dxTransVec = GetPosition();
	D3DXMatrixTranslation(&matTranslate,dxTransVec.x,dxTransVec.y,dxTransVec.z);
	return matScale*matRotate*matTranslate;
}
void CEntityEx::Show(){
	actor->setGlobalPosition(NxVec3(position.x,position.y,position.z));
	actor->clearActorFlag(NX_AF_DISABLE_COLLISION);
	actor->clearBodyFlag(NX_BF_KINEMATIC);
	visible = true;
}
void CEntityEx::Hide(){
	actor->raiseActorFlag(NX_AF_DISABLE_COLLISION);
	actor->raiseBodyFlag(NX_BF_KINEMATIC);
	visible = false;
}
void CEntityEx::Render(){
	if(!visible) return;
// 	RenderEx();
// 	return;
	if(frustrumShape != NULL){
		if(frustrumShape->InFrustum(GetPosition())){
			RenderEx();
		}
	}else{
		RenderEx();
	}
}

void CEntityEx::RenderEx(){
	if(bindObject){
		bindObject->RenderEx(GetMatrix());
	}else{
		D3DXMATRIX tempMat = GetMatrix();
		DirectX.GetEffect()->SetMatrix("World",&tempMat);
		DirectX.GetEffect()->SetMatrix("View", &Camera.GetView());
		DirectX.GetEffect()->SetMatrix("Projection", &Camera.GetProjection());
		DirectX.GetEffect()->SetMatrix("WVP",&(tempMat*Camera.GetMatrix()));

		unsigned int n=GetMesh()->GetMaterialsNum();
		for(DWORD i = 0; i < n; i++){
			if(texture){
				DirectX.GetEffect()->SetTexture("Texture",(texture->GetImage()));
			}
			if(normalMap){
				DirectX.GetEffect()->SetTexture("NormalMap",(normalMap->GetImage()));
				DirectX.GetEffect()->SetVector("CameraPos", &D3DXVECTOR4(Camera.GetPosition(), 1.0f));
			}
			DirectX.GetEffect()->CommitChanges();
			GetMesh()->GetModel()->DrawSubset(i);
		}
	}
}

bool CEntityEx::SetMesh(string meshName){
	mesh = Media.GetMesh(meshName);
	if(mesh == NULL){
		ELOG("CEntityEx","SetMesh",string("Nie znaleziono mesha, Nazwa: ") + meshName);
		return false;
	}
	NxBodyDesc *bodyDesc = NULL;
	if(dynamic == true){
		bodyDesc = new NxBodyDesc();
		bodyDesc->setToDefault();
		if(!bodyDesc->isValid()){
			ELOG("CEntityEx","SetMesh","BodyDesc isNotValid!");
			return false;
		}
	}
	NxMaterialDesc materialDesc;
	materialDesc.setToDefault();
	if(materialDesc.isValid()){
		NxMaterial *material = Scene.GetPhysxScene()->createMaterial(materialDesc);
		materialIndex = material->getMaterialIndex();
	}else{
		ELOG("CEntityEx","SetMesh","Nie mozna stworzyc materialu!");
		return false;
	}

	NxShapeDesc *tmpShapeDesc = GetShapeDesc();
	if(tmpShapeDesc == NULL){
		ELOG("CEntityEx","SetMesh","GetShapeDesc zwróci³o NULL!");
		return false;
	}
	tmpShapeDesc->materialIndex = materialIndex;
	tmpShapeDesc->name = name.c_str();
	if(!tmpShapeDesc->isValid()){
		ELOG("CEntityEx","SetMesh","TmpShapeDesc is notValid!");
		return false;
	}
	NxActorDesc *actorDesc = new NxActorDesc();
	actorDesc->setToDefault();
	actorDesc->shapes.push_back(tmpShapeDesc);
	if(dynamic == true) actorDesc->body=bodyDesc;
	actorDesc->density=10.0f;
	actorDesc->name=name.c_str();
	actorDesc->globalPose.t=NxVec3(position.x,position.y,position.z);
	actorDesc->userData = "entity";
	if(actorDesc->isValid()){
		actor = Scene.GetPhysxScene()->createActor(*actorDesc);
		actor->setGlobalOrientationQuat(rotationQuat);
	}else{
		ELOG("CEntityEx","SetMesh","Nie mozna stworzyc aktora (notValid)!");
		return false;
	}
	return true;
}
void CEntityEx::SetBindObject(CEntity* ent){
	Scene.Del(ent->GetName(), ent->GetType());
	bindObject = ent;

}
void CEntityEx::EnableForceField(D3DXVECTOR3 direction, float force){
	if(forceField == NULL){
		forceField = new CForceField(actor, direction, force, scale);
	}else{
		forceField->Enable(actor);
	}
}
void CEntityEx::EnableTrigger(D3DXVECTOR3 dim){
	if(trigger == NULL){
		trigger = new CTrigger(name, position, 
			D3DXVECTOR3(scale.x * dim.x, scale.y * dim.y, scale.z * dim.z));
	}else{
		trigger->Enable();
	}
}
void CEntityEx::SetStartRotation(D3DXVECTOR3 tmpRotation){
	D3DXQUATERNION dxquat;
	D3DXQuaternionIdentity(&dxquat);
	D3DXQuaternionRotationYawPitchRoll(&dxquat, D3DXToRadian(tmpRotation.y), D3DXToRadian(tmpRotation.x), D3DXToRadian(tmpRotation.z));
	rotationQuat = NxQuat(NxVec3(dxquat.x, dxquat.y, dxquat.z), dxquat.w);
}

D3DXVECTOR3 CEntityEx::GetPosition(){
	if(actor) {
		NxVec3 pos = actor->getGlobalPosition();
		return D3DXVECTOR3(pos.x,pos.y,pos.z);
	}else{
		return D3DXVECTOR3(0,0,0);
	}
}

NxMaterial* CEntityEx::GetMaterial(){
	return Scene.GetPhysxScene()->getMaterialFromIndex(materialIndex);
}

NxShapeDesc* CEntityEx::GetShapeDesc(){
	if(physxShapeType == PX_NONE){
		ELOG("CEntityEx","GetShapeDesc","physxshape nie ustawione!");
		return NULL;
	}
	switch(physxShapeType){
		case PX_BOX:
			{
				frustrumShape = new CFrustrumBox();
				fcShapeType = FC_BOX;
				if(frustrumShape->Compute(mesh, scale) == false){
					ELOG("CEntityEx","GetShapeDesc","Nie mozna stworzyc frustrumShape!");
					return NULL;
				}
				D3DXVECTOR3 pMin = frustrumShape->GetMinPoint();
				D3DXVECTOR3 pMax = frustrumShape->GetMaxPoint();

				NxBoxShapeDesc* boxShapeDesc = new NxBoxShapeDesc();
				boxShapeDesc->dimensions.set((pMax.x-pMin.x)/2,(pMax.y-pMin.y)/2,(pMax.z-pMin.z)/2);
				return boxShapeDesc;
			}
			break;
		case PX_CAPSULE:
			{
				frustrumShape = new CFrustrumBox();
				fcShapeType = FC_BOX;
				if(frustrumShape->Compute(mesh, scale) == false){
					ELOG("CEntityEx","GetShapeDesc","Nie mozna stworzyc frustrumShape!");
					return NULL;
				}
				D3DXVECTOR3 pMin = frustrumShape->GetMinPoint();
				D3DXVECTOR3 pMax = frustrumShape->GetMaxPoint();

				NxCapsuleShapeDesc* capsuleShapeDesc = new NxCapsuleShapeDesc();
				capsuleShapeDesc->height = (pMax.y - pMin.y) - (pMax.x - pMin.x);
				capsuleShapeDesc->radius = (pMax.x - pMin.x)/2;
				return capsuleShapeDesc;
			}
			break;
		case PX_SPHERE:
			{
				frustrumShape = new CFrustrumSphere();
				fcShapeType = FC_SPHERE;
				if(frustrumShape->Compute(mesh, scale) == false){
					ELOG("CEntityEx","GetShapeDesc","Nie mozna stworzyc frustrumShape!");
					return NULL;
				}
				NxSphereShapeDesc* sphereShapeDesc = new NxSphereShapeDesc();
				sphereShapeDesc->radius = frustrumShape->GetRadius();
				return sphereShapeDesc;
			}

			break;
		case PX_TRIANGLE:
			{
				frustrumShape = new CFrustrumBox();
				fcShapeType = FC_BOX;
				if(frustrumShape->Compute(mesh, scale) == false){
					ELOG("CEntityEx","GetShapeDesc","Nie mozna stworzyc frustrumShape!");
					return NULL;
				}

				NxTriangleMeshShapeDesc* shapeDesc = new NxTriangleMeshShapeDesc();
				if(mesh->GenerateTriangleMeshShapeDesc(shapeDesc, scale)){
					return shapeDesc;
				}else{
					return NULL;
				}
			}
			break;
		case PX_CONVEX:
			{			
				frustrumShape = new CFrustrumBox();
				fcShapeType = FC_BOX;
				if(frustrumShape->Compute(mesh, scale) == false){
					ELOG("CEntityEx","GetShapeDesc","Nie mozna stworzyc frustrumShape!");
					return NULL;
				}
				NxConvexShapeDesc* shapeDesc = mesh->GenerateConvexMeshDesc(scale);
				if(shapeDesc){
					return shapeDesc;
				}else{
					return NULL;
				}
			}
			break;
		default:
			return NULL;
	}
	return NULL;
}


