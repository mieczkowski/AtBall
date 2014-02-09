#include "Directx.h"
#include "Logger.h"
#include "Window.h"
#include "FPSCounter.h"
#include "Scene.h"
#include "SkyBox.h"
#include "Renderable.h"
#include "Gui.h"
#include "Camera.h"
struct Vertex
{
	float x, y, z;
	float tu, tv;
};
LPDIRECT3DVERTEXBUFFER9 g_pFullScreemVertexBuffer = NULL;
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_TEX1)
Vertex g_quadVertices[] =
{
	{-1.0f, 1.0f, 0.0f,  0.0f,0.0f },
	{ 1.0f, 1.0f, 0.0f,  1.0f,0.0f },
	{-1.0f,-1.0f, 0.0f,  0.0f,1.0f },
	{ 1.0f,-1.0f, 0.0f,  1.0f,1.0f }
};
CDirectx::CDirectx(){
	effect=NULL;
	simpleEffect = NULL;
	skyBoxEffect = NULL;
	normalMapEffect = NULL;
	font=NULL;
	d3d = NULL;
	device = NULL;
	sprite = NULL;
	postProcessingEffect = "Clean";
	vertexDeclarationSimple = NULL;
	technique = NULL;
	postProcessingEnable = true;
}
bool CDirectx::Init(){
	if(!(d3d=Direct3DCreate9(D3D_SDK_VERSION))){
		ELOG("CDirectx", "Init", "Nie udalo sie zainicjowaæ obiektu DirectX.");
		return false;
	}
	if(FAILED(d3d->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &dm))){
		ELOG("CDirectx", "Init", "Nie udalo sie pobrac AdapterDisplayMode.");
		return false;
	}
	if(FAILED(d3d->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps))){
		ELOG("CDirectx", "Init", "Nie udalo sie pobrac DeviceCaps.");
		return false;
	}
	vertexProcessing = 0;
	if (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT){
		vertexProcessing = D3DCREATE_HARDWARE_VERTEXPROCESSING;
		if (caps.DevCaps & D3DDEVCAPS_PUREDEVICE){
			vertexProcessing |= D3DCREATE_PUREDEVICE;
		}
	}else{
		vertexProcessing = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}

	if(SetPresentParameters() == false) return false;

	if(FAILED(d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, 
		Window.GetHWND(), vertexProcessing, &pp, &device))){
		ELOG("CDirectx", "Init", "Nie udalo sie utworzyc urzadzenia DirectX.");
		return false;
	}

	LPD3DXBUFFER pErrorMsgs = NULL;
	HRESULT hr = D3DXCreateEffectFromFile(device, "media/shaders/shader.fx", 0,0,0,0,&simpleEffect, &pErrorMsgs);

	if(FAILED(hr)){
		if(hr == D3DERR_INVALIDCALL) ELOG("CDirectx", "Init", 
			"Nie udalo sie skompilowac pliku shadera (simple). (The method call is invalid. For example, a method's parameter may have an invalid value.)");
		else if(hr == D3DXERR_INVALIDDATA) ELOG("CDirectx", "Init", "Nie udalo sie skompilowac pliku shadera (simple). (The data is invalid.)");
		else if(hr == E_OUTOFMEMORY) ELOG("CDirectx", "Init", "Nie udalo sie skompilowac pliku shadera (simple). (Could not allocate sufficient memory to complete the call.)");
		else ELOG("CDirectx", "Init", "Nie udalo sie skompilowac pliku shadera (simple). (nieznany blad)");
		SAFE_RELEASE(pErrorMsgs);
		return false;
	} 

	hr = D3DXCreateEffectFromFile(device, "media/shaders/skybox.fx", 0,0,0,0,&skyBoxEffect, &pErrorMsgs);
	if(FAILED(hr)){
		if(hr == D3DERR_INVALIDCALL) ELOG("CDirectx", "Init", 
			"Nie udalo sie skompilowac pliku shadera (skybox). (The method call is invalid. For example, a method's parameter may have an invalid value.)");
		else if(hr == D3DXERR_INVALIDDATA) ELOG("CDirectx", "Init", "Nie udalo sie skompilowac pliku shadera (skybox). (The data is invalid.)");
		else if(hr == E_OUTOFMEMORY) ELOG("CDirectx", "Init", "Nie udalo sie skompilowac pliku shadera (skybox). (Could not allocate sufficient memory to complete the call.)");
		else ELOG("CDirectx", "Init", "Nie udalo sie skompilowac pliku shadera (skybox). (nieznany blad)");
		SAFE_RELEASE(pErrorMsgs);
		return false;
	} 

	hr = D3DXCreateEffectFromFile(device, "media/shaders/normalMap.fx", 0,0,0,0,&normalMapEffect, &pErrorMsgs);
	if(FAILED(hr)){
		if(hr == D3DERR_INVALIDCALL) ELOG("CDirectx", "Init", 
			"Nie udalo sie skompilowac pliku shadera (normalMap). (The method call is invalid. For example, a method's parameter may have an invalid value.)");
		else if(hr == D3DXERR_INVALIDDATA) ELOG("CDirectx", "Init", "Nie udalo sie skompilowac pliku shadera (normalMap). (The data is invalid.)");
		else if(hr == E_OUTOFMEMORY) ELOG("CDirectx", "Init", "Nie udalo sie skompilowac pliku shadera (normalMap). (Could not allocate sufficient memory to complete the call.)");
		else ELOG("CDirectx", "Init", "Nie udalo sie skompilowac pliku shadera (normalMap). (nieznany blad)");
		SAFE_RELEASE(pErrorMsgs);
		return false;
	}

	hr = D3DXCreateEffectFromFile(device, "media/shaders/post.fx", 0,0,0,0,&postEffect, &pErrorMsgs);
	if(FAILED(hr)){
		if(hr == D3DERR_INVALIDCALL) ELOG("CDirectx", "Init", 
			"Nie udalo sie skompilowac pliku shadera (post). (The method call is invalid. For example, a method's parameter may have an invalid value.)");
		else if(hr == D3DXERR_INVALIDDATA) ELOG("CDirectx", "Init", "Nie udalo sie skompilowac pliku shadera (post). (The data is invalid.)");
		else if(hr == E_OUTOFMEMORY) ELOG("CDirectx", "Init", "Nie udalo sie skompilowac pliku shadera (post). (Could not allocate sufficient memory to complete the call.)");
		else ELOG("CDirectx", "Init", "Nie udalo sie skompilowac pliku shadera (post). (nieznany blad)");
		SAFE_RELEASE(pErrorMsgs);
		return false;
	}

	SAFE_RELEASE(pErrorMsgs);


	D3DVERTEXELEMENT9 decl[] = 
	{
		{ 0, 0  * sizeof(float),D3DDECLTYPE_FLOAT3,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },  // pos
		{ 0, 3  * sizeof(float),D3DDECLTYPE_FLOAT3,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,   0 },  // normal
		{ 0, 6  * sizeof(float),D3DDECLTYPE_FLOAT2,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0 },  // tex0
		D3DDECL_END()
	};

	device->CreateVertexDeclaration(decl, &vertexDeclarationSimple);

	D3DVERTEXELEMENT9 decl2[] =
	{
		{0,0, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
		{0, 3  * sizeof(float),D3DDECLTYPE_FLOAT3,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,   0},
		D3DDECL_END()
	};
	device->CreateVertexDeclaration( decl, &vertexDeclarationSkyBox );

	D3DVERTEXELEMENT9 decl3[] = 
	{
		{0,0, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
		{0,16, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0},
		{0,28, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
		{0,36, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TANGENT, 0},
		{0,48, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BINORMAL, 0},
		D3DDECL_END()
	};
	device->CreateVertexDeclaration( decl, &vertexDeclarationNormalMap );

	D3DVERTEXELEMENT9 decl4[] =
	{
		{0,0, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
		{0, 3  * sizeof(float),D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,   0},
		D3DDECL_END()
	};
	
	device->CreateVertexDeclaration( decl, &vertexDeclarationPost );
	//TMP
	if(postProcessingEnable){
		device->CreateTexture(Window.GetWidth(), Window.GetHeight(), 1, 
			D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &RenderTexture, NULL);

		device->GetRenderTarget(0, &MainSurface);
		RenderTexture->GetSurfaceLevel(0, &RenderSurface);
		device->CreateVertexBuffer( 4*sizeof(Vertex), D3DUSAGE_WRITEONLY, 
			D3DFVF_CUSTOMVERTEX, D3DPOOL_MANAGED, 
			&g_pFullScreemVertexBuffer, NULL );

		void *pVertices = NULL;

		g_pFullScreemVertexBuffer->Lock( 0, sizeof(g_quadVertices), (void**)&pVertices, 0 );
		memcpy( pVertices, g_quadVertices, sizeof(g_quadVertices) );
		g_pFullScreemVertexBuffer->Unlock();
	}	
	LOG("CDirectx", "Init", "Pomyslnie zainicjowano DirectX!");
	return true;
}

void CDirectx::Clear(){
	LOG("CDirectx", "Clear", "Czyszczenie obiektu!");
	if(postProcessingEnable){
		SAFE_RELEASE(RenderSurface); //
		SAFE_RELEASE(RenderTexture); //
	}	
	SAFE_RELEASE(postEffect);
	SAFE_RELEASE(simpleEffect);
	SAFE_RELEASE(skyBoxEffect);
	SAFE_RELEASE(normalMapEffect);
	SAFE_RELEASE(vertexDeclarationSimple);
	SAFE_RELEASE(device);
	SAFE_RELEASE(d3d);
	return;
}
ostringstream& CDirectx::GetMessageBuffer(){
	return message;
}
bool CDirectx::Render(GAME_STATUS status){
	if(!device){
		ELOG("CDirectx", "Render", "Urzadzenie nie istnieje - przerywam rendering.");
		return false;
	}
	if(IsDeviceLost() == true){
		return true;
	}
	if(postProcessingEnable){
		device->GetRenderTarget(0, &MainSurface);
		RenderTexture->GetSurfaceLevel(0, &RenderSurface);

		device->SetRenderTarget(0, RenderSurface);
	}
	
	device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	device->BeginScene();

	switch(status)
	{
	case game:
		{
			D3DXHANDLE hTech = 0;
			UINT uPasses;
			
			/*
				Render SKYBOXA
			*/
			effect = &skyBoxEffect;
			device->SetVertexDeclaration(vertexDeclarationSkyBox);
			hTech = DirectX.GetEffect()->GetTechniqueByName("SkyBox");
			DirectX.GetEffect()->SetTechnique(hTech);
			if (SUCCEEDED(DirectX.GetEffect()->Begin(&uPasses, D3DXFX_DONOTSAVESTATE))){  
				for (UINT uPass = 0; uPass < uPasses; uPass++){
					DirectX.GetEffect()->BeginPass(uPass);
					SkyBox.Render();
					DirectX.GetEffect()->EndPass();
				}
			}
			
			/*
				Renderowanie zwyk³ych modeli z tekstur¹
			*/

			effect = &simpleEffect;
			device->SetVertexDeclaration(vertexDeclarationSimple);
			hTech = DirectX.GetEffect()->GetTechniqueByName("Simple");
			DirectX.GetEffect()->SetTechnique(hTech);
			if (SUCCEEDED(DirectX.GetEffect()->Begin(&uPasses, D3DXFX_DONOTSAVESTATE))){  
				for (UINT uPass = 0; uPass < uPasses; uPass++){
					DirectX.GetEffect()->BeginPass(uPass);
					Scene.Render(RST_SIMPLE);
					DirectX.GetEffect()->EndPass();					
				}
			}

			DirectX.GetEffect()->End();

			/*
			Renderowanie zwyk³ych modeli z normal mapa
			*/

			effect = &normalMapEffect;
			device->SetVertexDeclaration(vertexDeclarationNormalMap);
			hTech = DirectX.GetEffect()->GetTechniqueByName("NormalMap");
			DirectX.GetEffect()->SetTechnique(hTech);
			if (SUCCEEDED(DirectX.GetEffect()->Begin(&uPasses, D3DXFX_DONOTSAVESTATE))){  
				for (UINT uPass = 0; uPass < uPasses; uPass++){
					DirectX.GetEffect()->BeginPass(uPass);
					Scene.Render(RST_NORMALMAP);
					DirectX.GetEffect()->EndPass();
				}
			}

			DirectX.GetEffect()->End();
			
			if(!postProcessingEnable) Gui.Render(status);
		}
			break;
	default:
		if(!postProcessingEnable) Gui.Render(status);
		break;
	}
	if(postProcessingEnable) device->SetRenderTarget(0, MainSurface); //
	device->EndScene();
	if(postProcessingEnable){
		device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
		device->BeginScene();

		D3DXHANDLE hTech = 0;
		UINT uPasses;
		effect = &postEffect;
		//device->SetVertexDeclaration(vertexDeclarationPost);
		//device->SetFVF( D3DFVF_CUSTOMVERTEX );
		hTech = DirectX.GetEffect()->GetTechniqueByName(postProcessingEffect.c_str());
		DirectX.GetEffect()->SetTechnique(hTech);
		if (SUCCEEDED(DirectX.GetEffect()->Begin(&uPasses, D3DXFX_DONOTSAVESTATE))){  
			for (UINT uPass = 0; uPass < uPasses; uPass++){
				DirectX.GetEffect()->BeginPass(uPass);
				DirectX.GetEffect()->SetTexture( "ScreenTexture", RenderTexture );
				//DirectX.GetEffect()->SetMatrix( "Projection", &(Camera.GetProjection()) );
				//DirectX.GetEffect()->SetMatrix( "View", &matView );
				device->SetStreamSource( 0, g_pFullScreemVertexBuffer, 0, sizeof(Vertex) );
				device->SetFVF( D3DFVF_CUSTOMVERTEX );
				device->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2 );
				DirectX.GetEffect()->EndPass();					
			}
			DirectX.GetEffect()->End();
			Gui.Render(status);
		}
		device->EndScene();
	}
	
	device->Present(0,0,0,0);
	 
//D3DXSaveSurfaceToFile("imageSurf.jpg",D3DXIFF_JPG,RenderSurface,NULL,NULL);
	return true;
}
void CDirectx::OnLostDevice(){
	Gui.Reset(false);
//  	SAFE_RELEASE(RenderTexture);
//  	RenderTexture = 0;
//  	SAFE_RELEASE(RenderSurface);
//  	SAFE_RELEASE(MainSurface);
}
void CDirectx::OnResetDevice(){
// 	ELOGEX("RESET DEVICE");
// 	if(FAILED(device->CreateTexture(Window.GetWidth(), Window.GetHeight(), 1, 
// 		D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &RenderTexture, NULL))){
// 		ELOGEX("TEXTURA NIE OK");
// 	}
// 	
// 	RenderTexture->GetSurfaceLevel(0, &RenderSurface);
// 	HRESULT x = device->GetRenderTarget(0, &MainSurface);
// 	ELOGEX("MAIN SURFACE");
// 	x = 
// 	ELOGEX("RENDER SURFACE");
// 	device->CreateVertexBuffer( 4*sizeof(Vertex), D3DUSAGE_WRITEONLY, 
// 		D3DFVF_CUSTOMVERTEX, D3DPOOL_MANAGED, 
// 		&g_pFullScreemVertexBuffer, NULL );
// 	ELOGEX("VERTEX BUFFER");
// 	void *pVertices = NULL;
// 
// 	g_pFullScreemVertexBuffer->Lock( 0, sizeof(g_quadVertices), (void**)&pVertices, 0 );
// 	ELOGEX("VERTEX BUFFER LOCK");
// 	memcpy( pVertices, g_quadVertices, sizeof(g_quadVertices) );
// 	ELOGEX("VERTEX BUFFER COPY");
// 	g_pFullScreemVertexBuffer->Unlock();
// 	ELOGEX("VERTEX BUFFER UNLOCK");
	Gui.Reset(true);
}
bool CDirectx::IsDeviceLost(){
	HRESULT lostResult = GetDevice()->TestCooperativeLevel();
	if(FAILED(lostResult)){
		if(lostResult == D3DERR_DEVICELOST){
			//urzadzenie dalej stracone, czekac..
			Sleep(50);
			return true;
		}else{
			if(SetPresentParameters()){
					OnLostDevice();
				if(device->Reset(&pp) == D3DERR_DEVICELOST){
					Sleep(1000);
					return true;
				}else{
					OnResetDevice();
					return false;
				}
			}else{
				ELOG("CDirectx", "IsDeviceLost", "Nie udalo sie ustawic PresentParameters po utracie urzadzenia.");
				return true;
			}
		}
	}
	return false;
}

bool CDirectx::SetPresentParameters(){
	ZeroMemory(&pp,sizeof(pp));
	D3DFORMAT adapterFormat = (Window.IsWindowed()) ? dm.Format : D3DFMT_X8R8G8B8;
	if (SUCCEEDED( d3d->CheckDeviceFormat( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, 
		adapterFormat, D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_SURFACE, D3DFMT_D24S8 ) ) ){
			pp.AutoDepthStencilFormat = D3DFMT_D24S8;
	}
	else if ( SUCCEEDED( d3d->CheckDeviceFormat( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, adapterFormat, 
		D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_SURFACE, D3DFMT_D24X8 ) ) ){
			pp.AutoDepthStencilFormat = D3DFMT_D24X8;
	}
	else if ( SUCCEEDED( d3d->CheckDeviceFormat( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, adapterFormat, 
		D3DUSAGE_DEPTHSTENCIL, D3DRTYPE_SURFACE, D3DFMT_D16 ) ) ){
			pp.AutoDepthStencilFormat = D3DFMT_D16;
	}else{
		ELOG("CDirectx", "SetPresentParameters", "Nie udalo sie ustawic AutoDepthStencilFormat.");
		return false;
	}

	pp.BackBufferWidth = (Window.IsWindowed()) ? 0 : dm.Width;
	pp.BackBufferHeight = (Window.IsWindowed()) ? 0 : dm.Height;
	pp.BackBufferCount = 1;
	pp.Windowed = Window.IsWindowed();						
	pp.BackBufferFormat = adapterFormat;   
	pp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	pp.EnableAutoDepthStencil = true;
	//pp.AutoDepthStencilFormat = D3DFMT_D16;
	pp.Flags = D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL;
	pp.FullScreen_RefreshRateInHz = (Window.IsWindowed()) ? 0 : dm.RefreshRate;
	pp.hDeviceWindow = Window.GetHWND();

	return true;
}

