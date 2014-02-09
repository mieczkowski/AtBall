#include "Window.h"
#include "Logger.h"
LRESULT CALLBACK CWindow::WindowEvenProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){
	switch(msg){
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		case WM_KEYDOWN:
// 			switch (wParam){
// 				case VK_ESCAPE:
// 				PostQuitMessage( 0 );
// 				break;
// 			}
			return 0;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

void CWindow::Hide(void){
	if(window){
		ShowWindow(window, SW_HIDE); 
		UpdateWindow(window);
	}
}

void CWindow::Show(void){
	if(window){
		ShowWindow(window, SW_SHOW); 
		UpdateWindow(window);
	}
}
bool CWindow::CreateWindowClass(void){
	ZeroMemory(&windowClass, sizeof(WNDCLASSEX));
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.hInstance = instance;
	windowClass.lpszClassName = TEXT("AtClass");
	windowClass.lpfnWndProc = &CWindow::WindowEvenProc;
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	windowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	if(fullscreen == 0) windowClass.hbrBackground = (HBRUSH) COLOR_WINDOW;
	windowClass.style = CS_HREDRAW | CS_VREDRAW;

	if(RegisterClassEx(&windowClass) == 0){
		return false;
	}
	return true;
}
bool CWindow::Create(void){
	if(instance == NULL){
		ELOG("WindowMgr","Create","Nie istnieje instancja okna");
		return false;
	}
	window = CreateWindowEx(NULL, 
		TEXT("AtClass"), 
		TEXT("AtBall"), 
		( fullscreen != 0 ) ? (WS_EX_TOPMOST | WS_POPUP) : (WS_OVERLAPPEDWINDOW),
		( fullscreen != 0 ) ? 0 : ((GetSystemMetrics(SM_CXSCREEN) - width) / 2), 
		( fullscreen != 0 ) ? 0 : ((GetSystemMetrics(SM_CYSCREEN) - height) / 2), 
		width, 
		height, 
		NULL, NULL, instance, NULL);

	if(window == NULL){
		ELOG("WindowMgr","Create","Nie udalo sie stworzyc okna");
		return false;
	}

	RECT rect = { 0, 0, width, height };
	AdjustWindowRect( &rect, GetWindowLong( window, GWL_STYLE ), FALSE );
	SetWindowPos( window, HWND_TOP, 0, 0, rect.right - rect.left, rect.bottom - rect.top, SWP_NOZORDER | SWP_NOMOVE ); 
	if(window == NULL){
		return false;
	}
	ShowCursor(false);
	return true;
}

bool CWindow::Init(HINSTANCE _instance, int _cmd, int _fullscreen, int screenSize){
	instance = _instance;
	cmd = _cmd;
	fullscreen = _fullscreen;
	width = 1280;
	height = 800;
	RECT rc;
	GetWindowRect(GetDesktopWindow(), &rc);
	if(fullscreen == 1){
		width = rc.right;
		height = rc.bottom;
	}else{
		switch(screenSize){
		case 1:
			width = 800;
			height = 600;
			break;
		case 2:
			width = 1024;
			height = 768;
			break;
		case 3:
			width = 1280;
			height = 800;
			break;
		case 4:
			width = 1280;
			height = 1024;
			break;
		case 5:
			width = 1440;
			height = 900;
			break;
		case 6:
			width = 1680;
			height = 1050;
			break;
		case 7:
			width = 1920;
			height = 1200;
			break;
		}
	}
	if(!CreateWindowClass()){
		ELOG("CWindow", "Init", "Nie mozna stworzyc klasy okna!");
		return false;
	}
	if(!Create()){
		ELOG("CWindow", "Init", "Nie mozna stworzyc okna!");
		return false;
	}

	LOG("CWindow", "Init", "Pomyslnie zainicjowano okno!");
	return true;
}
