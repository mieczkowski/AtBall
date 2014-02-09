#pragma once

#include "stdfx.h"

class CSkyBox{
	CSkyBox(){ skyboxTexture = 0; cube = 0; }
	CSkyBox(const CSkyBox &){}
	CSkyBox& operator=(const CSkyBox&){}
	~CSkyBox(){}

public:
	static CSkyBox& GetInstance(){
		static CSkyBox inst;
		return inst;
	}

	bool Init();
	void Render();
	void Clear(){ 
		SAFE_RELEASE(cube);
		SAFE_RELEASE(skyboxTexture);
	}
protected:
	LPDIRECT3DCUBETEXTURE9 skyboxTexture;
	LPD3DXMESH cube;
};
#define SkyBox CSkyBox::GetInstance()