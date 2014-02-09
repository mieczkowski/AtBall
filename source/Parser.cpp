#include "Parser.h"
#include "stdfx.h"
#include <iostream>
#include <sstream>
#include "inc/xml/irrXML.h"
#include "Script.h"
#include "Game.h"
#include "Logger.h"
using namespace std;
using namespace irr;
using namespace io;
template<class T>
T fromString(const std::string& s){
	std::istringstream stream (s);
	T t;
	stream >> t;
	return t;
}
string cutDir(string filename){
	return filename.substr(filename.find_last_of("/")+1);
}
D3DXVECTOR3 strToVec(string vals){
	string x, y, z;
	size_t first = vals.find_first_of(",");
	size_t second = vals.find_last_of(",");
	x = vals.substr(0, first);
	y = vals.substr(first+2, vals.length() - second + 1);
	z = vals.substr(second+2);
	D3DXVECTOR3 tmpVec;
	tmpVec.x = fromString<float>(x);
	tmpVec.y = fromString<float>(y);
	tmpVec.z = fromString<float>(z);
	return tmpVec;
}
struct Entity{
	string name;
	D3DXVECTOR3 position;
	D3DXVECTOR3 rotation;
	D3DXVECTOR3 scale;
	string mesh;
	string texture;
};
void ClearEntity(Entity *entity){
	entity->name = "";
	entity->mesh = "";
	entity->position = D3DXVECTOR3(0,0,0);
	entity->rotation = D3DXVECTOR3(0,0,0);
	entity->scale = D3DXVECTOR3(0,0,0);
	entity->texture = "";
}
int CallLuaFunction(string name, Entity *entity){
	lua_State* script = Script.GetScript(Game.GetActualLevel());
	if(script != NULL){
		lua_getglobal(script, name.c_str());
		lua_pushstring(script, entity->name.c_str());
		lua_pushstring(script, entity->mesh.c_str());
		lua_pushstring(script, entity->texture.c_str());
		lua_pushnumber(script, entity->position.x);
		lua_pushnumber(script, entity->position.y);
		lua_pushnumber(script, entity->position.z);
		lua_pushnumber(script, entity->rotation.x);
		lua_pushnumber(script, entity->rotation.y);
		lua_pushnumber(script, entity->rotation.z);
		lua_pushnumber(script, entity->scale.x);
		lua_pushnumber(script, entity->scale.y);
		lua_pushnumber(script, entity->scale.z);
		int result;
		result = lua_pcall(script, 12, 1, 0);
		if(result == 0){
			ClearEntity(entity);
			return (BOOL)lua_toboolean(script, -1);
		}else{
			ELOG("CParser","CallLuaFunction",string("Nie mozna wywolac procedury: ") + name);
			string error = lua_tostring(script, -1);
			ELOGEX(string("LUA OUTPUT: ") + error);
			return FALSE;
		}
	}else{
		ELOG("CParser","CallLuaFunction",string("Skrypt nie istnieje: ") + Game.GetActualLevel());
		return FALSE;
	}
}
bool CParser::parseIrrXml(string xmlFile, string method){
	IrrXMLReader* xml = createIrrXMLReader(xmlFile.c_str());
	if(!xml){
		ELOG("CParser", "parseIrrXml", string("Plik XML nie istnieje: ") + xmlFile);
		return false;
	}
	int status = 0;
	Entity entity;
	ClearEntity(&entity);

	while(xml && xml->read()){
		switch(xml->getNodeType()){
		case EXN_ELEMENT:
			{
				string get = xml->getNodeName();
				if(get == "node"){
					string type = xml->getAttributeValue("type");
					if(type == "mesh"){
						if(status == 0){
							status = 1; //zaczynamy parsowanie modelu (dzieki temu omijamy zbedne poczatkowe znaczniki)
							//ELOGEX("DEBUG: WYKRYTO MESHA");
						}else{
							if(!CallLuaFunction(method, &entity)) {
								break;
							}else{
								//ELOGEX("DEBUG: WYKRYTO MESHA");
							}
						}
					}
				}else if(get == "vector3d" && status == 1){
					string name = xml->getAttributeValue("name");
					if(name == "Position"){
						string position = xml->getAttributeValue("value");
						entity.position = strToVec(position);
					}else if(name == "Rotation"){						
						string rotation = xml->getAttributeValue("value");
						entity.rotation = strToVec(rotation);
					}else if(name == "Scale"){
						string scale = xml->getAttributeValue("value");
						entity.scale = strToVec(scale);
					}
				}else if(get == "string" && status == 1){
					string name = xml->getAttributeValue("name");
					if(name == "Mesh"){
						string model = cutDir(xml->getAttributeValue("value"));
						entity.mesh = model;
					}else if(name == "Name"){
						string nazwa = xml->getAttributeValue("value");
						entity.name = nazwa;
					}
				}else if(get == "texture" && status == 1){
					string name = xml->getAttributeValue("name");
					if(name == "Texture1"){
						string filename = cutDir(xml->getAttributeValue("value"));
						entity.texture = filename;
					}
				}
			}
			break;
		}
	}
	CallLuaFunction(method, &entity);
	delete xml;
	return true;
}
