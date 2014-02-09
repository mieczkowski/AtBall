#pragma once
#include "stdfx.h"
#include <map>
using namespace std;
#include "Entity.h"

class CEntityMgr{
public:
	CEntityMgr(){}
	CEntityMgr(const CEntityMgr &){}
	CEntityMgr& operator=(const CEntityMgr&){}
	~CEntityMgr(){}
public:
	static CEntityMgr& GetInstance(){
		static CEntityMgr inst;
		return inst;
	}
	void Clear();
	bool AddEntity(CEntity* object);
	CEntity* GetEntity(string name);
	void RemoveEntity(string name);
	map<string, class CEntity*>* GetEntityList(){return &entityList;}
private:
	map<string, class CEntity*> entityList;
};

#define EntityMgr CEntityMgr::GetInstance()