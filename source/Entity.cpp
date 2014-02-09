#include "Entity.h"
#include "Directx.h"
#include "Media.h"
#include "Mesh.h"
#include "Texture.h"
#include "Logger.h"
#include "FrustrumShapes.h"
#include "Camera.h"
#include "Scene.h"
#include "FPSCounter.h"

CEntity::CEntity(string _name){
	name = _name;
	type = RST_SIMPLE;
	mesh = NULL;
	texture = NULL;
	frustrumShape = NULL;
	fcShapeType = FC_NONE;
	normalMap = NULL;
	rotationSpeed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	position = D3DXVECTOR3(0.0f,0.0f,0.0f);
	visible = true;
	D3DXMatrixIdentity(&matRotate);
	D3DXMatrixIdentity(&matTranslate);
	D3DXMatrixIdentity(&matScale);
	SetStartRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	SetStartScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
}
void CEntity::Update(){
	if(!visible) return;
	float timeX = rotationSpeed.x*FPSCounter.GetElapsedTime();
	if(timeX > 3.14) timeX = -timeX;
	rotation.x += timeX;

	float timeY = rotationSpeed.y*FPSCounter.GetElapsedTime();
	if(timeY > 3.14) timeY = -timeY;
	rotation.y += timeY;

	float timeZ = rotationSpeed.z*FPSCounter.GetElapsedTime();
	if(timeZ > 3.14) timeZ = -timeZ;
	rotation.z += timeZ;
}
void CEntity::SetAnimation(float x, float y, float z){
	rotationSpeed.x = x;
	rotationSpeed.y = y;
	rotationSpeed.z = z;
}
void CEntity::Render(){
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
void CEntity::RenderEx(){
	D3DXMATRIX tempMat = GetMatrix();
	DirectX.GetEffect()->SetMatrix("World",&tempMat);
	DirectX.GetEffect()->SetMatrix("View", &Camera.GetView());
	DirectX.GetEffect()->SetMatrix("Projection", &Camera.GetProjection());
	DirectX.GetEffect()->SetMatrix("WVP",&(tempMat*Camera.GetMatrix()));

	unsigned int n=GetMesh()->GetMaterialsNum();
	for(DWORD i = 0; i < n; i++){
		if(texture){
			DirectX.GetEffect()->SetTexture("Texture",(texture->GetImage()));
			DirectX.GetEffect()->CommitChanges();
		}
		GetMesh()->GetModel()->DrawSubset(i);
	}
}
void CEntity::RenderEx(D3DXMATRIX world){
	DirectX.GetEffect()->SetMatrix("World",&world);
	DirectX.GetEffect()->SetMatrix("View", &Camera.GetView());
	DirectX.GetEffect()->SetMatrix("Projection", &Camera.GetProjection());
	DirectX.GetEffect()->SetMatrix("WVP",&(world*Camera.GetMatrix()));

	unsigned int n=GetMesh()->GetMaterialsNum();
	for(DWORD i = 0; i < n; i++){
		if(texture){
			DirectX.GetEffect()->SetTexture("Texture",(texture->GetImage()));
			DirectX.GetEffect()->CommitChanges();
		}
		if(normalMap){
			DirectX.GetEffect()->SetTexture("NormalMap",(normalMap->GetImage()));
			DirectX.GetEffect()->SetVector("CameraPos", &D3DXVECTOR4(Camera.GetPosition(), 1.0f));
		}
		GetMesh()->GetModel()->DrawSubset(i);
	}
}
bool CEntity::SetNormalMap(string name, IRenderable* entity){
	normalMap = Media.GetTexture(name);
	if(normalMap == NULL){
		ELOG("CEntity","SetTexture",string("Nie znaleziono textury (normal mapy), Nazwa: ") + name);
		return false;
	}
	type = RST_NORMALMAP;
	return true;
}
bool CEntity::SetMesh(string meshName){
	mesh = Media.GetMesh(meshName);
	if(mesh == NULL){
		ELOG("CEntity","SetMesh",string("Nie znaleziono mesha, Nazwa: ") + meshName);
		return false;
	}
	frustrumShape = new CFrustrumBox();
	fcShapeType = FC_BOX;
	if(frustrumShape->Compute(mesh, scale) == false){
		ELOG("CEntityEx","GetShapeDesc","Nie mozna stworzyc frustrumShape!");
		return NULL;
	}
	return true;
}
bool CEntity::SetTexture(string textureName){
	texture = Media.GetTexture(textureName);
	if(texture == NULL){
		ELOG("CEntity","SetTexture",string("Nie znaleziono textury, Nazwa: ") + textureName);
		return false;
	}	
	return true;
}
D3DXMATRIX CEntity::GetRotationMatrix(){
	D3DXMATRIX matRotX;
	D3DXMATRIX matRotY;
	D3DXMATRIX matRotZ;
	D3DXMatrixRotationX(&matRotX, D3DXToRadian(rotation.x));
	D3DXMatrixRotationY(&matRotY, D3DXToRadian(rotation.y));
	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(rotation.z));
	return matRotX * matRotY * matRotZ;
}
void CEntity::SetStartScale(D3DXVECTOR3 tmpScale){
	scale = tmpScale;
}
void CEntity::SetStartPosition(D3DXVECTOR3 tmpStartPosition){
	position = tmpStartPosition;
}
void CEntity::SetStartRotation(D3DXVECTOR3 tmpRotation){
	rotation = tmpRotation;
}
D3DXVECTOR3 CEntity::GetPosition(){
	return position;
}
D3DXMATRIX CEntity::GetMatrix(){
	D3DXMatrixScaling(&matScale, scale.x, scale.y, scale.z);
	D3DXMATRIX matRotX;
	D3DXMATRIX matRotY;
	D3DXMATRIX matRotZ;
	D3DXMatrixRotationX(&matRotX, D3DXToRadian(rotation.x));
	D3DXMatrixRotationY(&matRotY, D3DXToRadian(rotation.y));
	D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(rotation.z));
	D3DXMatrixTranslation(&matTranslate,position.x,position.y,position.z);
	return matScale*matRotX*matRotY*matRotZ*matTranslate;
}