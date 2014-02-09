#pragma once
#include "stdfx.h"
#include <iostream>
#include <sstream>
#include "Game.h"
using namespace std;
class CDirectx{
public:
	CDirectx();
	CDirectx(const CDirectx &){}
	CDirectx& operator=(const CDirectx&){}
	~CDirectx(){}
public:
	static CDirectx& GetInstance(){
		static CDirectx inst;
		return inst;
	}
	bool Init();
	void Clear();
	//bool Reset(void);
	bool Render(GAME_STATUS status);
	bool IsDeviceLost();
	LPDIRECT3DDEVICE9 GetDevice(){return device;}
	LPDIRECT3D9 GetD3D(){return d3d;}
	LPD3DXEFFECT GetEffect(){return *effect;}
	LPD3DXSPRITE GetSpriteDevice(){return sprite;}
	LPDIRECT3DVERTEXDECLARATION9 GetVertexDeclSimple(){return vertexDeclarationSimple;}
	LPDIRECT3DVERTEXDECLARATION9 GetVertexDeclSkyBox(){return vertexDeclarationSkyBox;}
	LPDIRECT3DVERTEXDECLARATION9 GetVertexDeclNormalMap(){return vertexDeclarationNormalMap;}
	D3DPRESENT_PARAMETERS GetPartams(){return pp;}
	D3DXHANDLE GetTechnique(){return technique;}
	D3DDISPLAYMODE GetDisplayMode(){return dm;}
	ostringstream& GetMessageBuffer();
	bool SetPresentParameters();
	void SetPostProcessingEffect(string e){postProcessingEffect = e;}
	void SetPostProcessingEnable(bool e){postProcessingEnable = e;}
	void OnLostDevice();
	void OnResetDevice();
private:
	LPD3DXEFFECT* effect;
	LPD3DXEFFECT simpleEffect;
	LPDIRECT3DVERTEXDECLARATION9 vertexDeclarationSimple;
	LPD3DXEFFECT skyBoxEffect;
	LPDIRECT3DVERTEXDECLARATION9 vertexDeclarationSkyBox;
	LPD3DXEFFECT normalMapEffect;
	LPDIRECT3DVERTEXDECLARATION9 vertexDeclarationNormalMap;
	LPD3DXEFFECT postEffect;
	LPDIRECT3DVERTEXDECLARATION9 vertexDeclarationPost;

	LPDIRECT3D9 d3d;
	LPDIRECT3DDEVICE9 device;
	
	LPD3DXSPRITE sprite;
	
	D3DPRESENT_PARAMETERS pp;
	D3DXHANDLE technique;
	D3DDISPLAYMODE dm;
	D3DCAPS9 caps;
	DWORD vertexProcessing;
	LPD3DXFONT font;
	ostringstream message;


	//TMP
	LPDIRECT3DSURFACE9 MainSurface;

	LPDIRECT3DSURFACE9 RenderSurface;
	LPDIRECT3DTEXTURE9 RenderTexture;

	string postProcessingEffect;
	bool postProcessingEnable;
};

#define DirectX CDirectx::GetInstance()