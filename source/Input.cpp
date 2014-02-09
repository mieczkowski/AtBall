#include "Input.h"
#include "Window.h"
#include "Logger.h"
#include "Directx.h"
#include "FPSCounter.h"
bool CInput::Init(void){
	HINSTANCE temp = Window.GetHInstance();

	if(DirectInput8Create(temp,DIRECTINPUT_VERSION,IID_IDirectInput8,(void**)&input,NULL)!=DI_OK){
		ELOG("InputMgr", "Init", "Failed to create Direct Input Device!");
		return false;
	}
	if(input->CreateDevice(GUID_SysKeyboard,&inputKeyboard,NULL)!=DI_OK){
		ELOG("InputMgr", "Init", "Failed to create keyboard Device!");
		return false;
	}

	if(input->CreateDevice(GUID_SysMouse,&inputMouse,NULL)!=DI_OK){
		ELOG("InputMgr", "Init", "Failed to create mouse Device!");
		return false;
	}

	if(inputKeyboard->SetDataFormat(&c_dfDIKeyboard)!=DI_OK){
		ELOG("InputMgr", "Init", "Failed to set keyboard data format!");
		return false;
	}

	if(inputMouse->SetDataFormat(&c_dfDIMouse)!=DI_OK){
		ELOG("InputMgr", "Init", "Failed to set mouse data format!");
		return false;
	}
	if(inputKeyboard->SetCooperativeLevel(Window.GetHWND(),DISCL_BACKGROUND | DISCL_NONEXCLUSIVE)!=DI_OK){
		ELOG("InputMgr", "Init", "Failed to set keyboard cooperative level!");
		return false;
	}
	if(inputMouse->SetCooperativeLevel(Window.GetHWND(),DISCL_BACKGROUND | DISCL_NONEXCLUSIVE)!=DI_OK){
		ELOG("InputMgr", "Init", "Failed to set mouse cooperative level!");
		return false;
	}
	mouseEvent = CreateEvent(NULL, FALSE, FALSE, NULL); 
	HRESULT tempResult = inputMouse->SetEventNotification(mouseEvent);

	if(tempResult!=DI_OK && tempResult!=DI_POLLEDDEVICE){
		ELOG("InputMgr", "Init", "Failed to set mouse event notification!");
		return false;
	}

	#define SAMPLE_BUFFER_SIZE 16 

	DIPROPDWORD dipdw; 
	dipdw.diph.dwSize = sizeof(DIPROPDWORD); 
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER); 
	dipdw.diph.dwObj = 0; 
	dipdw.diph.dwHow = DIPH_DEVICE; 
	dipdw.dwData = SAMPLE_BUFFER_SIZE; 

	tempResult=inputMouse->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);

	if(tempResult!=DI_OK && tempResult!=DI_POLLEDDEVICE){
		ELOG("InputMgr", "Init", "Failed to set mouse property!");
		return false;
	}
	ZeroMemory(&mouseState,sizeof(mouseState));
	tempResult = inputMouse->Acquire();
	if(tempResult!=DI_OK){
		if(tempResult==S_FALSE)
			ELOG("InputMgr", "Init", "The mouse device was already acquired!");
		else{
			ELOG("InputMgr", "Init", "Failed to acquire mouse device!");
			return false;
		}
	}
	tempResult = inputKeyboard->Acquire();
	if(tempResult!=DI_OK){
		if(tempResult==S_FALSE)
			ELOG("InputMgr", "Init", "The keyboard device was already acquired!");
		else{
			ELOG("InputMgr", "Init", "Failed to acquire keyboard device!");
			return false;
		}
	}
	return true;
}

void CInput::Clear(void){
	inputKeyboard->Unacquire();
	inputMouse->Unacquire();
	inputKeyboard->Release();
	inputMouse->Release();
	input->Release();
	return;
}

void CInput::Update(void){
	inputMouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&mouseState);
	inputKeyboard->GetDeviceState(sizeof(unsigned char[256]), (LPVOID)keyState);
	for (int i = 0; i < 4; i++){
		if(mouseState.rgbButtons[i] & 0x80) 
			mouseButton[i] = true; 
		else 
			mouseButton[i] = false;
	}
// 	DirectX.GetMessageBuffer().str(" ");
// 
// 	static LONG x = 0;
// 	static LONG y = 0;
// 	DirectX.GetMessageBuffer() << "FPS: " << FPSCounter.GetFPS() << endl;
// 	if(mouseState.lX != x){
// 		x = mouseState.lX;
// 	}
// 	DirectX.GetMessageBuffer() << "Mouse X: " << x << endl;
// 	if(mouseState.lY != y){
// 		y = mouseState.lY;
// 	}
// 	DirectX.GetMessageBuffer() << "Mouse Y: " << y << endl;
// 	if(mouseButton[0]){
// 		DirectX.GetMessageBuffer() << "Wcisniety 0!: " << mouseState.lZ << endl;
// 	}
	return;
}

bool* CInput::GetMouseButton(void){
	return mouseButton;
}
bool CInput::CameraChangeType(){
	if(KEYDOWN(keyState,DIK_F1)){
		return true;
	}
	return false;
}
bool CInput::CameraRotateLeft(){
	if(KEYDOWN(keyState,DIK_Q)){
		return true;
	}
	return false;
}
bool CInput::CameraRotateRight(){
	if(KEYDOWN(keyState,DIK_E)){
		return true;
	}
	return false;
}
bool CInput::CameraUp(){
	if(KEYDOWN(keyState,DIK_R)){
		return true;
	}
	return false;
}
bool CInput::CameraDown(){
	if(KEYDOWN(keyState,DIK_F)){
		return true;
	}
	return false;
}
bool CInput::CameraLeft(){
	if(KEYDOWN(keyState,DIK_A)){
		return true;
	}
	return false;
}
bool CInput::CameraRight(){
	if(KEYDOWN(keyState,DIK_D)){
		return true;
	}
	return false;
}
bool CInput::CameraForward(){
	if(KEYDOWN(keyState,DIK_W)){
		return true;
	}
	return false;
}
bool CInput::CameraBack(){
	if(KEYDOWN(keyState,DIK_S)){
		return true;
	}
	return false;
}
bool CInput::ArrowUp(){
	if(KEYDOWN(keyState,DIK_UP)){
		return true;
	}
	return false;
}
bool CInput::ArrowDown(){
	if(KEYDOWN(keyState,DIK_DOWN)){
		return true;
	}
	return false;
}
bool CInput::ArrowLeft(){
	if(KEYDOWN(keyState,DIK_LEFT)){
		return true;
	}
	return false;
}
bool CInput::ArrowRight(){
	if(KEYDOWN(keyState,DIK_RIGHT)){
		return true;
	}
	return false;
}
bool CInput::Space(){
	if(KEYDOWN(keyState,DIK_SPACE)){
		return true;
	}
	return false;
}
bool CInput::Pause(){
	if(KEYDOWN(keyState,DIK_P)){
		return true;
	}
	return false;
}
bool CInput::Esc(){
	if(KEYDOWN(keyState,DIK_ESCAPE)){
		return true;
	}
	return false;
}
bool CInput::Enter(){
	if(KEYDOWN(keyState,DIK_RETURN)){
		return true;
	}
	return false;
}
bool CInput::Reset(){
	if(KEYDOWN(keyState,DIK_F5)){
		return true;
	}
	return false;
}
