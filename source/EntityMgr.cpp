#include "EntityMgr.h"
#include "Logger.h"
#include "Scene.h"
#include "Renderable.h"
void CEntityMgr::Clear(){
	LOG("EntityMgr","Clear","Niszczenie obiektu.");
	if(entityList.empty() == false){
		for(map<string, CEntity*>::iterator itr = entityList.begin(); itr != entityList.end(); itr++){
			LOG("EntityMgr","Clear",string("Usuwanie obiektu: ") + itr->first);
			SAFE_DELETE(itr->second);
		}
		entityList.clear();
	}	
}
bool CEntityMgr::AddEntity(CEntity *object){
	if(object == NULL) return false;
	string name = object->GetName();
	pair<map<string, CEntity*>::iterator, bool> ret;
	ret = entityList.insert(pair<string, CEntity*>(name, object));
	if(ret.second == false){
		ELOG("EntityMgr","AddObject",string("Nie mozna dodaæ obiektu do mapy obiektow! Nazwa: ") + name);
		return false;
	}else{
		LOG("EntityMgr","AddObject",string("Dodano obiekt do mapy obiektow, Nazwa: ") + name);
	}
	return true;
}
CEntity* CEntityMgr::GetEntity(string name){
	map<string, CEntity*>::iterator itr = entityList.find(name);
	if(itr != entityList.end()){
		return itr->second;
	}else{
		ELOG("EntityMgr","GetEntity",string("Obiekt nie istnieje! Nazwa: ") + name);
		return NULL;
	}
}
void CEntityMgr::RemoveEntity(string name){
	map<string, CEntity*>::iterator itr = entityList.find(name);
	if(itr != entityList.end()){
		Scene.Del(name, itr->second->GetType());
		LOG("EntityMgr","RemoveEntity",string("Usuwam obiekt! Nazwa: ") + name);
		SAFE_DELETE(itr->second);
		entityList.erase(itr);
	}
}
