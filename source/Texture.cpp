#include "Texture.h"
#include "Logger.h"
#include "Directx.h"
using namespace std;
bool CTexture::Load(string _fileName){
	fileName = _fileName;
	if(D3DXCreateTextureFromFileEx(DirectX.GetDevice(),    // the device pointer
		fileName.c_str(),
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,    
		D3DX_FROM_FILE,
		NULL,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_FILTER_LINEAR, //D3DX_DEFAULT
		D3DX_FILTER_LINEAR,
		D3DCOLOR_XRGB(255, 0, 255),
		NULL,
		NULL,
		&image)	!= D3D_OK){
			ELOG("CTexture", "Set", string("Nie mo¿na by³o za³adowaæ tekstury! Nazwa: ") + fileName);
			return false;
	}
// 	if(D3DXCreateTextureFromFileA(DirectX.GetDevice(), fileName.c_str(), &image) != D3D_OK){
// 			ELOG("CTexture", "Set", string("Nie mozna bylo zaladowac tekstury! Nazwa: ") + fileName);
// 			return false;
// 	}
	return true;
}
void CTexture::Reload(){
	Clear();
	Load(fileName);
}
