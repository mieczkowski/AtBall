#include "Game.h"
#include "Logger.h"
#include "Script.h"
#include "SoundMgr.h"
#include "Window.h"
#include "Directx.h"
#include "FPSCounter.h"
#include "Input.h"
#include "Camera.h"
#include "Scene.h"
#include "EntityMgr.h"
#include "Physx.h"
#include "Media.h"
#include "SkyBox.h"
#include "StoneControl.h"
#include "Gui.h"
#include "Timer.h"
bool CGame::Init(HINSTANCE hInstance, int nShowCmd){
	isPaused = false;
	if(!Script.Load("config")){
		ELOG("Game", "Init", "Nie mozna zaladowac pliku konfiguracyjnego!");
		return false;
	}
	level = Script.GetStringVariable("config", "level", "");
	if(level == ""){
		ELOG("Game", "Init", "Brak zmiennej LEVEL1 w pliku konfiguracyjnym!");
		Script.Clear();
		return false;
	}
	nextLevel = level;
	firstLevel = level;
	if(!SoundMgr.Init()){
		ELOG("Game", "Init", "Nie mozna zainicjowac systemu dzwieku!");
		Script.Clear();
		return false;
	}
	int fullscreen = Script.GetIntegerVariable("config", "fullscreen", 0);
	int screenSize = Script.GetIntegerVariable("config", "screenSize", 4);
	int postProcessingEnable = Script.GetIntegerVariable("config", "postProcessingEnable", 1);
	if(postProcessingEnable == 1) DirectX.SetPostProcessingEnable(true);
	else DirectX.SetPostProcessingEnable(false);
	if(!Window.Init(hInstance, nShowCmd, fullscreen, screenSize)){
		ELOG("Game", "Init", "Nie mozna zainicjowac okna!");
		Script.Clear();
		SoundMgr.Clear();
		return false;
	}
	if(!Input.Init()){
		ELOG("Game", "Init", "Nie mozna zainicjowac inputa!");
		Script.Clear();
		SoundMgr.Clear();
		return false;
	}
	if(!DirectX.Init()){
		ELOG("Game", "Init", "Nie mozna zainicjowac DirectX!");
		Script.Clear();
		SoundMgr.Clear();
		Input.Clear();
		return false;
	}
	if(!Gui.Init()){
		ELOG("Game", "Init", "Nie mozna zainicjowac GUI!");
		Script.Clear();
		SoundMgr.Clear();
		Input.Clear();
		DirectX.Clear();
		return false;
	}
	if(!Physx.Init()){
		ELOG("Game", "Init", "Nie mozna zainicjowac PhysX!");
		Script.Clear();
		SoundMgr.Clear();
		Input.Clear();
		Gui.Clear();
		DirectX.Clear();
		return false;
	}
	Camera.Init();
	if(!Scene.Init()){
		ELOG("Game", "Init", "Nie mozna zainicjowac Sceny!");
		Script.Clear();
		SoundMgr.Clear();
		Input.Clear();
		Gui.Clear();
		DirectX.Clear();
		return false;
	}
	if(!SkyBox.Init()){
		ELOG("Game", "Init", "Nie mozna utworzyc SkyBox'a!");
		Script.Clear();
		SoundMgr.Clear();
		Input.Clear();
		Gui.Clear();
		DirectX.Clear();
		return false;
	}
	
	LOG("Game", "Init", "Inicjalizacja silnika zakonczona pomyslnie!");
	Script.CallFunction("config", "onEngineStart");
	ChangeStatus(start1);
	return true;
}
bool CGame::Update(){
	FPSCounter.Update();
	SoundMgr.Update();
	TimerMgr.Update();
	Input.Update();
	if(status == game || status == pause){
		if(Input.Pause()){
			CTimer* timer = TimerMgr.GetTimer("SYSTEM PAUSETime");
			if(timer == NULL){
				Pause();
				CTimer* tmp = new CTimerSimple(0.5);
				TimerMgr.AddTimer("SYSTEM PAUSETime", tmp);
			}
		}
	}
	if(status == error){
		if(Input.Reset()){
			Reset();
		}
		if(Input.Esc()){
			Exit();
		}
	}
	if(status == game){
		if(Input.Reset()){
			Reset();
		}else if(Input.Esc()){
			ChangeStatus(mainMenu);
		}
	}
	if(status == instructions){
		if(Input.Esc()){
			ChangeStatus(mainMenu);
		}
	}
	Gui.Update(status);
	if(status == loading2){
		if(NextLevel()) ChangeStatus(game); //jesli nie uda sie to metoda sama ustawi status error
	}else if(status == loading){
		ChangeStatus(loading2); //zmieniamy zeby wyswietlic tlo loading, a przy kolejnym Update() wczytac level
	}else if(status == game){
		CTimer* timer = TimerMgr.GetTimer("SYSTEM InputSpaceTime");
		if(timer == NULL){
			if(Input.Space()){
				CTimer* tmp = new CTimerSimple(0.2f);
				TimerMgr.AddTimer("SYSTEM InputSpaceTime", tmp);
				Script.CallFunction(Game.GetActualLevel(), "InputSpace");
			}
		}
		Scene.Update();	
		Camera.Update();
	}else if(status == error){
		if(Input.Esc()){
			Exit();
			return false;
		}
	}
	return true;
}
bool CGame::Render(){
	return DirectX.Render(status);
}
int CGame::Run(HINSTANCE hInstance, int nShowCmd){
	if(!Init(hInstance, nShowCmd)){
		return 1;
	}
	Window.Show();
	FPSCounter.Start();
	MSG msg;
	while (TRUE){
		if(status == closing) break;
		if (PeekMessage( &msg, NULL, 0, 0, PM_REMOVE)){
			if(msg.message == WM_QUIT){
				break;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		if(Update() == false) break;
		if(Render() == false){
			break;
		}
	}
	Clear();
	return 0;
}
void CGame::ChangeStatus(GAME_STATUS newStatus){
	string oldStatus;
	switch(status){
		case start1:
			oldStatus = "start1";
			break;
		case start2:
			oldStatus = "start2";
			break;
		case mainMenu:
			oldStatus = "mainMenu";
			break;
		case instructions:
			oldStatus = "instructions";
			break;
		case pause:
			oldStatus = "pause";
			break;
		case softPause:
			oldStatus = "softPause";
			break;
		case error:
			oldStatus = "error";
			break;
		case game:
			oldStatus = "game";
			break;
		case loading:
			oldStatus = "loading";
			break;
		case endGame:
			oldStatus = "endGame";
			break;
		case closing:
			oldStatus = "closing";
			break;
	}
	switch(newStatus){
		case start1:
			{
				CTimer *timer = new CTimerSimple(4);
				CCallback *callback = new CCallbackEngine(CFT_NEXTSTATUS);
				timer->SetCallback(callback);
				TimerMgr.AddTimer("SYSTEM start1", timer);
				Script.CallFunction("config", "onScreen1", oldStatus);
			}
			break;
		case start2:
			{
				CTimer *timer = new CTimerSimple(4);
				CCallback *callback = new CCallbackEngine(CFT_NEXTSTATUS);
				timer->SetCallback(callback);
				TimerMgr.AddTimer("SYSTEM start2", timer);
				Script.CallFunction("config", "onScreen2", oldStatus);
			}
			break;
		case mainMenu:
			{
				if(oldStatus == "game"){
					TimerMgr.Pause();
					SoundMgr.PauseAll();
				}
				Script.CallFunction("config", "onMainMenu", oldStatus);
			}
			break;
		case instructions:
				Script.CallFunction("config", "onInstructions", oldStatus);
			break;
		case pause:
				Script.CallFunction("config", "onPause", oldStatus);
			break;
		case softPause:
				Script.CallFunction("config", "onSoftPause", oldStatus);
			break;
		case error:
				Script.CallFunction("config", "onError", oldStatus);
			break;
		case game:
			{
				TimerMgr.Resume();
				SoundMgr.ResumeAll();
				Script.CallFunction("config", "onGame", oldStatus);
			}
			break;
		case loading:
			{
				Gui.mainMenuButtons[0]->SetAction(GBA_RESUME);
				Gui.mainMenuButtons[0]->SetText("Powrót do gry");
			}
			break;
		case endGame:
			{
				CTimer *timer = new CTimerSimple(2);
				CCallback *callback = new CCallbackEngine(CFT_NEXTSTATUS);
				timer->SetCallback(callback);
				TimerMgr.AddTimer("SYSTEM endGame", timer);
				Script.CallFunction("config", "onClosing", oldStatus);
			}
			break;
		case closing:
			Exit();
			break;
	}
	status = newStatus;
}
void CGame::EndGame(){
	Gui.mainMenuButtons[0]->SetAction(GBA_START);
	Gui.mainMenuButtons[0]->SetText("START GRY OD NOWA");
	level = firstLevel;
	nextLevel = level;
	Script.CallFunction("config", "onEndGame");
	ChangeStatus(mainMenu);
}
void CGame::NextStatus(){
	switch(status){
		case start1:
			ChangeStatus(start2);
			break;
		case start2:
			ChangeStatus(mainMenu);
			break;
		case mainMenu:
			ChangeStatus(loading);
			break;
		case endGame:
			ChangeStatus(closing);
			break;
	}
}
bool CGame::NextLevel(){
	Gui.SetCounter(0);
	Gui.SetStarCounter(0);
	Scene.Clear();
	Scene.Init();
	EntityMgr.Clear();
	SoundMgr.Clear();
	Media.Clear();
	Camera.Init();
	TimerMgr.Clear();
	Script.CallFunction("config", "onLoading");
	if(reset){
		reset = false;
		Script.RemoveScript(level);
		if(!Script.Load(level)){
			ELOG("Game", "Reset", "Nie mozna zaladowac poziomu!");
			ChangeStatus(error);
			return false;
		}
		nextLevel = Script.GetStringVariable(GetActualLevel(), "NextLevel", "");
		Script.CallFunction("config", "onReset");
		if(!Script.CallFunction(GetActualLevel(), "main")){
			ChangeStatus(error);
			return false;
		}
		return true;
	}else{
		bool first = false;
		if(level == nextLevel) first = true;
		if(nextLevel == ""){
			EndGame();
			return false;
		}
		Script.RemoveScript(level);
		if(!Script.Load(nextLevel)){
			if(first){
				ELOG("Game", "NextLevel", "Nie mozna zaladowac poziomu!");
				ChangeStatus(error);
			}else{
				LOG("Game", "NextLevel", "Nastepny poziom nie istnieje. Koniec gry");
				EndGame();
			}
			return false;
		}
		
		level = nextLevel;
		nextLevel = Script.GetStringVariable(level, "NextLevel", "");
		if(nextLevel == level) nextLevel = "";

		
		if(!Script.CallFunction(GetActualLevel(), "main")){
			ChangeStatus(error);
			return false;
		}
		return true;
	}
}
void CGame::Reset(){
	reset = true;
	ChangeStatus(loading);
}
void CGame::Pause(){
	if(status == pause || status == game){
		if(isPaused){
			ChangeStatus(game);
			FPSCounter.Start();
// 			CTimer* counter = TimerMgr.GetTimer("SYSTEM GameTime");
// 			if(counter) counter->Resume();
			TimerMgr.Resume();
			SoundMgr.ResumeAll();
		}else{
			ChangeStatus(pause);
			FPSCounter.Stop();
// 			CTimer* counter = TimerMgr.GetTimer("SYSTEM GameTime");
// 			if(counter) counter->Pause();
			TimerMgr.Pause();
			SoundMgr.PauseAll();
		}
		isPaused = !isPaused;
	}
}
void CGame::SoftPause(){
	if(status == game){
		ChangeStatus(softPause);
		FPSCounter.Stop();
		CTimer* counter = TimerMgr.GetTimer("SYSTEM GameTime");
		if(counter) counter->Pause();
		isSoftPaused = true;
	}
}
void CGame::SoftResume(){
	if(status == softPause){
		ChangeStatus(game);
		FPSCounter.Start();
		CTimer* counter = TimerMgr.GetTimer("SYSTEM GameTime");
		if(counter) counter->Pause();
		isSoftPaused = false;
	}
}
void CGame::Exit(){
	//Clear();
	PostQuitMessage(0);
}
void CGame::Clear(){
	FPSCounter.Stop();
	TimerMgr.Clear();
	EntityMgr.Clear();
	Scene.Clear();
	Media.Clear();
	Physx.Clear();
	Input.Clear();
	SoundMgr.Clear();
	Script.Clear();
	SkyBox.Clear();
	DirectX.Clear();
}