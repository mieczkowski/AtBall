#pragma once
#include "stdfx.h"

class CWindow{
public:
	CWindow(void){}
	CWindow(const CWindow &){}
	CWindow& operator=(const CWindow&){}
	~CWindow(void){}

public :
	static CWindow& GetInstance(){
		static CWindow inst;
		return inst;
	}
	HWND GetHWND(){ return window; }
	HINSTANCE GetHInstance(){ return instance; }
	bool IsWindowed(){ if(fullscreen) return false; else return true; }
	int GetWidth(){	return width; }
	int GetHeight(){ return height;	}

	bool Init(HINSTANCE _instance, int _cmd, int _fullscreen, int screenSize);
	bool CreateWindowClass();
	bool Create();
	void Show();
	void Hide();

	void Clear(void){}

private:
	static LRESULT CALLBACK WindowEvenProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	HWND window;
	MSG msg;
	WNDCLASSEX windowClass;
	HINSTANCE instance;
	int width;
	int height;
	WINDOWPLACEMENT windowPlacement;
	int cmd;
	int fullscreen;
};

#define Window CWindow::GetInstance()