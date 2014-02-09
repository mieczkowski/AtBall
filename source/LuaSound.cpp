#include "Script.h"
#include "Logger.h"
#include "SoundMgr.h"
#include "Renderable.h"
#include "Entity.h"
#include "EntityMgr.h"
void LuaSound::RegisterFunctions(lua_State* Lua){
	lua_register(Lua, "SoundAddFile", &LuaSound::AddFile);
	lua_register(Lua, "SoundDeleteFile", &LuaSound::DeleteFile);
	lua_register(Lua, "SoundPlay2D", &LuaSound::Play2D);
	lua_register(Lua, "SoundPlay3DPosition", &LuaSound::Play3DPosition);
	lua_register(Lua, "SoundPlay3DObject", &LuaSound::Play3DObject);
	lua_register(Lua, "SoundStop", &LuaSound::Stop);
	lua_register(Lua, "SoundStopLoop", &LuaSound::StopLoop);
	lua_register(Lua, "SoundPause", &LuaSound::Pause);
	lua_register(Lua, "SoundResume", &LuaSound::Resume);
	lua_register(Lua, "SoundPauseAll", &LuaSound::PauseAll);
	lua_register(Lua, "SoundResumeAll", &LuaSound::ResumeAll);
	lua_register(Lua, "SoundIsPlaying", &LuaSound::IsPlaying);
	lua_register(Lua, "SoundIsFinished", &LuaSound::IsFinished);
}

//name, filename
int LuaSound::AddFile(lua_State* tmpL){
	if(!Script.CheckInput(tmpL, 2)){
		ELOG("LuaSound","AddFile","Bledna liczba parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	if(!lua_isstring(tmpL, 1) || !lua_isstring(tmpL, 2)){
		ELOG("LuaSound","AddFile","Bledny typ parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	std::string name = lua_tostring(tmpL, 1);
	std::string filename = lua_tostring(tmpL, 2);
	SoundMgr.AddFile(name, filename);
	return Script.ReturnTrue(tmpL);
}
//name
int LuaSound::DeleteFile(lua_State* tmpL){
	if(!Script.CheckInput(tmpL, 1)){
		ELOG("LuaSound","DeleteFile","Bledna liczba parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	if(!lua_isstring(tmpL, 1)){
		ELOG("LuaSound","DeleteFile","Bledny typ parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	string name = lua_tostring(tmpL, 1);
	SoundMgr.DelFile(name);
	return Script.ReturnTrue(tmpL);
}
//name, file, loop
int LuaSound::Play2D(lua_State* tmpL){
	if(!Script.CheckInput(tmpL, 3)){
		ELOG("LuaSound","Play2D","Bledny typ parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	if(!lua_isstring(tmpL, 1) || !lua_isstring(tmpL, 2) || !lua_isnumber(tmpL, 3)){
		ELOG("LuaSound","Play2D","Bledny typ parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	string name = lua_tostring(tmpL, 1);
	string file = lua_tostring(tmpL, 2);
	int tmpLoop = (int)lua_tointeger(tmpL, 3);
	bool loop = false;
	if(tmpLoop == 1){
		loop = true;
	}
	if(SoundMgr.Play2D(name, file, loop)){
		return Script.ReturnTrue(tmpL);
	}else{
		ELOG("LuaSound","Play2D",string("Nie mozna odegrac dzwieku!") + file);
		return Script.ReturnFalse(tmpL);
	}
}
//name, file, loop, x,y,z
int LuaSound::Play3DPosition(lua_State* tmpL){
	if(Script.CheckInput(tmpL, 6)){
		if(!lua_isstring(tmpL, 2) || !lua_isnumber(tmpL, 3) || !lua_isnumber(tmpL, 4) || !lua_isnumber(tmpL, 5) || !lua_isnumber(tmpL, 6)){
			//ELOG("LuaSound","Play3DPosition","Bledny typ parametrow!");
			return Script.ReturnFalse(tmpL);
		}
		string name = lua_tostring(tmpL, 1);
		string file = lua_tostring(tmpL, 2);
		int tmpLoop = (int)lua_tointeger(tmpL, 3);
		float x = (float)lua_tonumber(tmpL, 4);
		float y = (float)lua_tonumber(tmpL, 5);
		float z = (float)lua_tonumber(tmpL, 6);
		vec3df position(x, y, z);
		bool loop = false;
		if(tmpLoop == 1){
			loop = true;
		}
		if(SoundMgr.Play3D(name, file, loop, position)){
			return Script.ReturnTrue(tmpL);
		}else{
			ELOG("LuaSound","Play3DPosition",string("Nie mozna odegrac dzwieku!") + file);
			return Script.ReturnFalse(tmpL);
		}
	}else{
		ELOG("LuaSound","Play3DPosition","Bledna liczba parametrow!");
		return Script.ReturnFalse(tmpL);
	}
}
//name, file, loop, object, follow
int LuaSound::Play3DObject(lua_State* tmpL){
	if(Script.CheckInput(tmpL, 5)){
		if(!lua_isstring(tmpL, 2) || !lua_isnumber(tmpL, 3) || !lua_isstring(tmpL, 4) 
			|| !lua_isnumber(tmpL, 5)){
				ELOG("LuaSound","Play3DObject","Bledny typ parametrow!");
				return Script.ReturnFalse(tmpL);
		}
		string name = lua_tostring(tmpL, 1);
		string file = lua_tostring(tmpL, 2);
		int tmpLoop = (int)lua_tointeger(tmpL, 3);
		string entName = lua_tostring(tmpL, 4);
		int tmpFollow = (int)lua_tointeger(tmpL, 5);
		bool loop = false;
		if(tmpLoop == 1){
			loop = true;
		}
		bool follow = false;
		if(tmpFollow == 1){
			follow = true;
		}
		IRenderable* ent = EntityMgr.GetEntity(entName);
		if(ent){
			if(SoundMgr.Play3D(name, file, loop, ent, follow)){
				return Script.ReturnTrue(tmpL);
			}else{
				ELOG("LuaSound","Play3DObject",string("Nie mozna odegrac dzwieku!") + file);
				return Script.ReturnFalse(tmpL);
			}
		}else{
			ELOG("LuaSound","Play3DObject",string("Nie mozna odegrac dzwieku! (obiekt do sledzenia nie istnieje): ") + entName);
			return Script.ReturnFalse(tmpL);
		}
	}else{
		ELOG("LuaSound","Play3DObject","Bledna liczba parametrow!");
		return Script.ReturnFalse(tmpL);
	}
}
//name
int LuaSound::Stop(lua_State* tmpL){
	if(!Script.CheckInput(tmpL, 1)){
		ELOG("LuaSound","Stop","Bledna liczba parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	if(!lua_isstring(tmpL, 1)){
		ELOG("LuaSound","Stop","Bledny typ parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	string name = lua_tostring(tmpL, 1);
	CSound* tmpSound = SoundMgr.GetSound(name);
	if(tmpSound){
		tmpSound->Stop();
		return Script.ReturnTrue(tmpL);
	}else{
		return Script.ReturnFalse(tmpL);
	}
}
//name
int LuaSound::StopLoop(lua_State* tmpL){
	if(!Script.CheckInput(tmpL, 1)){
		ELOG("LuaSound","StopLoop","Bledna liczba parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	if(!lua_isstring(tmpL, 1)){
		ELOG("LuaSound","StopLoop","Bledny typ parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	string name = lua_tostring(tmpL, 1);
	CSound* tmpSound = SoundMgr.GetSound(name);
	if(tmpSound){
		tmpSound->StopLoop();
		return Script.ReturnTrue(tmpL);
	}else{
		return Script.ReturnFalse(tmpL);
	}
}
//name
int LuaSound::Pause(lua_State* tmpL){
	if(!Script.CheckInput(tmpL, 1)){
		ELOG("LuaSound","Pause","Bledna liczba parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	if(!lua_isstring(tmpL, 1)){
		ELOG("LuaSound","Pause","Bledny typ parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	string name = lua_tostring(tmpL, 1);
	CSound* tmpSound = SoundMgr.GetSound(name);
	if(tmpSound){
		tmpSound->Pause();
		return Script.ReturnTrue(tmpL);
	}else{
		return Script.ReturnFalse(tmpL);
	}
}
//name
int LuaSound::Resume(lua_State* tmpL){
	if(!Script.CheckInput(tmpL, 1)){
		ELOG("LuaSound","Resume","Bledna liczba parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	if(!lua_isstring(tmpL, 1)){
		ELOG("LuaSound","Resume","Bledny typ parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	string name = lua_tostring(tmpL, 1);
	CSound* tmpSound = SoundMgr.GetSound(name);
	if(tmpSound){
		tmpSound->Resume();
		return Script.ReturnTrue(tmpL);
	}else{
		return Script.ReturnFalse(tmpL);
	}
}
//name
int LuaSound::IsPlaying(lua_State* tmpL){
	if(!Script.CheckInput(tmpL, 1)){
		ELOG("LuaSound","IsPlaying","Bledna liczba parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	if(!lua_isstring(tmpL, 1)){
		ELOG("LuaSound","IsPlaying","Bledny typ parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	string name = lua_tostring(tmpL, 1);
	CSound* tmpSound = SoundMgr.GetSound(name);
	if(tmpSound){
		if(tmpSound->IsPlaying()){
			return Script.ReturnTrue(tmpL);
		}else{
			return Script.ReturnFalse(tmpL);
		}
	}else{
		return Script.ReturnFalse(tmpL);
	}
}
//name
int LuaSound::IsFinished(lua_State* tmpL){
	if(!Script.CheckInput(tmpL, 1)){
		ELOG("LuaSound","IsFinished","Bledna liczba parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	if(!lua_isstring(tmpL, 1)){
		ELOG("LuaSound","IsFinished","Bledny typ parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	string name = lua_tostring(tmpL, 1);
	CSound* tmpSound = SoundMgr.GetSound(name);
	if(tmpSound){
		if(tmpSound->IsFinished()){
			return Script.ReturnTrue(tmpL);
		}else{
			return Script.ReturnFalse(tmpL);
		}
	}else{
		return Script.ReturnTrue(tmpL);
	}
}

int LuaSound::PauseAll(lua_State* tmpL){
	SoundMgr.PauseAll();
	return Script.ReturnTrue(tmpL);
}
int LuaSound::ResumeAll(lua_State* tmpL){
	SoundMgr.ResumeAll();
	return Script.ReturnTrue(tmpL);
}