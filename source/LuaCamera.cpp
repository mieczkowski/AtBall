#include "Script.h"
#include "Logger.h"
#include "Camera.h"
void LuaCamera::RegisterFunctions(lua_State* Lua){
	lua_register(Lua, "CameraSetFollowingObject", &LuaCamera::SetFollowingObject);
	lua_register(Lua, "CameraSetStatus", &LuaCamera::SetStatus);
	lua_register(Lua, "CameraSetRotation", &LuaCamera::SetRotation);
	lua_register(Lua, "CameraEnableAnimation", &LuaCamera::EnableAnimation);
	lua_register(Lua, "CameraDisableAnimation", &LuaCamera::DisableAnimation);
	lua_register(Lua, "CameraFreezePosition", &LuaCamera::FreezePosition);
	lua_register(Lua, "CameraUnfreezePosition", &LuaCamera::UnfreezePosition);

	lua_register(Lua, "CameraDistance", &LuaCamera::SetDistance);
	lua_register(Lua, "CameraDistanceUp", &LuaCamera::SetDistanceUp);
}
int LuaCamera::SetFollowingObject(lua_State* tmpL){
	if(!Script.CheckInput(tmpL, 1)){
		ELOG("LuaCamera","SetFollowingObject","Bledna liczba parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	if(!lua_isstring(tmpL, 1)){
		ELOG("LuaCamera","SetFollowingObject","Bledny typ parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	std::string name = lua_tostring(tmpL, 1);
	if(Camera.SetFollowedObject(name)){
		return Script.ReturnTrue(tmpL);
	}else{
		ELOG("LuaCamera","SetFollowingObject","Nie mozna ustawic obiektu do sledzenia!");
		return Script.ReturnFalse(tmpL);
	}
}
int LuaCamera::SetStatus(lua_State* tmpL){
	if(!Script.CheckInput(tmpL, 1)){
		ELOG("LuaCamera","SetStatus","Bledna liczba parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	if(!lua_isnumber(tmpL, 1)){
		ELOG("LuaCamera","SetStatus","Bledny typ parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	int status = lua_tointeger(tmpL, 1);
	if(status == 0){
		Camera.SetStatic();

	}else{
		Camera.SetDynamic();
	}
	return Script.ReturnTrue(tmpL);
}
int LuaCamera::SetRotation(lua_State* tmpL){
	if(!Script.CheckInput(tmpL, 1)){
		ELOG("LuaCamera","SetRotation","Bledna liczba parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	if(!lua_isnumber(tmpL, 1)){
		ELOG("LuaCamera","SetRotation","Bledny typ parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	int rotation = lua_tointeger(tmpL, 1);
	Camera.SetRotation(rotation);
	return Script.ReturnTrue(tmpL);
}
int LuaCamera::EnableAnimation(lua_State* tmpL){
	if(!Script.CheckInput(tmpL, 1)){
		ELOG("LuaCamera","EnableAnimation","Bledna liczba parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	if(!lua_isnumber(tmpL, 1)){
		ELOG("LuaCamera","EnableAnimation","Bledny typ parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	int rotation = lua_tointeger(tmpL, 1);
	Camera.EnableAnimation(rotation);
	return Script.ReturnTrue(tmpL);
}
int LuaCamera::DisableAnimation(lua_State* tmpL){
	Camera.DisableAnimation();
	return Script.ReturnTrue(tmpL);
}
int LuaCamera::FreezePosition(lua_State* tmpL){
	Camera.FreezePosition();
	return Script.ReturnTrue(tmpL);
}
int LuaCamera::UnfreezePosition(lua_State* tmpL){
	Camera.UnfreezePosition();
	return Script.ReturnTrue(tmpL);
}

int LuaCamera::SetDistance(lua_State* tmpL){
	if(!Script.CheckInput(tmpL, 1)){
		ELOG("LuaCamera","SetDistance","Bledna liczba parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	if(!lua_isnumber(tmpL, 1)){
		ELOG("LuaCamera","SetDistance","Bledny typ parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	int distance = lua_tointeger(tmpL, 1);
	Camera.SetDistance(distance);
	return Script.ReturnTrue(tmpL);
}
int LuaCamera::SetDistanceUp(lua_State* tmpL){
	if(!Script.CheckInput(tmpL, 1)){
		ELOG("LuaCamera","SetDistanceUp","Bledna liczba parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	if(!lua_isnumber(tmpL, 1)){
		ELOG("LuaCamera","SetDistanceUp","Bledny typ parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	int distance = lua_tointeger(tmpL, 1);
	Camera.SetDistanceUp(distance);
	return Script.ReturnTrue(tmpL);
}