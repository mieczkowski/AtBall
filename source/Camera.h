#pragma once
#include "stdfx.h"
#include "Renderable.h"
#include "Logger.h"
#include "Directx.h"
using namespace std;
enum CameraStatus{CAMERA_STATIC,CAMERA_FOLLOWING};
class CCamera
{
public:
	CCamera();
	CCamera(const CCamera &){}
	CCamera& operator=(const CCamera&){}
	~CCamera(){}

public:
	static CCamera& GetInstance(){
		static CCamera inst;
		return inst;
	}
	void Init();
	void Update();


	void SetStatic();
	void SetDynamic();
	bool SetFollowedObject(string name);
	void UpdatePosition();
	D3DXVECTOR3 GetPosition(){ return position; }
	D3DXVECTOR3 GetLookAt(){ return lookAt; }
	D3DXPLANE* GetFrustum(){ return frustum; }
	CameraStatus GetStatus(){ return status; }

	float GetRotation(){ return rotation; }
	void SetRotation(float rot){rotation = D3DXToRadian(rot);}
	void EnableAnimation(float rot){animationRotation = rot;}
	void DisableAnimation(){animationRotation = 0.0f;}
	
	void FreezePosition(){positionFrozen = true;}
	void UnfreezePosition(){positionFrozen = false;}

	void SetDistance(float d){distance = d;}
	void SetDistanceUp(float d){distanceUp = d;}

	D3DXVECTOR3 GetDirection();
	D3DXMATRIX GetMatrix(){ return matView*matProjection; }
	D3DXMATRIX GetProjection(){ return matView; }
	D3DXMATRIX GetView(){ return matProjection; }
	string message;
	float length;

protected:
	void UpdateViewMatrix(){ D3DXMatrixLookAtLH(&matView,&position,&lookAt,&up); }
	void SetPerspective(){ D3DXMatrixPerspectiveFovLH(&matProjection, D3DXToRadian(viewAngle), (FLOAT)DirectX.GetDisplayMode().Width / (FLOAT) DirectX.GetDisplayMode().Height, nearplane, farplane); }
	void BuildFrustum();


	D3DXPLANE frustum[6];
	D3DXMATRIX matView;
	D3DXMATRIX matProjection;
	int viewAngle;
	float nearplane, farplane, distance, rotation, distanceUp;
	CameraStatus status;
	IRenderable *followedObject;
	bool positionChanged;
	D3DXVECTOR3 position, lookAt, up;
	D3DXVECTOR3 localPosition, localDirection;
	
	bool positionFrozen;
	float animationRotation;
};

#define Camera CCamera::GetInstance()
