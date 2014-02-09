#pragma once
#include "stdfx.h"
#include <dinput.h>

class CInput
{
public:
	CInput(){
		input=NULL;
		inputKeyboard=NULL;
		inputMouse=NULL;
		mouseEvent=NULL;
	}
	CInput(const CInput &){}
	CInput& operator=(const CInput&){}
	~CInput(){}

public:
	static CInput& GetInstance(){
		static CInput inst;
		return inst;
	}
	bool Init();
	void Update();
	void Clear();
	DIMOUSESTATE* GetMouseState(){return &mouseState;}
	unsigned char* GetKeyState(){return keyState;}
	bool* GetMouseButton();
	bool mouseButton[4];
private:
	
	LPDIRECTINPUT8 input;
	LPDIRECTINPUTDEVICE8 inputKeyboard;
	LPDIRECTINPUTDEVICE8 inputMouse;
	HANDLE mouseEvent; 
	DIMOUSESTATE mouseState;
	unsigned char keyState[256];

public:
	bool ButtonPressed(int num){
			if(num > 0 && num < 4) return mouseButton[num];
			else return false;
		}
	bool CameraChangeType();
	bool CameraRotateLeft();
	bool CameraRotateRight();
	bool CameraUp();
	bool CameraDown();
	bool CameraLeft();
	bool CameraRight();
	bool CameraForward();
	bool CameraBack();
	bool ArrowUp();
	bool ArrowDown();
	bool ArrowLeft();
	bool ArrowRight();
	bool Space();
	bool Pause();
	bool Esc();
	bool Enter();
	bool Reset();
};
#define Input CInput::GetInstance()