#include "Gui.h"
#include "Directx.h"
#include "Game.h"
#include "Logger.h"
#include "FPSCounter.h"
#include "Window.h"
#include "Input.h"
#include "Timer.h"
#include "Script.h"
bool CGui::Init(){
	if(D3DXCreateSprite(DirectX.GetDevice(), &sprite)!=S_OK){
		ELOG("CGui", "Init", "Nie udalo sie utworzyc obiektu Sprite.");
		return false;
	}
	if(D3DXCreateFont(DirectX.GetDevice(), 20, 0, FW_ULTRABOLD, 0, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, 
		ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Verdana", &mainMenuFont )!=S_OK){//(LPCWSTR)
			ELOG("CDirectx", "Init", "Nie udalo sie utworzyc czcionki.");
			return false;
	}
	message = "";
	starValue1 = 0;
	starValue2 = 0;
	counterValue1 = 0;
	counterValue2 = 0;
	counterValue3 = 0;
	counterValue4 = 0;
	return InitScreens();
}
bool CGui::InitScreens(){
	if(D3DXCreateTextureFromFileEx(DirectX.GetDevice(),  "media/textures/gui/screen1.png", 
		Window.GetWidth(),  Window.GetHeight(), D3DX_DEFAULT,  NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,  D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT, D3DCOLOR_XRGB(255, 0, 255), NULL,  NULL, &screen1)!=S_OK){
			ELOG("CGui", "InitScreens", "Nie udalo sie zaladowac screen1.");
			return false;
	}
	if(D3DXCreateTextureFromFileEx(DirectX.GetDevice(),  "media/textures/gui/screen2.jpg", 
		Window.GetWidth(),  Window.GetHeight(), D3DX_DEFAULT,  NULL,  D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,  D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,  D3DCOLOR_XRGB(255, 0, 255), NULL,  NULL, &screen2)!=S_OK){
			ELOG("CGui", "InitScreens", "Nie udalo sie zaladowac screen2.");
			return false;
	}
	if(D3DXCreateTextureFromFileEx(DirectX.GetDevice(),  "media/textures/gui/instructions.jpg", 
		Window.GetWidth(),  Window.GetHeight(), D3DX_DEFAULT,  NULL,  D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,  D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,  D3DCOLOR_XRGB(255, 0, 255), NULL,  NULL, &instructionsScreen)!=S_OK){
			ELOG("CGui", "InitScreens", "Nie udalo sie zaladowac instructionsScreen.");
			return false;
	}
	if(D3DXCreateTextureFromFileEx(DirectX.GetDevice(),  "media/textures/gui/closing.jpg", 
		Window.GetWidth(),  Window.GetHeight(), D3DX_DEFAULT,  NULL,  D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,  D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,  D3DCOLOR_XRGB(255, 0, 255), NULL,  NULL, &closingScreen)!=S_OK){
			ELOG("CGui", "InitScreens", "Nie udalo sie zaladowac closingScreen.");
			return false;
	}
	if(D3DXCreateTextureFromFileEx(DirectX.GetDevice(),  "media/textures/gui/mainmenu.jpg", 
		Window.GetWidth(),  Window.GetHeight(), D3DX_DEFAULT,  NULL,  D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,  D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,  D3DCOLOR_XRGB(255, 0, 255), NULL,  NULL, &mainmenuScreen)!=S_OK){
			ELOG("CGui", "InitScreens", "Nie udalo sie zaladowac mainmenu.");
			return false;
	}
	if(D3DXCreateTextureFromFileEx(DirectX.GetDevice(),  "media/textures/gui/pause.jpg", 
		Window.GetWidth(),  Window.GetHeight(), D3DX_DEFAULT,  NULL,  D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,  D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,  D3DCOLOR_XRGB(255, 0, 255), NULL,  NULL, &pauseScreen)!=S_OK){
			ELOG("CGui", "InitScreens", "Nie udalo sie zaladowac pauseScreen.");
			return false;
	}
	if(D3DXCreateTextureFromFileEx(DirectX.GetDevice(),  "media/textures/gui/loading.jpg", 
		Window.GetWidth(),  Window.GetHeight(), D3DX_DEFAULT,  NULL,  D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,  D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,  D3DCOLOR_XRGB(255, 0, 255), NULL,  NULL, &loadingScreen)!=S_OK){
			ELOG("CGui", "InitScreens", "Nie udalo sie zaladowac pauseScreen.");
			return false;
	}
	if(D3DXCreateTextureFromFileEx(DirectX.GetDevice(),  "media/textures/gui/error.jpg", 
		Window.GetWidth(),  Window.GetHeight(), D3DX_DEFAULT,  NULL,  D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,  D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,  D3DCOLOR_XRGB(255, 0, 255), NULL,  NULL, &errorScreen)!=S_OK){
			ELOG("CGui", "InitScreens", "Nie udalo sie zaladowac error.");
			return false;
	}
	
	menuBackgroundX = (900 * Window.GetWidth()) / 1920;
	menuBackgroundY = (774 * Window.GetHeight()) / 1200;
	menuBackgroundPos = D3DXVECTOR3(Window.GetWidth()/2,Window.GetHeight()/2,0.0f);
	menuBackgroundCen = D3DXVECTOR3(menuBackgroundX/2,menuBackgroundY/2,0.0f);
	if(D3DXCreateTextureFromFileEx(DirectX.GetDevice(),  "media/textures/gui/menuBackground.jpg", 
		menuBackgroundX, menuBackgroundY, D3DX_DEFAULT,  NULL,  D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,  D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,  D3DCOLOR_XRGB(255, 0, 255), NULL,  NULL, &menuBackground)!=S_OK){
			ELOG("CGui", "InitScreens", "Nie udalo sie zaladowac menuBackground.");
			return false;
	}
	
	int buttonX = (499 * Window.GetWidth()) / 1920;
	int buttonY = (59 * Window.GetHeight()) / 1200;
	if(D3DXCreateTextureFromFileEx(DirectX.GetDevice(),  "media/textures/gui/button.jpg", 
		buttonX, buttonY, D3DX_DEFAULT,  NULL,  D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,  D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,  D3DCOLOR_XRGB(255, 0, 255), NULL,  NULL, &button)!=S_OK){
			ELOG("CGui", "InitScreens", "Nie udalo sie zaladowac button.");
			return false;
	}
	
	int b1Y = (130 * Window.GetHeight()) / 1200;
	int b2Y = (0 * Window.GetHeight()) / 1200;
	//int b3Y = (150 * Window.GetHeight()) / 1200;

	RECT r1;
	int LeftTopX = (Window.GetWidth()/2) - buttonX/2;
	int LeftTopY = (Window.GetHeight()/2) - b1Y - buttonY/2;
	int RightBottomX = (Window.GetWidth()/2) + buttonX/2;
	int RightBottomY = (Window.GetHeight()/2) - b1Y + buttonY/2;
	SetRect(&r1, LeftTopX, LeftTopY, RightBottomX, RightBottomY);

	RECT r2;
	LeftTopX = (Window.GetWidth()/2) - buttonX/2;
	LeftTopY = (Window.GetHeight()/2) + b2Y - buttonY/2;
	RightBottomX = (Window.GetWidth()/2) + buttonX/2;
	RightBottomY = (Window.GetHeight()/2) + b2Y + buttonY/2;
	SetRect(&r2, LeftTopX, LeftTopY, RightBottomX, RightBottomY);

	RECT r3;
	LeftTopX = (Window.GetWidth()/2) - buttonX/2;
	LeftTopY = (Window.GetHeight()/2) + b1Y - buttonY/2;
	RightBottomX = (Window.GetWidth()/2) + buttonX/2;
	RightBottomY = (Window.GetHeight()/2)+ b1Y + buttonY/2;
	SetRect(&r3, LeftTopX, LeftTopY, RightBottomX, RightBottomY);

	buttonSelect = 0;
	CGuiButton *button1 = new CGuiButton;
	button1->SetState(GBS_HOVER);
	button1->SetAction(GBA_START);
	button1->SetText("START GRY");
	button1->SetCenter(D3DXVECTOR3(buttonX/2,buttonY/2,0.0f));
	button1->SetPosition(D3DXVECTOR3(Window.GetWidth()/2,(Window.GetHeight()/2) - b1Y, 0.0f));
	
	button1->SetRect(r1);

	mainMenuButtons.push_back(button1);
	CGuiButton *button2 = new CGuiButton;
	button2->SetAction(GBA_MANUAL);
	button2->SetText("Instrukcje");
	button2->SetCenter(D3DXVECTOR3(buttonX/2,buttonY/2,0.0f));
	button2->SetPosition(D3DXVECTOR3(Window.GetWidth()/2,(Window.GetHeight()/2) + b2Y, 0.0f));
	button2->SetRect(r2);
	mainMenuButtons.push_back(button2);

	CGuiButton *button3 = new CGuiButton;
	button3->SetAction(GBA_EXIT);
	button3->SetText("Koniec");
	button3->SetCenter(D3DXVECTOR3(buttonX/2,buttonY/2,0.0f));
	button3->SetPosition(D3DXVECTOR3(Window.GetWidth()/2,(Window.GetHeight()/2) + b1Y, 0.0f));
	button3->SetRect(r3);
	mainMenuButtons.push_back(button3);


	messageBackgroundX = (600 * Window.GetWidth()) / 1920;
	messageBackgroundY = (356 * Window.GetHeight()) / 1200;
	messageBackgroundPos = D3DXVECTOR3(Window.GetWidth()/2,Window.GetHeight()/2,0.0f);
	messageBackgroundCen = D3DXVECTOR3(messageBackgroundX/2,messageBackgroundY/2,0.0f);
	if(D3DXCreateTextureFromFileEx(DirectX.GetDevice(),  "media/textures/gui/windowBackground.jpg", 
		messageBackgroundX, messageBackgroundY, D3DX_DEFAULT,  NULL,  D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,  D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,  D3DCOLOR_XRGB(255, 0, 255), NULL,  NULL, &messageBackground)!=S_OK){
			ELOG("CGui", "InitScreens", "Nie udalo sie zaladowac messageBackground.");
			return false;
	}

	LeftTopX = (Window.GetWidth()/2) - messageBackgroundX/2;
	LeftTopY = (Window.GetHeight()/2) - messageBackgroundY/2;
	RightBottomX = (Window.GetWidth()/2) + messageBackgroundX/2;
	RightBottomY = (Window.GetHeight()/2) + messageBackgroundY/2;
	SetRect(&messageRect, LeftTopX, LeftTopY, RightBottomX, RightBottomY);


	
	timeNumberX = (50 * Window.GetWidth()) / 1920;
	timeNumberY = (68 * Window.GetHeight()) / 1200;

	if(D3DXCreateTextureFromFileEx(DirectX.GetDevice(),  "media/textures/gui/0.jpg", 
		timeNumberX, timeNumberY, D3DX_DEFAULT,  NULL,  D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,  D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,  D3DCOLOR_XRGB(255, 164, 0), NULL,  NULL, &timeNumbers[0])!=S_OK){
			ELOG("CGui", "InitScreens", "Nie udalo sie zaladowac numeru 0.");
			return false;
	}
	if(D3DXCreateTextureFromFileEx(DirectX.GetDevice(),  "media/textures/gui/1.jpg", 
		timeNumberX, timeNumberY, D3DX_DEFAULT,  NULL,  D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,  D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,  D3DCOLOR_XRGB(255, 164, 0), NULL,  NULL, &timeNumbers[1])!=S_OK){
			ELOG("CGui", "InitScreens", "Nie udalo sie zaladowac numeru 1.");
			return false;
	}
	if(D3DXCreateTextureFromFileEx(DirectX.GetDevice(),  "media/textures/gui/2.jpg", 
		timeNumberX, timeNumberY, D3DX_DEFAULT,  NULL,  D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,  D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,  D3DCOLOR_XRGB(255, 164, 0), NULL,  NULL, &timeNumbers[2])!=S_OK){
			ELOG("CGui", "InitScreens", "Nie udalo sie zaladowac numeru 2.");
			return false;
	}
	if(D3DXCreateTextureFromFileEx(DirectX.GetDevice(),  "media/textures/gui/3.jpg", 
		timeNumberX, timeNumberY, D3DX_DEFAULT,  NULL,  D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,  D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,  D3DCOLOR_XRGB(255, 164, 0), NULL,  NULL, &timeNumbers[3])!=S_OK){
			ELOG("CGui", "InitScreens", "Nie udalo sie zaladowac numeru 3.");
			return false;
	}
	if(D3DXCreateTextureFromFileEx(DirectX.GetDevice(),  "media/textures/gui/4.jpg", 
		timeNumberX, timeNumberY, D3DX_DEFAULT,  NULL,  D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,  D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,  D3DCOLOR_XRGB(255, 164, 0), NULL,  NULL, &timeNumbers[4])!=S_OK){
			ELOG("CGui", "InitScreens", "Nie udalo sie zaladowac numeru 4.");
			return false;
	}
	if(D3DXCreateTextureFromFileEx(DirectX.GetDevice(),  "media/textures/gui/5.jpg", 
		timeNumberX, timeNumberY, D3DX_DEFAULT,  NULL,  D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,  D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,  D3DCOLOR_XRGB(255, 164, 0), NULL,  NULL, &timeNumbers[5])!=S_OK){
			ELOG("CGui", "InitScreens", "Nie udalo sie zaladowac numeru 5.");
			return false;
	}
	if(D3DXCreateTextureFromFileEx(DirectX.GetDevice(),  "media/textures/gui/6.jpg", 
		timeNumberX, timeNumberY, D3DX_DEFAULT,  NULL,  D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,  D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,  D3DCOLOR_XRGB(255, 164, 0), NULL,  NULL, &timeNumbers[6])!=S_OK){
			ELOG("CGui", "InitScreens", "Nie udalo sie zaladowac numeru 6.");
			return false;
	}
	if(D3DXCreateTextureFromFileEx(DirectX.GetDevice(),  "media/textures/gui/7.jpg", 
		timeNumberX, timeNumberY, D3DX_DEFAULT,  NULL,  D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,  D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,  D3DCOLOR_XRGB(255, 164, 0), NULL,  NULL, &timeNumbers[7])!=S_OK){
			ELOG("CGui", "InitScreens", "Nie udalo sie zaladowac numeru 7.");
			return false;
	}
	if(D3DXCreateTextureFromFileEx(DirectX.GetDevice(),  "media/textures/gui/8.jpg", 
		timeNumberX, timeNumberY, D3DX_DEFAULT,  NULL,  D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,  D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,  D3DCOLOR_XRGB(255, 164, 0), NULL,  NULL, &timeNumbers[8])!=S_OK){
			ELOG("CGui", "InitScreens", "Nie udalo sie zaladowac numeru 8.");
			return false;
	}
	if(D3DXCreateTextureFromFileEx(DirectX.GetDevice(),  "media/textures/gui/9.jpg", 
		timeNumberX, timeNumberY, D3DX_DEFAULT,  NULL,  D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,  D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,  D3DCOLOR_XRGB(255, 164, 0), NULL,  NULL, &timeNumbers[9])!=S_OK){
			ELOG("CGui", "InitScreens", "Nie udalo sie zaladowac numeru 9.");
			return false;
	}

	timeImgX = (453 * Window.GetWidth()) / 1920;
	timeImgY = (98 * Window.GetHeight()) / 1200;
	timeImgPos = D3DXVECTOR3(timeImgX/2,Window.GetHeight() - timeImgY/2,0.0f);
	timeImgCen = D3DXVECTOR3(timeImgX/2,timeImgY/2,0.0f);
	if(D3DXCreateTextureFromFileEx(DirectX.GetDevice(),  "media/textures/gui/czas.jpg", 
		timeImgX, timeImgY, D3DX_DEFAULT,  NULL,  D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,  D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,  D3DCOLOR_XRGB(255, 255, 255), NULL,  NULL, &timeImg)!=S_OK){
			ELOG("CGui", "InitScreens", "Nie udalo sie zaladowac menuBackground.");
			return false;
	}
	float moveX = 0;
	moveX = (13 * Window.GetWidth()) / 1920;

	timeNumer1Pos = D3DXVECTOR3(timeImgX/2 + moveX,Window.GetHeight() - timeImgY/2,0.0f);
	timeNumer1Cen = D3DXVECTOR3(timeNumberX/2,timeNumberY/2,0.0f);

	moveX = (65 * Window.GetWidth()) / 1920;
	timeNumer2Pos = D3DXVECTOR3(timeImgX/2 + moveX,Window.GetHeight() - timeImgY/2,0.0f);
	timeNumer2Cen = D3DXVECTOR3(timeNumberX/2,timeNumberY/2,0.0f);

	moveX = (135 * Window.GetWidth()) / 1920;
	timeNumer3Pos = D3DXVECTOR3(timeImgX/2 + moveX,Window.GetHeight() - timeImgY/2,0.0f);
	timeNumer3Cen = D3DXVECTOR3(timeNumberX/2,timeNumberY/2,0.0f);

	moveX = (185 * Window.GetWidth()) / 1920;
	timeNumer4Pos = D3DXVECTOR3(timeImgX/2 + moveX,Window.GetHeight() - timeImgY/2,0.0f);
	timeNumer4Cen = D3DXVECTOR3(timeNumberX/2,timeNumberY/2,0.0f);


	starImgX = (247 * Window.GetWidth()) / 1920;
	starImgY = (108 * Window.GetHeight()) / 1200;
	starImgPos = D3DXVECTOR3(Window.GetWidth() - starImgX/2,Window.GetHeight() - starImgY/2,0.0f);
	starImgCen = D3DXVECTOR3(starImgX/2,starImgY/2,0.0f);
	if(D3DXCreateTextureFromFileEx(DirectX.GetDevice(),  "media/textures/gui/star.jpg", 
		starImgX, starImgY, D3DX_DEFAULT,  NULL,  D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,  D3DX_DEFAULT,    // no filtering
		D3DX_DEFAULT,  D3DCOLOR_XRGB(255, 255, 255), NULL,  NULL, &starImg)!=S_OK){
			ELOG("CGui", "InitScreens", "Nie udalo sie zaladowac star.");
			return false;
	}

	moveX = (15 * Window.GetWidth()) / 1920;

	starNumer1Pos = D3DXVECTOR3(Window.GetWidth() - starImgX/2 + moveX,Window.GetHeight() - starImgY/2,0.0f);
	starNumer1Cen = D3DXVECTOR3(timeNumberX/2,timeNumberY/2,0.0f);

	moveX = (75 * Window.GetWidth()) / 1920;
	starNumer2Pos = D3DXVECTOR3(Window.GetWidth() - starImgX/2 + moveX,Window.GetHeight() - starImgY/2,0.0f);
	starNumer2Cen = D3DXVECTOR3(timeNumberX/2,timeNumberY/2,0.0f);

	return true;
}
void CGui::Update(GAME_STATUS status){
	if(status == mainMenu){
		CTimer* timer = TimerMgr.GetTimer("SYSTEM GUITime");
		if(timer == NULL) {
			int prevButton = buttonSelect - 1;
			if(prevButton < 0) prevButton = mainMenuButtons.size() - 1;
			int nextButton = buttonSelect + 1;
			if(nextButton == mainMenuButtons.size()) nextButton = 0;
			if(Input.ArrowDown()){
				mainMenuButtons[buttonSelect]->SetState(GBS_NONE);
				mainMenuButtons[nextButton]->SetState(GBS_HOVER);
				buttonSelect = nextButton;
				CTimer* tmp = new CTimerSimple(0.1f);
				TimerMgr.AddTimer("SYSTEM GUITime", tmp);
				Script.CallFunction("config", "onMenuChange");
			}
			if(Input.ArrowUp()){
				mainMenuButtons[buttonSelect]->SetState(GBS_NONE);
				mainMenuButtons[prevButton]->SetState(GBS_HOVER);
				buttonSelect = prevButton;
				CTimer* tmp = new CTimerSimple(0.1f);
				TimerMgr.AddTimer("SYSTEM GUITime", tmp);
				Script.CallFunction("config", "onMenuChange");
			}
		}
		if(Input.Enter()){
			mainMenuButtons[buttonSelect]->Execute();
			Script.CallFunction("config", "onMenuEnter");
		}
	}	
}
void CGui::SetCounter(unsigned int c){
	int sekundy = c/1000;
	int minuty = sekundy / 60;
	sekundy = sekundy - minuty * 60;
	//string zero1 = ( sekundy < 10 ) ? "0":"";
	//string zero2 = ( minuty < 10 ) ? "0":"";
	counterValue1 = minuty / 10;
	counterValue2 = minuty % 10; 
	counterValue3 = sekundy / 10; 
	counterValue4 = sekundy % 10;
}
void CGui::SetStarCounter(unsigned int c){
	starValue1 = c / 10;
	starValue2 = c % 10;
}
void CGui::Render(GAME_STATUS status){
	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	switch(status){
		case start1:
			sprite->Draw(screen1, NULL, NULL,NULL, 0xFFFFFFFF);
			break;
		case start2:
			sprite->Draw(screen2, NULL, NULL,NULL, 0xFFFFFFFF);
			break;
		case mainMenu:
			sprite->Draw(mainmenuScreen, NULL, NULL,NULL, 0xFFFFFFFF);
			sprite->Draw(menuBackground, NULL, &menuBackgroundCen,&menuBackgroundPos, D3DCOLOR_ARGB(127, 255, 255, 255));
			for(vector<CGuiButton*>::size_type i = 0; i < mainMenuButtons.size(); i++){
				mainMenuButtons[i]->Render();
			}
			break;
		case pause:
			sprite->Draw(pauseScreen, NULL, NULL,NULL, 0xFFFFFFFF);
			break;
		case loading:
		case loading2:
			sprite->Draw(loadingScreen, NULL, NULL,NULL, 0xFFFFFFFF);
			break;
		case error:
			sprite->Draw(errorScreen, NULL, NULL,NULL, 0xFFFFFFFF);
			break;
		case instructions:
			sprite->Draw(instructionsScreen, NULL, NULL,NULL, 0xFFFFFFFF);
			break;
		case endGame:
			sprite->Draw(closingScreen, NULL, NULL,NULL, 0xFFFFFFFF);
			break;
		case game:
		case softPause:
			if(message != ""){
				sprite->Draw(messageBackground, NULL, &messageBackgroundCen,&messageBackgroundPos, D3DCOLOR_ARGB(185, 255, 255, 255));
				Gui.GetMenuFont()->DrawTextA(Gui.GetSprite(), message.c_str(), -1, &messageRect, 
							DT_VCENTER | DT_CENTER, D3DCOLOR_ARGB(255, 255, 255, 255));
			}
			sprite->Draw(timeImg, NULL, &timeImgCen,&timeImgPos, D3DCOLOR_ARGB(255, 255, 255, 255));
			sprite->Draw(timeNumbers[counterValue1], NULL, &timeNumer1Cen,&timeNumer1Pos, D3DCOLOR_ARGB(255, 255, 255, 255));
			sprite->Draw(timeNumbers[counterValue2], NULL, &timeNumer2Cen,&timeNumer2Pos, D3DCOLOR_ARGB(255, 255, 255, 255));
			sprite->Draw(timeNumbers[counterValue3], NULL, &timeNumer3Cen,&timeNumer3Pos, D3DCOLOR_ARGB(255, 255, 255, 255));
			sprite->Draw(timeNumbers[counterValue4], NULL, &timeNumer4Cen,&timeNumer4Pos, D3DCOLOR_ARGB(255, 255, 255, 255));

			sprite->Draw(starImg, NULL, &starImgCen,&starImgPos, D3DCOLOR_ARGB(255, 255, 255, 255));
			sprite->Draw(timeNumbers[starValue1], NULL, &starNumer1Cen,&starNumer1Pos, D3DCOLOR_ARGB(255, 255, 255, 255));
			sprite->Draw(timeNumbers[starValue2], NULL, &starNumer2Cen,&starNumer2Pos, D3DCOLOR_ARGB(255, 255, 255, 255));
			break;
	}
	sprite->End();
}
void CGuiButton::Execute(){
	switch(action){
		case GBA_EXIT:
			Game.ChangeStatus(endGame);
			break;
		case GBA_START:
			Game.ChangeStatus(loading);
			break;
		case GBA_MANUAL:
			Game.ChangeStatus(instructions);
			break;
		case GBA_RESUME:
			Game.ChangeStatus(game);
			break;
	}
}
void CGuiButton::Render(){
	if(state == GBS_NONE){
		Gui.GetSprite()->Draw(Gui.GetButton(), NULL, &center,&position, 
			D3DCOLOR_ARGB(127, 255, 255, 255));
	}else{
		Gui.GetSprite()->Draw(Gui.GetButton(), NULL, &center,&position, 
			0xFFFFFFFF);
	}
	Gui.GetMenuFont()->DrawTextA(Gui.GetSprite(), text.c_str(), -1, &rct, DT_VCENTER | DT_CENTER, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CGui::Reset(bool t){
	if(t){
		mainMenuFont->OnResetDevice();
		sprite->OnResetDevice();
		
		//ELOGEX("RESET DEVICE");
	}else{
		mainMenuFont->OnLostDevice();
		sprite->OnLostDevice();
		
		//ELOGEX("LOST DEVICE");
	}
}
void CGui::Clear(){
	SAFE_RELEASE(mainMenuFont);
	SAFE_RELEASE(sprite);
	ClearScreens();
}
void CGui::ClearScreens(){
	SAFE_RELEASE(screen1);
	SAFE_RELEASE(screen2);
	SAFE_RELEASE(button);
	SAFE_RELEASE(mainmenuScreen);
	SAFE_RELEASE(closingScreen);
	SAFE_RELEASE(instructionsScreen);
	SAFE_RELEASE(pauseScreen);
	SAFE_RELEASE(loadingScreen);
	SAFE_RELEASE(errorScreen);
	SAFE_RELEASE(menuBackground);
}