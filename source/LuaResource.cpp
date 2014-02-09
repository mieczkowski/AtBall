#include "Script.h"
#include "Media.h"
#include "Logger.h"
#include "Parser.h"
void LuaResource::RegisterFunctions(lua_State* Lua){
	lua_register(Lua, "ResourceAddTexture", &LuaResource::AddTexture);
	lua_register(Lua, "ResourceAddMesh", &LuaResource::AddMesh);
	lua_register(Lua, "ResourceDelTexture", &LuaResource::DelTexture);
	lua_register(Lua, "ResourceDelMesh", &LuaResource::DelMesh);
	lua_register(Lua, "ResourceParseIrrXML", &LuaResource::ParseIrrXML);
}
int LuaResource::AddMesh(lua_State* tmpL){
	if(!Script.CheckInput(tmpL, 2)){
		ELOG("LuaResource","AddMesh","Bledna liczba parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	if(!lua_isstring(tmpL, 1) || !lua_isstring(tmpL, 2)){
		ELOG("LuaResource","AddMesh","Bledny typ parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	std::string name = lua_tostring(tmpL, 1);
	std::string path = lua_tostring(tmpL, 2);
	if(Media.AddMesh(name, path)){
		return Script.ReturnTrue(tmpL);
	}else{
		return Script.ReturnFalse(tmpL);
	}
}
int LuaResource::DelMesh(lua_State* tmpL){
	if(!Script.CheckInput(tmpL, 1)){
		ELOG("LuaResource","DelMesh","Bledna liczba parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	if(!lua_isstring(tmpL, 1)){
		ELOG("LuaResource","DelMesh","Bledny typ parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	std::string name = lua_tostring(tmpL, 1);
	Media.RemoveMesh(name);
	return Script.ReturnTrue(tmpL);
}
int LuaResource::AddTexture(lua_State* tmpL){
	if(!Script.CheckInput(tmpL, 2)){
		ELOG("LuaResource","AddTexture","Bledna liczba parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	if(!lua_isstring(tmpL, 1) || !lua_isstring(tmpL, 2)){
		ELOG("LuaResource","AddTexture","Bledny typ parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	std::string name = lua_tostring(tmpL, 1);
	std::string path = lua_tostring(tmpL, 2);
	if(Media.AddTexture(name, path)){
		return Script.ReturnTrue(tmpL);
	}else{
		return Script.ReturnFalse(tmpL);
	}
}
int LuaResource::DelTexture(lua_State* tmpL){
	if(!Script.CheckInput(tmpL, 1)){
		ELOG("LuaResource","DelTexture","Bledna liczba parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	if(!lua_isstring(tmpL, 1)){
		ELOG("LuaResource","DelTexture","Bledny typ parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	std::string name = lua_tostring(tmpL, 1);
	Media.RemoveTexture(name);
	return Script.ReturnTrue(tmpL);
}
int LuaResource::ParseIrrXML(lua_State *tmpL){
	if(!Script.CheckInput(tmpL, 2)){
		ELOG("LuaResource","ParseIrrXML","Bledna liczba parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	if(!lua_isstring(tmpL, 1) || !lua_isstring(tmpL, 2)){
		ELOG("LuaResource","ParseIrrXML","Bledny typ parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	
	std::string fileName = lua_tostring(tmpL, 1);
	std::string functionName = lua_tostring(tmpL, 2);
	bool result = CParser::parseIrrXml(fileName, functionName);
	if(result) return Script.ReturnTrue(tmpL);
	else return Script.ReturnFalse(tmpL);
}