#pragma once
#include "stdfx.h"
#include "Game.h"
#include <map>
#include <vector>
#include <string>
using std::string;
class CGuiMessage;
class CGuiButton;
class CGui{
public:
	CGui(){}
	CGui(const CGui &){}
	CGui& operator=(const CGui&){}
	~CGui(){}
public:
	static CGui& GetInstance(){
		static CGui inst;
		return inst;
	}
	bool Init();
	bool InitScreens();
	void Update(GAME_STATUS status);
	void Render(GAME_STATUS status);
	void Clear();
	void ClearScreens();
	void Reset(bool t);

	void SetMessage(string msg){message = msg;}
	string GetMessage(){return message;}
	
	LPD3DXSPRITE GetSprite(){ return sprite; }
	LPDIRECT3DTEXTURE9 GetButton(){ return button; }
	LPD3DXFONT GetMenuFont(){return mainMenuFont; }
	vector<CGuiButton*> mainMenuButtons;
	void SetCounter(unsigned int c);
	void SetStarCounter(unsigned int c);
private:
	string message;
	RECT messageRect;
	LPDIRECT3DTEXTURE9 messageBackground;
	int messageBackgroundX, messageBackgroundY;
	D3DXVECTOR3 messageBackgroundPos, messageBackgroundCen;

	LPD3DXSPRITE sprite;
	
	LPDIRECT3DTEXTURE9 screen1;
	LPDIRECT3DTEXTURE9 screen2;
	LPDIRECT3DTEXTURE9 instructionsScreen;
	LPDIRECT3DTEXTURE9 closingScreen;
	LPDIRECT3DTEXTURE9 mainmenuScreen;
	LPDIRECT3DTEXTURE9 pauseScreen;
	LPDIRECT3DTEXTURE9 loadingScreen;
	LPDIRECT3DTEXTURE9 errorScreen;
	LPDIRECT3DTEXTURE9 menuBackground;
	int menuBackgroundX, menuBackgroundY;
	D3DXVECTOR3 menuBackgroundPos, menuBackgroundCen;
	LPDIRECT3DTEXTURE9 button;
	int buttonSelect;
	LPD3DXFONT mainMenuFont;

	int counterValue1;
	int counterValue2;
	int counterValue3;
	int counterValue4;

	int starValue1;
	int starValue2;
	
	LPDIRECT3DTEXTURE9 timeImg;
	int timeImgX, timeImgY;
	D3DXVECTOR3 timeImgPos, timeImgCen;

	LPDIRECT3DTEXTURE9 starImg;
	int starImgX, starImgY;
	D3DXVECTOR3 starImgPos, starImgCen;

	LPDIRECT3DTEXTURE9 timeNumbers[10];
	/*LPDIRECT3DTEXTURE9 time1;
	LPDIRECT3DTEXTURE9 time2;
	LPDIRECT3DTEXTURE9 time3;
	LPDIRECT3DTEXTURE9 time4;
	LPDIRECT3DTEXTURE9 time5;
	LPDIRECT3DTEXTURE9 time6;
	LPDIRECT3DTEXTURE9 time7;
	LPDIRECT3DTEXTURE9 time8;
	LPDIRECT3DTEXTURE9 time9;
	LPDIRECT3DTEXTURE9 time0;*/

	int timeNumberX, timeNumberY;
	D3DXVECTOR3 timeNumer1Pos, timeNumer1Cen;
	D3DXVECTOR3 timeNumer2Pos, timeNumer2Cen;
	D3DXVECTOR3 timeNumer3Pos, timeNumer3Cen;
	D3DXVECTOR3 timeNumer4Pos, timeNumer4Cen;

	int starNumberX, starNumberY;
	D3DXVECTOR3 starNumer1Pos, starNumer1Cen;
	D3DXVECTOR3 starNumer2Pos, starNumer2Cen;
};

enum GuiButtonAction{
	GBA_START, GBA_RESUME, GBA_MANUAL, GBA_EXIT
};
enum GuiButtonState{
	GBS_NONE, GBS_HOVER
};
class CGuiButton{
public:
	CGuiButton(){action = GBA_START; state = GBS_NONE;}
	void Execute();
	void Render();
	void SetAction(GuiButtonAction a){action = a;}
	void SetText(string t){ text = t; }
	void SetCenter(D3DXVECTOR3 c){ center = c; }
	void SetPosition(D3DXVECTOR3 p){ position = p;}
	void SetRect(RECT r){ rct = r; }
	void SetState(GuiButtonState s){state = s;}
protected:
	string text;
	RECT rct;
	D3DXVECTOR3 position, center;
	GuiButtonAction action;
	GuiButtonState state;
};

#define Gui CGui::GetInstance()