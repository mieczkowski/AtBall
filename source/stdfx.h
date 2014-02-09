#pragma once

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#define DIRECTINPUT_VERSION 0x0800

#define SAFE_RELEASE(x) if( x ) { (x)->Release(); (x) = NULL; }
#define SAFE_DELETE(x) if( x ) { delete(x); (x) = NULL; }
#define SAFE_DELETE_ARRAY(x) if( x ) { delete [] (x); (x) = NULL; }
#define D3D_DEBUG_INFO
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEYDOWN(name, key) (name[key] & 0x80)


#include <windows.h>
#include <windowsx.h>
#include <d3d9.h>
#include <d3dx9.h>

#include <string>
using namespace std;

#pragma comment(lib, "lua5.1.lib")
#pragma comment(lib, "irrKlang.lib")
#pragma comment(lib, "DxErr.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "PhysXLoader.lib")
#pragma comment(lib, "PhysXCooking.lib")
#pragma comment(lib, "NxCharacter.lib")

