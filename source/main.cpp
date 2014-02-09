#include "Game.h"
#include "Logger.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd){
	LOGEX("WinMain: START");
	int result = Game.Run(hInstance,nShowCmd);
	//while(true){}

	return result;
}