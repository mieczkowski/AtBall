#include "SkyBox.h"
#include "Camera.h"
#include "Logger.h"
#include "Directx.h"
#include "Script.h"

bool CSkyBox::Init(){
	if(D3DXCreateCubeTextureFromFile(
		DirectX.GetDevice(), 
		Script.GetStringVariable("config","skyboxTexture", "").c_str(), 
		&skyboxTexture) != D3D_OK){
			ELOG("CSkyBox","Init","Nie mozna zaladowac tekstury SkyBox'a!");
			return false;
	}
	if(D3DXCreateBox(DirectX.GetDevice(), 2.0f, 2.0f, 2.0f, &cube, NULL) != D3D_OK){
		ELOG("CSkyBox","Init","Nie mozna utworzyc modelu SkyBox'a!");
		return false;
	}

	LOG("CSkyBox","Init","Pomyœlnie zainicjowano SkyBox'a!");
	return true;
}
void CSkyBox::Render(){
	
	D3DXMATRIX translate;
	D3DXMatrixTranslation(&translate, Camera.GetPosition().x, Camera.GetPosition().y, Camera.GetPosition().z);
	D3DXMATRIX rotate;
	D3DXMatrixRotationYawPitchRoll(&rotate, -D3DX_PI/2, -D3DX_PI/2, 0.0f);

	DirectX.GetEffect()->SetMatrix("gWorld", &(rotate * translate));
	DirectX.GetEffect()->SetMatrix("gViewProj", &Camera.GetMatrix());
	//DirectX.GetEffect()->SetMatrix("Projection", &Camera.GetProjection());
	DirectX.GetEffect()->SetTexture("skybox", skyboxTexture );

	//DirectX.GetEffect()->SetVector("CameraPosition", &(D3DXVECTOR4(Camera.GetPosition().x,Camera.GetPosition().y,Camera.GetPosition().z,0.0f)));
	DirectX.GetEffect()->SetTexture("SkyBoxTexture",(skyboxTexture));
	DirectX.GetEffect()->CommitChanges();
	cube->DrawSubset(0);

}