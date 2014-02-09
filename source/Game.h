#pragma once
#include "stdfx.h"
enum GAME_STATUS{
	start1, start2, 
	mainMenu, instructions,
	loading, loading2, game, pause, softPause, 
	endGame, closing, error
};
class CGame{
private:
	CGame(){ level = ""; isPaused = false; isSoftPaused = false; status = start1; reset = false;}
	CGame(const CGame &){}
	CGame& operator=(const CGame&){}
public:
	~CGame(){}
	static CGame& GetInstance(){
		static CGame inst;
		return inst;
	}

	bool Init(HINSTANCE hInstance, int nShowCmd);
	bool Update();
	bool Render();
	int Run(HINSTANCE hInstance, int nShowCmd);
	void ChangeStatus(GAME_STATUS newStatus);
	void NextStatus();
	GAME_STATUS GetStatus(){return status;}
	string GetActualLevel(){return level;}
	void SetLevel(string _level){ level = _level; }
	bool NextLevel();
	void Reset();
	void Pause();
	void SoftPause();
	void SoftResume();
	void EndGame();
	void Exit();
	void Clear();
private:
	GAME_STATUS status;
	string level, nextLevel, firstLevel;
	bool isPaused;
	bool isSoftPaused;
	bool reset;
};

#define Game CGame::GetInstance()