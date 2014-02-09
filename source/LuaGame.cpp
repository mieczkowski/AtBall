#include "Script.h"
#include "Logger.h"
#include "Game.h"
#include "Gui.h"
#include "Directx.h"
#include "Timer.h"
void LuaGame::RegisterFunctions(lua_State* Lua){
	lua_register(Lua, "ShowError", &LuaGame::Error);
	lua_register(Lua, "ShowInfo", &LuaGame::Info);
	lua_register(Lua, "EndGame", &LuaGame::EndGame);
	lua_register(Lua, "ShowMessage", &LuaGame::ShowMessage);
	lua_register(Lua, "SetTimeout", &LuaGame::SetTimeout);
	lua_register(Lua, "SetAuroraCount", &LuaGame::SetStarsCount);
	lua_register(Lua, "ResetGame", &LuaGame::Reset);
	lua_register(Lua, "SetPostProcessingEffect", &LuaGame::SetPostProcessingEffect);
}
int LuaGame::Reset(lua_State* tmpL){
	Game.Reset();
	return 0;
}
int LuaGame::Error(lua_State* tmpL){
	if(!Script.CheckInput(tmpL, 1)){
		ELOG("LuaGame","Error","Bledna liczba parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	if(!lua_isstring(tmpL, 1)){
		ELOG("LuaGame","Error","Bledny typ parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	std::string message = lua_tostring(tmpL, 1);
	ELOG("LUA:","...",message);
	return Script.ReturnTrue(tmpL);
}
int LuaGame::Info(lua_State* tmpL){
	if(!Script.CheckInput(tmpL, 1)){
		ELOG("LuaGame","Info","Bledna liczba parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	if(!lua_isstring(tmpL, 1)){
		ELOG("LuaGame","Info","Bledny typ parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	std::string message = lua_tostring(tmpL, 1);
	LOG("LUA:","...",message);
	return Script.ReturnTrue(tmpL);
}
int LuaGame::EndGame(lua_State* tmpL){
	Game.ChangeStatus(loading);
	return 0;
}
int LuaGame::ShowMessage(lua_State* tmpL){
	if(!Script.CheckInput(tmpL, 1)){
		ELOG("LuaGame","ShowMessage","Bledna liczba parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	if(!lua_isstring(tmpL, 1)){
		ELOG("LuaGame","ShowMessage","Bledny typ parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	std::string message = lua_tostring(tmpL, 1);
	Gui.SetMessage(message);
	return Script.ReturnTrue(tmpL);
}
int LuaGame::SetTimeout(lua_State *tmpL){
	if(!Script.CheckInput(tmpL, 1)){
		ELOG("LuaGame","SetTimeout","Bledna liczba parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	if(!lua_isnumber(tmpL, 1)){
		ELOG("LuaGame","SetTimeout","Bledny typ parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	float time = (float)lua_tonumber(tmpL, 1);
	if(time > 60*60) time = 60*60;
	CTimer* checkTimer = TimerMgr.GetTimer("SYSTEM GameTime");
	if(checkTimer) return Script.ReturnTrue(tmpL);
	CTimerCounting* timer = new CTimerCounting(time);
	CCallbackEngine* callback = new CCallbackEngine(CFT_COUNTER);
	timer->SetCallback(callback);
	TimerMgr.AddTimer("SYSTEM GameTime", timer);
	return Script.ReturnTrue(tmpL);
}
int LuaGame::SetStarsCount(lua_State *tmpL){
	if(!Script.CheckInput(tmpL, 1)){
		ELOG("LuaGame","SetStarsCount","Bledna liczba parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	if(!lua_isnumber(tmpL, 1)){
		ELOG("LuaGame","SetStarsCount","Bledny typ parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	int number = (int)lua_tointeger(tmpL, 1);
	if(number < 0) number = 0;
	if(number > 99) number = 99;
	Gui.SetStarCounter(number);
	return Script.ReturnTrue(tmpL);
}
int LuaGame::SetPostProcessingEffect(lua_State *tmpL){
	if(!Script.CheckInput(tmpL, 1)){
		ELOG("LuaGame","SetPostProcessingEffect","Bledna liczba parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	if(!lua_isstring(tmpL, 1)){
		ELOG("LuaGame","SetPostProcessingEffect","Bledny typ parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	string name = lua_tostring(tmpL, 1);
	DirectX.SetPostProcessingEffect(name);
	return Script.ReturnTrue(tmpL);
}