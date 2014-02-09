#pragma once
#include "stdfx.h"
class CTexture
{
public:
	CTexture(){image = NULL;}
	~CTexture(){}
public:
	bool Load(string _fileName);
	void Reload();
	void Clear(){
		SAFE_RELEASE(image);
	}
	LPDIRECT3DTEXTURE9 GetImage(){return image;}
	string GetFilename(){return fileName;}
private:
	LPDIRECT3DTEXTURE9 image;
	string fileName;
};
