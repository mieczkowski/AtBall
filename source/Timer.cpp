#include "Timer.h"
#include <vector>
#include "Logger.h"
#include "Game.h"
#include "Script.h"
#include "Gui.h"
using namespace std;
void CTimerMgr::Update(){
	vector<string> toDelete;
	if(timerList.empty() == false){
		for(map<string, CTimer*>::iterator itr = timerList.begin(); itr != timerList.end(); itr++){
			if(itr->second){
				if(itr->second->IsFinished()){
					toDelete.push_back(itr->first);
				}
			}
		}
	}
	for(vector<string>::size_type i = 0; i < toDelete.size(); i++) RemoveTimer(toDelete[i]);
	if(timerList.empty() == false){
		for(map<string, CTimer*>::iterator itr = timerList.begin(); itr != timerList.end(); itr++){
			if(itr->second){
				itr->second->Check();
			}
		}
	}
}
void CTimerMgr::Pause(){
	if(timerList.empty() == false){
		for(map<string, CTimer*>::iterator itr = timerList.begin(); itr != timerList.end(); itr++){
			if(itr->second){
				itr->second->Pause();
			}
		}
	}
}
void CTimerMgr::Resume(){
	if(timerList.empty() == false){
		for(map<string, CTimer*>::iterator itr = timerList.begin(); itr != timerList.end(); itr++){
			if(itr->second){
				itr->second->Resume();
			}
		}
	}
}
void CTimerMgr::Clear(){
	if(timerList.empty() == false){
		for(map<string, CTimer*>::iterator itr = timerList.begin(); itr != timerList.end(); itr++){
			LOG("CTimerMgr","Clear",string("Usuwanie obiektu: ") + itr->first);
			SAFE_DELETE(itr->second);
		}
		timerList.clear();
	}	
}
bool CTimerMgr::AddTimer(string name, CTimer *timer){
	if(timer == NULL) return false;
	pair<map<string, CTimer*>::iterator, bool> ret;
	ret = timerList.insert(pair<string, CTimer*>(name, timer));
	if(ret.second == false){
		ELOG("CTimerMgr","AddTimer",string("Nie mozna dodaæ timera! Nazwa: ") + name);
		return false;
	}
	return true;
}
CTimer* CTimerMgr::GetTimer(string name){
	map<string, CTimer*>::iterator itr = timerList.find(name);
	if(itr != timerList.end()){
		return itr->second;
	}else{
		return NULL;
	}
}
void CTimerMgr::RemoveTimer(string name){
	map<string, CTimer*>::iterator itr = timerList.find(name);
	if(itr != timerList.end()){
		SAFE_DELETE(itr->second);
		timerList.erase(itr);
	}
}
CTimer::~CTimer(){
	SAFE_DELETE(callback);
}
CTimerSimple::CTimerSimple(float seconds){
	start = clock();
	end = start + static_cast<clock_t>(seconds * CLOCKS_PER_SEC);
	finished = false;
	paused = false;
	callback = NULL;
}
void CTimerSimple::Resume(){
	if(!paused) return;
	clock_t now = clock();
	start += now - pauseTime; //dodajemy do startu ilosc sekund ktora uplynela podczas pauzy
	end += now - pauseTime;
	paused = false;
}
void CTimerSimple::Check(){
	if(paused == true || finished == true) return;
	clock_t now = clock();
	if(now > end){
		if(callback){
			callback->Execute(now - end);
		}
		finished = true;
	}
}
/////////////////////////////////////
void CTimerCounting::Check(){
	if(paused == true || finished == true) return;
	clock_t now = clock();
	if(now < end){
		if(callback) callback->Execute(end - now);
	}else{
		if(callback) callback->Execute(0);
		finished = true;
	}
}

/////////////////////////////////////

void CCallbackLua::Execute(clock_t time){
	Script.CallFunction(Game.GetActualLevel(), name, time);
}
void CCallbackEngine::Execute(clock_t time){
	switch(type){
		case CFT_NEXTSTATUS:
			Game.NextStatus();
			break;
		case CFT_COUNTER:
			Gui.SetCounter(time);
			Script.CallFunction(Game.GetActualLevel(), "TimeoutCounting", time);
			if(time == 0){
				Script.CallFunction(Game.GetActualLevel(), "Timeout");
			}
			break;
	}
}