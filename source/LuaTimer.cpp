#include "Script.h"
#include "Timer.h"
#include "Logger.h"
void LuaTimer::RegisterFunctions(lua_State* Lua){
	lua_register(Lua, "TimerAdd", &LuaTimer::AddTimer);
	lua_register(Lua, "TimerDel", &LuaTimer::DelTimer);
	lua_register(Lua, "TimerExists", &LuaTimer::TimerExists);
}
int LuaTimer::AddTimer(lua_State *tmpL){
	//nazwa, czas konca w sekundach, typTimera, typCallbacku, nazwa funkcji lub metoda systemowa
	if(!Script.CheckInput(tmpL, 5)){
		ELOG("LuaTimer","AddTimer","Bledna liczba parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	if(!lua_isstring(tmpL, 1) || !lua_isnumber(tmpL, 2) || !lua_isnumber(tmpL, 3)
		|| !lua_isnumber(tmpL, 4)){
		ELOG("LuaTimer","AddTimer","Bledny typ parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	std::string name = lua_tostring(tmpL, 1);
	float time = (float)lua_tonumber(tmpL, 2);
	int timerType = (int)lua_tonumber(tmpL, 3);
	int callbackType = (int)lua_tonumber(tmpL, 4);
	CTimer* timer = NULL;
	CCallback* callback = NULL;
	switch(timerType){
		case 0://simple
			timer = new CTimerSimple(time);
			if(callbackType == 0){
				int callbackMethod = (int)lua_tonumber(tmpL, 5);
				//ewentualna implementacja kolejnych
				callback = new CCallbackEngine(CFT_NEXTSTATUS);
				timer->SetCallback(callback);
			}else{
				std::string luaFunction = lua_tostring(tmpL, 5);
				callback = new CCallbackLua(luaFunction);
			}
			break;
		case 1://counting
			timer = new CTimerCounting(time);
			if(callbackType == 0){
				int callbackMethod = (int)lua_tonumber(tmpL, 5);
				//ewentualna implementacja kolejnych
				callback = new CCallbackEngine(CFT_NEXTSTATUS);
				timer->SetCallback(callback);
			}else{
				std::string luaFunction = lua_tostring(tmpL, 5);
				callback = new CCallbackLua(luaFunction);
			}
			break;
		default:
			return Script.ReturnFalse(tmpL);
			break;
	}
	timer->SetCallback(callback);
	if(TimerMgr.AddTimer(name, timer)){
		return Script.ReturnTrue(tmpL);
	}else{
		return Script.ReturnFalse(tmpL);
	}	
}
int LuaTimer::DelTimer(lua_State *tmpL){
	if(!Script.CheckInput(tmpL, 1)){
		ELOG("LuaTimer","DelTimer","Bledna liczba parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	if(!lua_isstring(tmpL, 1)){
			ELOG("LuaTimer","DelTimer","Bledny typ parametrow!");
			return Script.ReturnFalse(tmpL);
	}
	std::string name = lua_tostring(tmpL, 1);
	TimerMgr.RemoveTimer(name);
	return Script.ReturnTrue(tmpL);
}
int LuaTimer::TimerExists(lua_State *tmpL){
	if(!Script.CheckInput(tmpL, 1)){
		ELOG("LuaTimer","TimerExists","Bledna liczba parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	if(!lua_isstring(tmpL, 1)){
		ELOG("LuaTimer","TimerExists","Bledny typ parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	std::string name = lua_tostring(tmpL, 1);
	if(TimerMgr.GetTimer(name) != NULL){
		return Script.ReturnTrue(tmpL);
	}else{
		return Script.ReturnFalse(tmpL);
	}
	
}
