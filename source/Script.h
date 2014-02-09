#pragma once
#include "stdfx.h"
extern "C" {
#include "inc/lua/lua.h"
#include "inc/lua/lualib.h"
#include "inc/lua/lauxlib.h"
};
#include <map>
using namespace std;
class CScript{
private:
	CScript(){}
	CScript(const CScript &){}
	CScript& operator=(const CScript&){}
	~CScript(){}
	
	map<string, lua_State*> scriptList;
public:
	static CScript& Instance(){
		static CScript inst;
		return inst;
	}
	bool Load(string filename);
	bool Load(string filename, bool addToMap);
	bool Reload(string filename);
	void RegisterFunctions(lua_State* script);
	void RemoveScript(string filename);
	lua_State* GetScript(string filename);
	lua_State* GetScript(string filename, bool logError);
	
	int GetIntegerVariable(string filename, string var);
	int GetIntegerVariable(string filename, string var, int defaultValue);
	float GetNumberVariable(string filename, string var);
	float GetNumberVariable(string filename, string var, float defaultValue);
	string GetStringVariable(string filename, string var);
	string GetStringVariable(string filename, string var, string defaultValue);
	bool CallFunction(string filename, string name);
	bool CallFunction(string filename, string name, string par1);
	bool CallFunction(string filename, string name, unsigned int val);
	bool CallFunction(string filename, string name, string par1, string par2);
	bool CheckInput(lua_State* tmpL, int number);
	int ReturnTrue(lua_State* tmpL);
	int ReturnFalse(lua_State* tmpL);
	int ReturnString(lua_State* tmpL, string str);
	int ReturnNumber(lua_State* tmpL, float number);

	void Clear();
};
#define Script CScript::Instance()

class LuaResource{
public:
	static void RegisterFunctions(lua_State* Lua);
	static int AddMesh(lua_State* tmpL);
	static int DelMesh(lua_State* tmpL);
	static int AddTexture(lua_State* tmpL);
	static int DelTexture(lua_State* tmpL);
	static int ParseIrrXML(lua_State* tmpL);
};

class LuaSound{
public:
	static void RegisterFunctions(lua_State* Lua);
	static int AddFile(lua_State* tmpL);
	static int DeleteFile(lua_State* tmpL);
	static int Play2D(lua_State* tmpL);
	static int Play3DPosition(lua_State* tmpL);
	static int Play3DObject(lua_State* tmpL);
	static int Stop(lua_State* tmpL);
	static int StopLoop(lua_State* tmpL);
	static int Pause(lua_State* tmpL);
	static int Resume(lua_State* tmpL);
	static int IsPlaying(lua_State* tmpL);
	static int IsFinished(lua_State* tmpL);
	static int PauseAll(lua_State* tmpL);
	static int ResumeAll(lua_State* tmpL);

};

class LuaEntity{
public:
	static void RegisterFunctions(lua_State* Lua);
	static int CreateEntity(lua_State* tmpL);
	static int DeleteEntity(lua_State* tmpL);
	static int SetPosition(lua_State* tmpL);
	static int SetRotation(lua_State* tmpL);
	static int SetScale(lua_State* tmpL);
	static int GetPosition(lua_State* tmpL);
	static int SetDynamic(lua_State* tmpL);
	static int SetMesh(lua_State* tmpL);
	static int SetTexture(lua_State* tmpL);
	static int Show(lua_State* tmpL);
	static int Hide(lua_State* tmpL);
	static int SetAnimation(lua_State* tmpL);

	static int SetPhysxShape(lua_State* tmpL);
	static int GetPhysxShape(lua_State* tmpL);
	
	static int SetActorAngularDamping(lua_State* tmpL);
	static int GetActorAngularDamping(lua_State* tmpL);
	static int SetActorMaxAngularVelocity(lua_State* tmpL);
	static int GetActorMaxAngularVelocity(lua_State* tmpL);
	static int SetActorMass(lua_State* tmpL);
	static int GetActorMass(lua_State* tmpL);
	static int SetMaterialRestitution(lua_State* tmpL);
	static int GetMaterialRestitution(lua_State* tmpL);
	static int SetMaterialStaticFriction(lua_State* tmpL);
	static int GetMaterialStaticFriction(lua_State* tmpL);
	static int SetMaterialDynamicFriction(lua_State* tmpL);
	static int GetMaterialDynamicFriction(lua_State* tmpL);
	static int RaiseBodyFlag(lua_State* tmpL);
	static int ClearBodyFlag(lua_State* tmpL);
	static int SetCallback(lua_State* tmpL);
	static int SetUpdateObject(lua_State* tmpL);
	static int EnableUpdateObject(lua_State* tmpL);
	static int DisableUpdateObject(lua_State* tmpL);
	static int ClearForces(lua_State* tmpL);

	static int SetForceField(lua_State* tmpL);
	static int EnableForceField(lua_State* tmpL);
	static int DisableForceField(lua_State* tmpL);

	static int SetTrigger(lua_State* tmpL);
	static int EnableTrigger(lua_State* tmpL);
	static int DisableTrigger(lua_State* tmpL);
	static int SetTriggerCallback(lua_State* tmpL);
	
	static int SetBindObject(lua_State* tmpL);

	static int SetNormalMap(lua_State* tmpL);
};

class LuaCamera{
public:
	static void RegisterFunctions(lua_State* Lua);
	static int SetStatus(lua_State* tmpL);
	static int SetFollowingObject(lua_State* tmpL);
	static int SetRotation(lua_State* tmpL);
	static int EnableAnimation(lua_State* tmpL);
	static int DisableAnimation(lua_State* tmpL);
	static int FreezePosition(lua_State* tmpL);
	static int UnfreezePosition(lua_State* tmpL);

	static int SetDistance(lua_State* tmpL);
	static int SetDistanceUp(lua_State* tmpL);
};

class LuaGame{
public:
	//start gry, koniec gry, save, nextlevel
	static void RegisterFunctions(lua_State* Lua);
	static int Error(lua_State* tmpL);
	static int Info(lua_State* tmpL);
	static int EndGame(lua_State* tmpL);
	static int ShowMessage(lua_State* tmpL);
	static int Pause(lua_State* tmpL);
	static int Resume(lua_State* tmpL);
	static int SetTimeout(lua_State* tmpL);
	static int SetStarsCount(lua_State* tmpL);
	static int Reset(lua_State* tmpL);
	static int SetPostProcessingEffect(lua_State* tmpL);
};

class LuaTimer{
public:
	static void RegisterFunctions(lua_State* Lua);
	static int AddTimer(lua_State* tmpL);
	static int DelTimer(lua_State* tmpL);
	static int TimerExists(lua_State* tmpL);
};