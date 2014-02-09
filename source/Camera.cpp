#include "Camera.h"
//#include <d3dx9mesh.h>
#include "Input.h"
#include "FPSCounter.h"
#include "Mesh.h"
#include "Entity.h"
#include "EntityMgr.h"
#include "Game.h"
#include <map>
using namespace std;
CCamera::CCamera(void){
	followedObject = NULL;
	positionChanged = false;
	D3DXMatrixIdentity(&matProjection);
	D3DXMatrixIdentity(&matView);
}
void CCamera::Init(){
	viewAngle=45;
	up=D3DXVECTOR3(0.0f,1.0f,0.0f);
	nearplane=0.01f;
	farplane=250.0f;
	position = D3DXVECTOR3(0.0f,0.0f,0.0f);
	lookAt = D3DXVECTOR3(0.0f,0.0f,0.0f);
	distance = 10.0f;
	rotation = 0.0f;
	distanceUp = 5.0f;
	animationRotation = 0.0f;
	followedObject = NULL;
	positionChanged = false;
	positionFrozen = false;
	D3DXMatrixIdentity(&matProjection);
	D3DXMatrixIdentity(&matView);
	status=CAMERA_STATIC;
	SetPerspective();
	SetStatic();
}
void CCamera::SetStatic(){
	status = CAMERA_STATIC;
	lookAt = D3DXVECTOR3(0.0f,0.0f,0.0f);
	position = D3DXVECTOR3(0.0f,5.0f,-10.0f);
	UpdateViewMatrix();
	BuildFrustum();
}
void CCamera::SetDynamic(){
	if(followedObject != NULL){
		status = CAMERA_FOLLOWING;
	}
}
D3DXVECTOR3 CCamera::GetDirection(){
	D3DXVECTOR3 direction;
	D3DXVec3Normalize(&direction, &(lookAt - position));
	return direction;
}
void CCamera::UpdatePosition(){
	if(followedObject != NULL){
		lookAt = followedObject->GetPosition();
		float x = lookAt.x - sin(rotation)*distance;
		float y = lookAt.y + distanceUp;
		float z = lookAt.z - cos(rotation)*distance;
		if(x != position.x || y != position.y || z != position.z){
			positionChanged = true;
		}
		if(!positionFrozen){
			position.x = x;
			position.y = y;
			position.z = z;
		}		
		UpdateViewMatrix();
		BuildFrustum();
	}
}
bool CCamera::SetFollowedObject(string name){
	followedObject = (IRenderable*) EntityMgr.GetEntity(name);
	if(followedObject == NULL){
		ELOG("Camera","SetFollowedObject","Nie znaleziono obiektu do sledzenia, ustawianie statycznej kamery!");
		return false;
	}
	return true;
}
void CCamera::Update(){
	if(Input.CameraChangeType()){
		if(status == CAMERA_STATIC){
			SetDynamic();
		}else{
			SetStatic();
		}
	}
	if(status == CAMERA_STATIC){
		if(Game.GetStatus() == game){
			float camSpeed = 20.0f;
			if(Input.CameraForward()){
				if(!positionFrozen) position.z += camSpeed * FPSCounter.GetElapsedTime();
				lookAt.z += camSpeed * FPSCounter.GetElapsedTime();
			}
			if(Input.CameraBack()){
				if(!positionFrozen) position.z -= camSpeed * FPSCounter.GetElapsedTime();
				lookAt.z -= camSpeed * FPSCounter.GetElapsedTime();
			}
			if(Input.CameraLeft()){
				if(!positionFrozen) position.x -= camSpeed * FPSCounter.GetElapsedTime();
				lookAt.x -= camSpeed * FPSCounter.GetElapsedTime();
			}
			if(Input.CameraRight()){
				if(!positionFrozen) position.x += camSpeed * FPSCounter.GetElapsedTime();
				lookAt.x += camSpeed * FPSCounter.GetElapsedTime();
			}
			if(Input.CameraDown()){
				if(!positionFrozen) position.y -= camSpeed * FPSCounter.GetElapsedTime();
				lookAt.y -= camSpeed * FPSCounter.GetElapsedTime();
			}
			if(Input.CameraUp()){
				if(!positionFrozen) position.y += camSpeed * FPSCounter.GetElapsedTime();
				lookAt.y += camSpeed * FPSCounter.GetElapsedTime();
			}
		}
		UpdateViewMatrix();
		BuildFrustum();
	}else{
		if(Game.GetStatus() == game || Game.GetStatus() == softPause){
			if(animationRotation != 0.0f){
				//automatyczna rotacja kamery
				rotation += animationRotation * FPSCounter.GetElapsedTime();
			}else{
				if(Game.GetStatus() == game){
					//kamera sterowana myszka
					float rotationSpeed = 0.2f * FPSCounter.GetElapsedTime();
					float moveSpeed = 0.38f * FPSCounter.GetElapsedTime();

					rotation += Input.GetMouseState()->lX * rotationSpeed;

					if(Input.mouseButton[0]){
						distanceUp += Input.GetMouseState()->lY * moveSpeed;
						if(distanceUp < 1.0f) distanceUp = 1.0f;
						else if(distanceUp > 8.0f) distanceUp = 8.0f;
						distance += Input.GetMouseState()->lY * moveSpeed;
						if(distance < 6) distance = 6.0f;
						else if(distance > 13.0f) distance = 13.0f;
					}
				}
			}
		}
		UpdatePosition();
		UpdateViewMatrix();
		BuildFrustum();
	}
}
void CCamera::BuildFrustum(){
	// Left plane

	D3DXMATRIX CameraMatrix = GetMatrix();

	frustum[0].a = CameraMatrix._14 + CameraMatrix._11;
	frustum[0].b = CameraMatrix._24 + CameraMatrix._21;
	frustum[0].c = CameraMatrix._34 + CameraMatrix._31;
	frustum[0].d = CameraMatrix._44 + CameraMatrix._41;

	// Right plane
	frustum[1].a = CameraMatrix._14 - CameraMatrix._11;
	frustum[1].b = CameraMatrix._24 - CameraMatrix._21;
	frustum[1].c = CameraMatrix._34 - CameraMatrix._31;
	frustum[1].d = CameraMatrix._44 - CameraMatrix._41;

	// Top plane
	frustum[2].a = CameraMatrix._14 - CameraMatrix._12;
	frustum[2].b = CameraMatrix._24 - CameraMatrix._22;
	frustum[2].c = CameraMatrix._34 - CameraMatrix._32;
	frustum[2].d = CameraMatrix._44 - CameraMatrix._42;

	// Bottom plane
	frustum[3].a = CameraMatrix._14 + CameraMatrix._12;
	frustum[3].b = CameraMatrix._24 + CameraMatrix._22;
	frustum[3].c = CameraMatrix._34 + CameraMatrix._32;
	frustum[3].d = CameraMatrix._44 + CameraMatrix._42;

	// Near plane
	frustum[4].a = CameraMatrix._13;
	frustum[4].b = CameraMatrix._23;
	frustum[4].c = CameraMatrix._33;
	frustum[4].d = CameraMatrix._43;

	// Far plane
	frustum[5].a = CameraMatrix._14 - CameraMatrix._13;
	frustum[5].b = CameraMatrix._24 - CameraMatrix._23;
	frustum[5].c = CameraMatrix._34 - CameraMatrix._33;
	frustum[5].d = CameraMatrix._44 - CameraMatrix._43;

	// Normalize planes
	for ( int i = 0; i < 6; i++ ) D3DXPlaneNormalize( &frustum[i], &frustum[i] );
}
