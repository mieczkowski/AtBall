#include "Script.h"
#include "Logger.h"
#include "Scene.h"
#include "EntityMgr.h"
#include "SoundMgr.h"
#include "Media.h"
#include "Camera.h"
using namespace std;

bool CScript::Load(string filename){
	return Load(filename, true);
}
bool CScript::Load(string filename, bool addToMap){
	lua_State* script;
	script = lua_open();
	luaL_openlibs(script);
	if(addToMap == true){
		if(GetScript(filename, false) == NULL){
			pair<map<string, lua_State*>::iterator, bool> ret;
			ret = scriptList.insert(pair<string, lua_State*>(filename, script));
			if(ret.second == false){
				ELOG("CScript","Load",string("Nie mozna dodac skryptu do mapy: ") + filename);
				return false;
			}else{
				LOG("CScript","Load",string("Pomyslnie dodano skrypt: ") + filename);
			}
		}else{
			ELOG("CScript","Load",string("Proba dodania istniejacego skryptu: ") + filename);
		}
	}
	string file = string("scripts/") + filename + string(".lua");
	if(int err = luaL_dofile(script, file.c_str()) != 0){
		string error = lua_tostring(script, -1);
		lua_pop(script, 1);
		ELOG("CScript","Load",string("Nie mozna wykonac skryptu: ") + filename);
		ELOGEX(string("LUA OUTPUT: ") + error);
		RemoveScript(filename);
		return false;
	}
	RegisterFunctions(script);
	return true;	
}
bool CScript::Reload(string fileName){
	EntityMgr.Clear();
	Scene.Clear();
	SoundMgr.Clear();
	Media.Clear();
	Scene.Init();
	Camera.Init();
	return Load(fileName, false);
}
void CScript::RemoveScript(string filename){
	map<string, lua_State*>::iterator itr = scriptList.find(filename);
	if(itr != scriptList.end()){
		if(itr->second != NULL){
			lua_close(itr->second);
		}
		LOG("CScript","RemoveScript",string("Usuwam skrypt. Nazwa: ") + filename);
		scriptList.erase(itr);
	}
}
void CScript::RegisterFunctions(lua_State* script){
	LuaResource::RegisterFunctions(script);
	LuaGame::RegisterFunctions(script);
	LuaEntity::RegisterFunctions(script);
	LuaSound::RegisterFunctions(script);
	LuaCamera::RegisterFunctions(script);
	LuaTimer::RegisterFunctions(script);
}
lua_State* CScript::GetScript(string filename, bool logError){
	map<string, lua_State*>::iterator itr = scriptList.find(filename);
	if(itr != scriptList.end()){
		return itr->second;
	}else{
		if(logError) ELOG("CScript","GetScript",string("INFO: Skrypt nie istnieje! Nazwa: ") + filename);
		return NULL;
	}
}
lua_State* CScript::GetScript(string filename){
	return GetScript(filename, true);
}
void CScript::Clear(){
	LOG("CScript", "Clear", "Czyszczenie obiektu.");
	if(scriptList.empty() == false){
		for(map<string, lua_State*>::iterator itr = scriptList.begin(); itr != scriptList.end(); itr++){
			LOG("CLevelMgr","Clear",string("Usuwanie skryptu: ") + itr->first);
			lua_close(itr->second);
		}
		scriptList.clear();
	}	
}
int CScript::GetIntegerVariable(string filename, string var){
	return GetIntegerVariable(filename, var, 0);
}
int CScript::GetIntegerVariable(string filename, string var, int defaultValue){
	lua_State* script = GetScript(filename);
	if(script == NULL){
		ELOG("CScript","GetIntegerVariable",string("Skrypt nie istnieje: ") + filename);
		return defaultValue;
	}
	lua_getglobal(script, var.c_str());
	if(!lua_isnumber(script, -1)){
		ELOG("CScript","GetIntegerVariable",string("Parametr nie jest typu INTEGER lub zmienna nie istnieje!: ") + var);
		return defaultValue;
	}
	return (int)lua_tointeger(script, -1);
}
float CScript::GetNumberVariable(string filename, string var){
	return GetNumberVariable(filename, var, 0.0f);
}
float CScript::GetNumberVariable(string filename, string var, float defaultValue){
	lua_State* script = GetScript(filename);
	if(script == NULL){
		ELOG("CScript","GetNumberVariable",string("Skrypt nie istnieje: ") + filename);
		return defaultValue;
	}
	lua_getglobal(script, var.c_str());
	if(!lua_isnumber(script, -1)){
		ELOG("CScript","GetNumberVariable",string("Parametr nie jest typu FLOAT lub zmienna nie istnieje!: ") + var);
		return defaultValue;
	}
	return (float)lua_tonumber(script, -1);
}
string CScript::GetStringVariable(string filename, string var){
	return GetStringVariable(filename, var, "");
}
string CScript::GetStringVariable(string filename, string var, string defaultValue){
	lua_State* script = GetScript(filename);
	if(script == NULL){
		ELOG("CScript","GetStringVariable",string("Skrypt nie istnieje: ") + filename);
		return defaultValue;
	}
	lua_getglobal(script, var.c_str());
	if(!lua_isstring(script, -1)){
		ELOG("CScript","GetStringVariable",string("Parametr nie jest typu STRING lub zmienna nie istnieje!: ") + var);
		return defaultValue;
	}
	return string(lua_tostring(script, -1));
}
bool CScript::CallFunction(string filename, string name){
	LOG("CScript","CallFunction",string("Wywolanie procedury START: ") + name);
	lua_State* script = GetScript(filename);
	if(script != NULL){
		lua_getglobal(script, name.c_str());
		int result;
		result = lua_pcall(script, 0, 1, 0);
		if(result == 0){
			//LOG("CScript","CallFunction",string("Wywolanie procedury STOP: ") + name);
			return true;
		}else{
			ELOG("CScript","CallFunction",string("Nie mozna wywolac procedury: ") + name);
			string error = lua_tostring(script, -1);
			ELOGEX(string("LUA OUTPUT: ") + error);
			return false;
		}
	}else{
		ELOG("CLevelMgr","CallFunction",string("Skrypt nie istnieje: ") + filename);
		return false;
	}

}
bool CScript::CallFunction(string filename, string name, string par1){
	lua_State* script = GetScript(filename);
	if(script != NULL){
		lua_getglobal(script, name.c_str());
		lua_pushstring(script, par1.c_str());
		int result;
		result = lua_pcall(script, 1, 1, 0);
		if(result == 0){
			//LOG("CScript","CallFunction",string("Wywolanie procedury: ") + name);
			return lua_toboolean(script, -1);
		}else{
			ELOG("CScript","CallFunction",string("Nie mozna wywolac procedury: ") + name);
			string error = lua_tostring(script, -1);
			ELOGEX(string("LUA OUTPUT: ") + error);
			return false;
		}
	}else{
		ELOG("CScript","CallFunction",string("Skrypt nie istnieje: ") + filename);
		return false;
	}
}
bool CScript::CallFunction(string filename, string name, unsigned int val){
	lua_State* script = GetScript(filename);
	if(script != NULL){
		lua_getglobal(script, name.c_str());
		lua_pushinteger(script, val);
		int result;
		result = lua_pcall(script, 1, 1, 0);
		if(result == 0){
			//LOG("CScript","CallFunction",string("Wywolanie procedury: ") + name);
			return lua_toboolean(script, -1);
		}else{
			ELOG("CScript","CallFunction",string("Nie mozna wywolac procedury: ") + name);
			string error = lua_tostring(script, -1);
			ELOGEX(string("LUA OUTPUT: ") + error);
			return false;
		}
	}else{
		ELOG("CScript","CallFunction",string("Skrypt nie istnieje: ") + filename);
		return false;
	}
}
bool CScript::CallFunction(string filename, string name, string par1, string par2){
	lua_State* script = GetScript(filename);
	if(script != NULL){
		lua_getglobal(script, name.c_str());
		lua_pushstring(script, par1.c_str());
		lua_pushstring(script, par2.c_str());
		int result;
		result = lua_pcall(script, 2, 1, 0);
		if(result == 0){
			//LOG("CScript","CallFunction",string("Wywolanie procedury: ") + name);
			return lua_toboolean(script, -1);
		}else{
			ELOG("CScript","CallFunction",string("Nie mozna wywolac procedury: ") + name);
			string error = lua_tostring(script, -1);
			ELOGEX(string("LUA OUTPUT: ") + error);
			return false;
		}
	}else{
		ELOG("CScript","CallFunction",string("Skrypt nie istnieje: ") + filename);
		return false;
	}
}
bool CScript::CheckInput(lua_State* tmpL, int count){
	int parameterCount = lua_gettop(tmpL);
	if(parameterCount != count){
		return false;
	}else{
		return true;
	}
}
int CScript::ReturnTrue(lua_State* tmpL){
	lua_pushboolean(tmpL, true);
	return 1;
}
int CScript::ReturnFalse(lua_State* tmpL){
	lua_pushboolean(tmpL, false);
	return 1;
}
int CScript::ReturnString(lua_State* tmpL, string str){
	lua_pushstring(tmpL, str.c_str());
	return 1;
}
int CScript::ReturnNumber(lua_State* tmpL, float number){
	lua_pushnumber(tmpL, number);
	return 1;
}