#include "Script.h"
#include "StoneControl.h"
#include "Game.h"
#include "Media.h"
#include "Logger.h"
#include "Camera.h"
#include "Entity.h"
#include "EntityMgr.h"
#include "StoneControl.h"
#include "Scene.h"
#include "Renderable.h"
#include "ForceField.h"
#include "Trigger.h"
#include <cstdlib>
#include <ctime>

void LuaEntity::RegisterFunctions(lua_State* Lua){
	lua_register(Lua, "EntityCreate", &LuaEntity::CreateEntity);
	lua_register(Lua, "EntityDelete", &LuaEntity::DeleteEntity);
	lua_register(Lua, "EntitySetStartPosition", &LuaEntity::SetPosition);
	lua_register(Lua, "EntitySetStartRotation", &LuaEntity::SetRotation);
	lua_register(Lua, "EntitySetStartScale", &LuaEntity::SetScale);
	lua_register(Lua, "EntityGetPosition", &LuaEntity::GetPosition);
	lua_register(Lua, "EntityShow", &LuaEntity::Show);
	lua_register(Lua, "EntityHide", &LuaEntity::Hide);
	lua_register(Lua, "EntitySetAnimation", &LuaEntity::SetAnimation);

	lua_register(Lua, "EntitySetDynamic", &LuaEntity::SetDynamic);
	lua_register(Lua, "EntitySetPhysxShape", &LuaEntity::SetPhysxShape);
	lua_register(Lua, "EntityGetPhysxShape", &LuaEntity::GetPhysxShape);
	lua_register(Lua, "EntitySetMesh", &LuaEntity::SetMesh);
	lua_register(Lua, "EntitySetTexture", &LuaEntity::SetTexture);
	lua_register(Lua, "EntitySetNormalMap", &LuaEntity::SetNormalMap);
	lua_register(Lua, "EntitySetActorAngularDamping", &LuaEntity::SetActorAngularDamping);
	lua_register(Lua, "EntityGetActorAngularDamping", &LuaEntity::GetActorAngularDamping);	
	lua_register(Lua, "EntitySetActorMaxAngularVelocity", &LuaEntity::SetActorMaxAngularVelocity);
	lua_register(Lua, "EntityGetActorMaxAngularVelocity", &LuaEntity::GetActorMaxAngularVelocity);
	lua_register(Lua, "EntitySetActorMass", &LuaEntity::SetActorMass);
	lua_register(Lua, "EntityGetActorMass", &LuaEntity::GetActorMass);
	lua_register(Lua, "EntitySetMaterialRestitution", &LuaEntity::SetMaterialRestitution);
	lua_register(Lua, "EntityGetMaterialRestitution", &LuaEntity::GetMaterialRestitution);
	lua_register(Lua, "EntitySetMaterialStaticFriction", &LuaEntity::SetMaterialStaticFriction);
	lua_register(Lua, "EntityGetMaterialStaticFriction", &LuaEntity::GetMaterialStaticFriction);
	lua_register(Lua, "EntitySetMaterialDynamicFriction", &LuaEntity::SetMaterialDynamicFriction);
	lua_register(Lua, "EntityGetMaterialDynamicFriction", &LuaEntity::GetMaterialDynamicFriction);
	lua_register(Lua, "EntityRaiseBodyFlag", &LuaEntity::RaiseBodyFlag);
	lua_register(Lua, "EntityClearBodyFlag", &LuaEntity::ClearBodyFlag);
	lua_register(Lua, "EntitySetCallback", &LuaEntity::SetCallback);
	lua_register(Lua, "EntitySetUpdateObject", &LuaEntity::SetUpdateObject);

	lua_register(Lua, "EntitySetForceField", &LuaEntity::SetForceField);
	lua_register(Lua, "EntityEnableForceField", &LuaEntity::EnableForceField);
	lua_register(Lua, "EntityDisableForceField", &LuaEntity::DisableForceField);

	lua_register(Lua, "EntitySetTrigger", &LuaEntity::SetTrigger);
	lua_register(Lua, "EntityEnableTrigger", &LuaEntity::EnableTrigger);
	lua_register(Lua, "EntityDisableTrigger", &LuaEntity::DisableTrigger);
	lua_register(Lua, "EntitySetTriggerCallback", &LuaEntity::SetTriggerCallback);

	lua_register(Lua, "EntitySetBindObject", &LuaEntity::SetBindObject);
	lua_register(Lua, "EntityEnableUpdateObject", &LuaEntity::EnableUpdateObject);
	lua_register(Lua, "EntityDisableUpdateObject", &LuaEntity::DisableUpdateObject);
	lua_register(Lua, "EntityClearForces", &LuaEntity::ClearForces);
}

int LuaEntity::CreateEntity(lua_State* tmpL){
	if(!Script.CheckInput(tmpL, 2)){
		ELOG("LuaEntity","CreateEntity","Bledna liczba parametrow!");
		return Script.ReturnString(tmpL, "");
	}
	if(!lua_isstring(tmpL, 1) || !lua_isnumber(tmpL, 2)){
		ELOG("LuaEntity","CreateEntity","Bledny typ parametrow!");
		return Script.ReturnString(tmpL, "");
	}
	std::string name = lua_tostring(tmpL, 1);

	if(name == ""){
		static unsigned long i = 0;
		name = Str(++i);
	}
	int type = (int)lua_tonumber(tmpL, 2);
	CEntity* entity;
	switch(type){
		case 0:
			entity = new CEntityEx(name);
			break;
		case 1:
			entity = new CEntity(name);
			break;
		default:
			return Script.ReturnString(tmpL, "");
			break;
	}
	if(EntityMgr.AddEntity(entity)){
		return Script.ReturnString(tmpL, name);
	}else{
		SAFE_DELETE(entity);
		return Script.ReturnString(tmpL, "");
	}
}
int LuaEntity::DeleteEntity(lua_State* tmpL){
	if(!Script.CheckInput(tmpL, 1)){
		ELOG("LuaEntity","DeleteEntity","Bledna liczba parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	if(!lua_isstring(tmpL, 1)){
		ELOG("LuaEntity","DeleteEntity","Bledny typ parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	std::string name = lua_tostring(tmpL, 1);
	EntityMgr.RemoveEntity(name);
	return 0;
}
int LuaEntity::SetPosition(lua_State* tmpL){
	if(!Script.CheckInput(tmpL, 4)){
		ELOG("LuaEntity","SetStartPosition","Bledna liczba parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	if(!lua_isstring(tmpL, 1) || !lua_isnumber(tmpL, 2)
		|| !lua_isnumber(tmpL, 3) || !lua_isnumber(tmpL, 4)){
			ELOG("LuaEntity","SetStartPosition","Bledny typ parametrow!");
			return Script.ReturnFalse(tmpL);
	}
	std::string name = lua_tostring(tmpL, 1);
	CEntity* tmpEntity = EntityMgr.GetEntity(name);
	if(tmpEntity){
		float x = (float)lua_tonumber(tmpL, 2);
		float y = (float)lua_tonumber(tmpL, 3);
		float z = (float)lua_tonumber(tmpL, 4);
		tmpEntity->SetStartPosition(D3DXVECTOR3(x, y, z));
		return Script.ReturnTrue(tmpL);
	}else{
		ELOG("LuaEntity","SetPosition",string("Nie mozna ustawic pozycji startowej! Nazwa: ")+name);
		return Script.ReturnFalse(tmpL);
	}
}
int LuaEntity::SetRotation(lua_State* tmpL){
	if(!Script.CheckInput(tmpL, 4)){
		ELOG("LuaEntity","SetStartRotation","Bledna liczba parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	if(!lua_isstring(tmpL, 1) || !lua_isnumber(tmpL, 2)
		|| !lua_isnumber(tmpL, 3) || !lua_isnumber(tmpL, 4)){
			ELOG("LuaEntity","SetStartRotation","Bledny typ parametrow!");
			return Script.ReturnFalse(tmpL);
	}
	std::string name = lua_tostring(tmpL, 1);
	CEntity* tmpEntity = EntityMgr.GetEntity(name);
	if(tmpEntity){
		float x = (float)lua_tonumber(tmpL, 2);
		float y = (float)lua_tonumber(tmpL, 3);
		float z = (float)lua_tonumber(tmpL, 4);
		tmpEntity->SetStartRotation(D3DXVECTOR3(x, y, z));
		return Script.ReturnTrue(tmpL);
	}else{
		ELOG("LuaEntity","SetRotation",string("Nie mozna ustawic rotacji startowej! Nazwa: ")+name);
		return Script.ReturnFalse(tmpL);
	}
}
int LuaEntity::SetScale(lua_State* tmpL){
	if(!Script.CheckInput(tmpL, 4)){
		ELOG("LuaEntity","SetStartScale","Bledna liczba parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	if(!lua_isstring(tmpL, 1) || !lua_isnumber(tmpL, 2)
		|| !lua_isnumber(tmpL, 3) || !lua_isnumber(tmpL, 4)){
			ELOG("LuaEntity","SetStartScale","Bledny typ parametrow!");
			return Script.ReturnFalse(tmpL);
	}
	std::string name = lua_tostring(tmpL, 1);
	CEntity* tmpEntity = EntityMgr.GetEntity(name);
	if(tmpEntity){
		float x = (float)lua_tonumber(tmpL, 2);
		float y = (float)lua_tonumber(tmpL, 3);
		float z = (float)lua_tonumber(tmpL, 4);
		tmpEntity->SetStartScale(D3DXVECTOR3(x, y, z));
		return Script.ReturnTrue(tmpL);
	}else{
		ELOG("LuaEntity","SetScale",string("Nie mozna ustawic skali startowej! Nazwa: ")+name);
		return Script.ReturnFalse(tmpL);
	}
}
int LuaEntity::GetPosition(lua_State* tmpL){
	if(!Script.CheckInput(tmpL, 1)){
		ELOG("LuaEntity","GetPosition","Bledna liczba parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	if(!lua_isstring(tmpL, 1)){
		ELOG("LuaEntity","GetPosition","Bledny typ parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	std::string name = lua_tostring(tmpL, 1);
	CEntity* tmpEntity = EntityMgr.GetEntity(name);
	if(tmpEntity){
		D3DXVECTOR3 tmpVec = tmpEntity->GetPosition();
		lua_pushnumber(tmpL, tmpVec.x);
		lua_pushnumber(tmpL, tmpVec.y);
		lua_pushnumber(tmpL, tmpVec.z);
		return 3;
	}else{
		ELOG("LuaEntity","GetPosition",string("Nie mozna pobrac pozycji! Nazwa: ")+name);
		return Script.ReturnFalse(tmpL);
	}

}
int LuaEntity::SetDynamic(lua_State* tmpL){
	if(!Script.CheckInput(tmpL, 2)){
		ELOG("LuaEntity","SetDynamic","Bledna liczba parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	if(!lua_isstring(tmpL, 2)){
		ELOG("LuaEntity","SetDynamic","Bledny typ parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	std::string name = lua_tostring(tmpL, 1);
	int type = (int)lua_tointeger(tmpL, 2);
	CEntityEx* tmpEntity = (CEntityEx*) EntityMgr.GetEntity(name);
	if(tmpEntity){
		if(type == 0){
			tmpEntity->SetDynamic(false);
		}else{
			tmpEntity->SetDynamic(true);
		}
		return Script.ReturnTrue(tmpL);
	}else{
		ELOG("LuaEntity","SetDynamic",string("Nie mozna ustawic Dynamic! Nazwa: ")+name);
		return Script.ReturnFalse(tmpL);
	}
}
int LuaEntity::SetAnimation(lua_State* tmpL){
	if(!Script.CheckInput(tmpL, 4)){
		ELOG("LuaEntity","SetAnimation","Bledna liczba parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	if(!lua_isstring(tmpL, 1) || !lua_isnumber(tmpL, 2)
		|| !lua_isnumber(tmpL, 3) || !lua_isnumber(tmpL, 4)){
			ELOG("LuaEntity","SetAnimation","Bledny typ parametrow!");
			return Script.ReturnFalse(tmpL);
	}
	std::string name = lua_tostring(tmpL, 1);
	CEntity* tmpEntity = EntityMgr.GetEntity(name);
	if(tmpEntity){
		float x = (float)lua_tonumber(tmpL, 2);
		float y = (float)lua_tonumber(tmpL, 3);
		float z = (float)lua_tonumber(tmpL, 4);
		tmpEntity->SetAnimation(x, y, z);
		return Script.ReturnTrue(tmpL);
	}else{
		ELOG("LuaEntity","SetAnimation",string("Nie mozna ustawic animacji! Nazwa: ")+name);
		return Script.ReturnFalse(tmpL);
	}
}
int LuaEntity::SetPhysxShape(lua_State* tmpL){
	if(!Script.CheckInput(tmpL, 2)){
		ELOG("LuaEntity","SetPhysxShape","Bledna liczba parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	if(!lua_isstring(tmpL, 1) || !lua_isnumber(tmpL, 2)){
		ELOG("LuaEntity","SetPhysxShape","Bledny typ parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	std::string name = lua_tostring(tmpL, 1);
	int type = (int)lua_tointeger(tmpL, 2);
	CEntityEx* tmpEntity = (CEntityEx*) EntityMgr.GetEntity(name);
	if(tmpEntity){
		switch(type){
			case 1: //box
				tmpEntity->SetPhysxShape(PX_BOX);
				break;
			case 2: //capsule
				tmpEntity->SetPhysxShape(PX_CAPSULE);
				break;
			case 3: //sphere
				tmpEntity->SetPhysxShape(PX_SPHERE);
				break;
			case 4: //triangle
				tmpEntity->SetPhysxShape(PX_TRIANGLE);
				break;
			case 5: //convex
				tmpEntity->SetPhysxShape(PX_CONVEX);
				break;
			default:
				return Script.ReturnFalse(tmpL);
				break;
		}
		return Script.ReturnTrue(tmpL);
	}else{
		return Script.ReturnFalse(tmpL);
	}
}
int LuaEntity::GetPhysxShape(lua_State* tmpL){
	if(!Script.CheckInput(tmpL, 1)){
		ELOG("LuaEntity","GetPhysxShape","Bledna liczba parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	if(!lua_isstring(tmpL, 1)){
		ELOG("LuaEntity","GetPhysxShape","Bledny typ parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	std::string name = lua_tostring(tmpL, 1);
	CEntityEx* tmpEntity = (CEntityEx*) EntityMgr.GetEntity(name);
	if(tmpEntity){
		PhysxShapeType typ = tmpEntity->GetPhysxShape();
		int typNumber = 0;
		switch(typ){
			case PX_BOX:
				typNumber = 1;
				break;
			case PX_CAPSULE:
				typNumber = 2;
				break;
			case PX_SPHERE:
				typNumber = 3;
				break;
			case PX_TRIANGLE:
				typNumber = 4;
				break;
			case PX_CONVEX:
				typNumber = 5;
				break;
		}
		if(typNumber == 0) return Script.ReturnFalse(tmpL);
		lua_pushnumber(tmpL, typNumber);
		return 1;
	}else{
		return Script.ReturnFalse(tmpL);
	}
}
int LuaEntity::SetMesh(lua_State* tmpL){
	if(!Script.CheckInput(tmpL, 2)){
		ELOG("LuaEntity","SetMesh","Bledna liczba parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	if(!lua_isstring(tmpL, 1) || !lua_isstring(tmpL, 2)){
		ELOG("LuaEntity","SetMesh","Bledny typ parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	std::string name = lua_tostring(tmpL, 1);
	std::string meshName = lua_tostring(tmpL, 2);
	CEntity* tmpEntity = EntityMgr.GetEntity(name);
	if(tmpEntity){
		bool result = tmpEntity->SetMesh(meshName);
		if(result){
			if(Scene.Add(tmpEntity)){
				return Script.ReturnTrue(tmpL);
			}else{
				ELOG("LuaEntity","SetMesh",string("Nie mozna dodac obiektu do sceny! Nazwa: ")+name);
				return Script.ReturnFalse(tmpL);
			}
		}else{
			ELOG("LuaEntity","SetMesh",string("Nie mozna ustawic mesha, SetMesh failed! Nazwa: ")+name);
			return Script.ReturnFalse(tmpL);
		}
	}else{
		ELOG("LuaEntity","SetMesh",string("Nie mozna ustawic mesha, entity nie istnieje! Nazwa: ")+name);
		return Script.ReturnFalse(tmpL);
	}
}
int LuaEntity::SetTexture(lua_State* tmpL){
	if(!Script.CheckInput(tmpL, 2)){
		ELOG("LuaEntity","SetTexture","Bledna liczba parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	if(!lua_isstring(tmpL, 1) || !lua_isstring(tmpL, 2)){
		ELOG("LuaEntity","SetTexture","Bledny typ parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	std::string name = lua_tostring(tmpL, 1);
	if(name == ""){
		return Script.ReturnFalse(tmpL);
	}
	std::string textureName = lua_tostring(tmpL, 2);
	CEntityEx* tmpEntity = (CEntityEx*) EntityMgr.GetEntity(name);
	if(tmpEntity){
		bool result = tmpEntity->SetTexture(textureName);
		if(result){
			return Script.ReturnTrue(tmpL);
		}else{
			return Script.ReturnFalse(tmpL);
		}
	}else{
		return Script.ReturnFalse(tmpL);
	}
}
int LuaEntity::SetNormalMap(lua_State* tmpL){
	if(!Script.CheckInput(tmpL, 2)){
		ELOG("LuaEntity","SetNormalMap","Bledna liczba parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	if(!lua_isstring(tmpL, 1) || !lua_isstring(tmpL, 2)){
		ELOG("LuaEntity","SetNormalMap","Bledny typ parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	std::string name = lua_tostring(tmpL, 1);
	if(name == ""){
		return Script.ReturnFalse(tmpL);
	}
	std::string textureName = lua_tostring(tmpL, 2);
	CEntity* tmpEntity = (CEntity*) EntityMgr.GetEntity(name);
	if(tmpEntity){
		bool result = tmpEntity->SetNormalMap(textureName, tmpEntity);
		if(result){
			return Script.ReturnTrue(tmpL);
		}else{
			return Script.ReturnFalse(tmpL);
		}
	}else{
		return Script.ReturnFalse(tmpL);
	}
}
int LuaEntity::SetActorAngularDamping(lua_State* tmpL){
	if(!Script.CheckInput(tmpL, 2)){
		ELOG("LuaEntity","SetActorAngularDamping","Bledna liczba parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	if(!lua_isstring(tmpL, 1) || !lua_isnumber(tmpL, 2)){
		ELOG("LuaEntity","SetActorAngularDamping","Bledny typ parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	std::string name = lua_tostring(tmpL, 1);
	float value = (float)lua_tonumber(tmpL, 2);
	CEntityEx* tmpEntity = (CEntityEx*) EntityMgr.GetEntity(name);
	if(tmpEntity){
		NxActor *tmpActor = tmpEntity->GetActor();
		if(tmpActor){
			tmpActor->setAngularDamping(value);
			return Script.ReturnTrue(tmpL);
		}
		return Script.ReturnFalse(tmpL);
	}else{
		return Script.ReturnFalse(tmpL);
	}
}
int LuaEntity::GetActorAngularDamping(lua_State* tmpL){
	if(!Script.CheckInput(tmpL, 1)){
		ELOG("LuaEntity","GetActorAngularDamping","Bledna liczba parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	if(!lua_isstring(tmpL, 1)){
		ELOG("LuaEntity","GetActorAngularDamping","Bledny typ parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	std::string name = lua_tostring(tmpL, 1);
	CEntityEx* tmpEntity = (CEntityEx*) EntityMgr.GetEntity(name);
	if(tmpEntity){
		NxActor *tmpActor = tmpEntity->GetActor();
		if(tmpActor){
			lua_pushnumber(tmpL, tmpActor->getAngularDamping());
			return 1;
		}
		return Script.ReturnFalse(tmpL);
	}else{
		return Script.ReturnFalse(tmpL);
	}
}
int LuaEntity::SetActorMaxAngularVelocity(lua_State* tmpL){
	if(!Script.CheckInput(tmpL, 2)){
		ELOG("LuaEntity","SetActorMaxAngularVelocity","Bledna liczba parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	if(!lua_isstring(tmpL, 1) || !lua_isnumber(tmpL, 2)){
		ELOG("LuaEntity","SetActorMaxAngularVelocity","Bledny typ parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	std::string name = lua_tostring(tmpL, 1);
	float value = (float)lua_tonumber(tmpL, 2);
	CEntityEx* tmpEntity = (CEntityEx*) EntityMgr.GetEntity(name);
	if(tmpEntity){
		NxActor *tmpActor = tmpEntity->GetActor();
		if(tmpActor){
			tmpActor->setMaxAngularVelocity(value);
			return Script.ReturnTrue(tmpL);
		}
		return Script.ReturnFalse(tmpL);
	}else{
		return Script.ReturnFalse(tmpL);
	}
}
int LuaEntity::GetActorMaxAngularVelocity(lua_State* tmpL){
	if(!Script.CheckInput(tmpL, 1)){
		ELOG("LuaEntity","GetActorMaxAngularVelocity","Bledna liczba parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	if(!lua_isstring(tmpL, 1)){
		ELOG("LuaEntity","GetActorMaxAngularVelocity","Bledny typ parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	std::string name = lua_tostring(tmpL, 1);
	CEntityEx* tmpEntity = (CEntityEx*) EntityMgr.GetEntity(name);
	if(tmpEntity){
		NxActor *tmpActor = tmpEntity->GetActor();
		if(tmpActor){
			lua_pushnumber(tmpL, tmpActor->getMaxAngularVelocity());
			return 1;
		}
		return Script.ReturnFalse(tmpL);
	}else{
		return Script.ReturnFalse(tmpL);
	}
}
int LuaEntity::SetActorMass(lua_State* tmpL){
	if(!Script.CheckInput(tmpL, 2)){
		ELOG("LuaEntity","SetActorMass","Bledna liczba parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	if(!lua_isstring(tmpL, 1) || !lua_isnumber(tmpL, 2)){
		ELOG("LuaEntity","SetActorMass","Bledny typ parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	std::string name = lua_tostring(tmpL, 1);
	float value = (float)lua_tonumber(tmpL, 2);
	CEntityEx* tmpEntity = (CEntityEx*) EntityMgr.GetEntity(name);
	if(tmpEntity){
		NxActor *tmpActor = tmpEntity->GetActor();
		if(tmpActor){
			tmpActor->setMass(value);
			return Script.ReturnTrue(tmpL);
		}
		return Script.ReturnFalse(tmpL);
	}else{
		return Script.ReturnFalse(tmpL);
	}
}
int LuaEntity::GetActorMass(lua_State* tmpL){
	if(!Script.CheckInput(tmpL, 1)){
		ELOG("LuaEntity","GetActorMass","Bledna liczba parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	if(!lua_isstring(tmpL, 1)){
		ELOG("LuaEntity","GetActorMass","Bledny typ parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	std::string name = lua_tostring(tmpL, 1);
	CEntityEx* tmpEntity = (CEntityEx*) EntityMgr.GetEntity(name);
	if(tmpEntity){
		NxActor *tmpActor = tmpEntity->GetActor();
		if(tmpActor){
			lua_pushnumber(tmpL, tmpActor->getMass());
			return 1;
		}
		return Script.ReturnFalse(tmpL);
	}else{
		return Script.ReturnFalse(tmpL);
	}
}
int LuaEntity::SetMaterialRestitution(lua_State* tmpL){
	if(!Script.CheckInput(tmpL, 2)){
		ELOG("LuaEntity","SetMaterialRestitution","Bledna liczba parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	if(!lua_isstring(tmpL, 1) || !lua_isnumber(tmpL, 2)){
		ELOG("LuaEntity","SetMaterialRestitution","Bledny typ parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	std::string name = lua_tostring(tmpL, 1);
	float value = (float)lua_tonumber(tmpL, 2);
	CEntityEx* tmpEntity = (CEntityEx*) EntityMgr.GetEntity(name);
	if(tmpEntity){
		NxMaterial *tmpMaterial = tmpEntity->GetMaterial();
		if(tmpMaterial){
			tmpMaterial->setRestitution(value);
			return Script.ReturnTrue(tmpL);
		}
		return Script.ReturnFalse(tmpL);
	}else{
		return Script.ReturnFalse(tmpL);
	}
}
int LuaEntity::GetMaterialRestitution(lua_State* tmpL){
	if(!Script.CheckInput(tmpL, 1)){
		ELOG("LuaEntity","GetMaterialRestitution","Bledna liczba parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	if(!lua_isstring(tmpL, 1)){
		ELOG("LuaEntity","GetMaterialRestitution","Bledny typ parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	std::string name = lua_tostring(tmpL, 1);
	CEntityEx* tmpEntity = (CEntityEx*) EntityMgr.GetEntity(name);
	if(tmpEntity){
		NxMaterial *tmpMaterial = tmpEntity->GetMaterial();
		if(tmpMaterial){
			lua_pushnumber(tmpL, tmpMaterial->getRestitution());
			return 1;
		}
		return Script.ReturnFalse(tmpL);
	}else{
		return Script.ReturnFalse(tmpL);
	}
}
int LuaEntity::SetMaterialStaticFriction(lua_State* tmpL){
	if(!Script.CheckInput(tmpL, 2)){
		ELOG("LuaEntity","SetMaterialStaticFriction","Bledna liczba parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	if(!lua_isstring(tmpL, 1) || !lua_isnumber(tmpL, 2)){
		ELOG("LuaEntity","SetMaterialStaticFriction","Bledny typ parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	std::string name = lua_tostring(tmpL, 1);
	float value = (float)lua_tonumber(tmpL, 2);
	CEntityEx* tmpEntity = (CEntityEx*) EntityMgr.GetEntity(name);
	if(tmpEntity){
		NxMaterial *tmpMaterial = tmpEntity->GetMaterial();
		if(tmpMaterial){
			tmpMaterial->setStaticFriction(value);
			return Script.ReturnTrue(tmpL);
		}
		return Script.ReturnFalse(tmpL);
	}else{
		return Script.ReturnFalse(tmpL);
	}
}
int LuaEntity::GetMaterialStaticFriction(lua_State* tmpL){
	if(!Script.CheckInput(tmpL, 1)){
		ELOG("LuaEntity","GetMaterialStaticFriction","Bledna liczba parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	if(!lua_isstring(tmpL, 1)){
		ELOG("LuaEntity","GetMaterialStaticFriction","Bledny typ parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	std::string name = lua_tostring(tmpL, 1);
	CEntityEx* tmpEntity = (CEntityEx*) EntityMgr.GetEntity(name);
	if(tmpEntity){
		NxMaterial *tmpMaterial = tmpEntity->GetMaterial();
		if(tmpMaterial){
			lua_pushnumber(tmpL, tmpMaterial->getStaticFriction());
			return 1;
		}
		return Script.ReturnFalse(tmpL);
	}else{
		return Script.ReturnFalse(tmpL);
	}
}
int LuaEntity::SetMaterialDynamicFriction(lua_State* tmpL){
	if(!Script.CheckInput(tmpL, 2)){
		ELOG("LuaEntity","SetMaterialDynamicFriction","Bledna liczba parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	if(!lua_isstring(tmpL, 1) || !lua_isnumber(tmpL, 2)){
		ELOG("LuaEntity","SetMaterialDynamicFriction","Bledny typ parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	std::string name = lua_tostring(tmpL, 1);
	float value = (float)lua_tonumber(tmpL, 2);
	CEntityEx* tmpEntity = (CEntityEx*) EntityMgr.GetEntity(name);
	if(tmpEntity){
		NxMaterial *tmpMaterial = tmpEntity->GetMaterial();
		if(tmpMaterial){
			tmpMaterial->setDynamicFriction(value);
			return Script.ReturnTrue(tmpL);
		}
		return Script.ReturnFalse(tmpL);
	}else{
		return Script.ReturnFalse(tmpL);
	}
}
int LuaEntity::GetMaterialDynamicFriction(lua_State* tmpL){
	if(!Script.CheckInput(tmpL, 1)){
		ELOG("LuaEntity","GetMaterialDynamicFriction","Bledna liczba parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	if(!lua_isstring(tmpL, 1)){
		ELOG("LuaEntity","GetMaterialDynamicFriction","Bledny typ parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	std::string name = lua_tostring(tmpL, 1);
	CEntityEx* tmpEntity = (CEntityEx*) EntityMgr.GetEntity(name);
	if(tmpEntity){
		NxMaterial *tmpMaterial = tmpEntity->GetMaterial();
		if(tmpMaterial){
			lua_pushnumber(tmpL, tmpMaterial->getDynamicFriction());
			return 1;
		}
		return Script.ReturnFalse(tmpL);
	}else{
		return Script.ReturnFalse(tmpL);
	}
}
int LuaEntity::RaiseBodyFlag(lua_State* tmpL){
	if(!Script.CheckInput(tmpL, 2)){
		ELOG("LuaEntity","RaiseBodyFlag","Bledna liczba parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	if(!lua_isstring(tmpL, 1) || !lua_isnumber(tmpL, 2)){
		ELOG("LuaEntity","RaiseBodyFlag","Bledny typ parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	std::string name = lua_tostring(tmpL, 1);
	int type = (int)lua_tointeger(tmpL, 2);
	CEntityEx* tmpEntity = (CEntityEx*) EntityMgr.GetEntity(name);
	if(tmpEntity){
		NxActor *tmpActor = tmpEntity->GetActor();
		if(tmpActor){
			switch(type){
			case 1: //NX_BF_KINEMATIC
				tmpActor->raiseBodyFlag(NX_BF_KINEMATIC);
				break;
			default:
				return Script.ReturnFalse(tmpL);
				break;
			}
			return Script.ReturnTrue(tmpL);
		}else{
			return Script.ReturnFalse(tmpL);
		}
	}else{
		return Script.ReturnFalse(tmpL);
	}
}
int LuaEntity::ClearBodyFlag(lua_State* tmpL){
	if(!Script.CheckInput(tmpL, 2)){
		ELOG("LuaEntity","ClearBodyFlag","Bledna liczba parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	if(!lua_isstring(tmpL, 1) || !lua_isnumber(tmpL, 2)){
		ELOG("LuaEntity","ClearBodyFlag","Bledny typ parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	std::string name = lua_tostring(tmpL, 1);
	int type = (int)lua_tointeger(tmpL, 2);
	CEntityEx* tmpEntity = (CEntityEx*) EntityMgr.GetEntity(name);
	if(tmpEntity){
		NxActor *tmpActor = tmpEntity->GetActor();
		if(tmpActor){
			switch(type){
			case 1: //NX_BF_KINEMATIC
				tmpActor->clearBodyFlag(NX_BF_KINEMATIC);
				break;
			default:
				return Script.ReturnFalse(tmpL);
				break;
			}
			return Script.ReturnTrue(tmpL);
		}else{
			return Script.ReturnFalse(tmpL);
		}
	}else{
		return Script.ReturnFalse(tmpL);
	}
}
int LuaEntity::SetCallback(lua_State* tmpL){
	if(!Script.CheckInput(tmpL, 3)){
		ELOG("LuaEntity","SetCallback","Bledna liczba parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	if(!lua_isstring(tmpL, 1) || !lua_isstring(tmpL, 2) || !lua_isnumber(tmpL, 3)){
		ELOG("LuaEntity","SetCallback","Bledny typ parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	std::string name = lua_tostring(tmpL, 1);
	std::string procedureName = lua_tostring(tmpL, 2);
	int type = (int)lua_tointeger(tmpL, 3);
	CEntityEx* tmpEntity = (CEntityEx*) EntityMgr.GetEntity(name);
	if(tmpEntity){
		/*
		Callback.onStartTouch = 1
		Callback.onEndTouch = 2
		Callback.onTouch = 3
		Callback.onImpact = 4
		Callback.onStartTouchForceThreshold = 5
		Callback.onEndTouchForceThreshold = 6
		Callback.onTouchForceThreshold = 7
		*/
		tmpEntity->GetActor()->setContactReportFlags(NX_NOTIFY_ALL);
		switch(type){
		case 1:
			tmpEntity->SetCallbackProcedure(NX_NOTIFY_ON_START_TOUCH, procedureName);
			break;
		case 2:
			tmpEntity->SetCallbackProcedure(NX_NOTIFY_ON_END_TOUCH, procedureName);
			break;
		case 3:
			tmpEntity->SetCallbackProcedure(NX_NOTIFY_ON_TOUCH, procedureName);
			break;
		case 4:
			tmpEntity->SetCallbackProcedure(NX_NOTIFY_ON_IMPACT, procedureName);
			break;
		case 5:
			tmpEntity->SetCallbackProcedure(NX_NOTIFY_ON_START_TOUCH_FORCE_THRESHOLD, procedureName);
			break;
		case 6:
			tmpEntity->SetCallbackProcedure(NX_NOTIFY_ON_END_TOUCH_FORCE_THRESHOLD, procedureName);
			break;
		case 7:
			tmpEntity->SetCallbackProcedure(NX_NOTIFY_ON_TOUCH_FORCE_THRESHOLD, procedureName);
			break;
		default:
			ELOG("LuaEntity","SetCallback","Nie przypisano funkcji do zdarzenia: bledny parametr zdarzenia!");
			return Script.ReturnFalse(tmpL);
			break;
		}
		return Script.ReturnTrue(tmpL);
	}else{
		ELOG("LuaEntity","SetCallback","Nie przypisano funkcji do zdarzenia: obiekt nie istnieje!");
		return Script.ReturnFalse(tmpL);
	}
}
//name, nazwa klasy (bez Update)
int LuaEntity::SetUpdateObject(lua_State* tmpL){
	if(!Script.CheckInput(tmpL, 2)){
		ELOG("LuaEntity","SetUpdateObject","Bledna liczba parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	if(!lua_isstring(tmpL, 1) || !lua_isstring(tmpL, 2)){
		ELOG("LuaEntity","SetUpdateObject","Bledny typ parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	std::string name = lua_tostring(tmpL, 1);
	std::string className = lua_tostring(tmpL, 2);
	if(className == "StoneControl"){
		CEntityEx* ent = (CEntityEx*) EntityMgr.GetEntity(name);
		if(ent){
			IUpdateable* tmpUp = ent->GetUpdateObject();
			if(tmpUp == NULL){
				CStoneControl* up = new CStoneControl(ent);
				ent->SetUpdateObject(up);
				LOG("LuaEntity","SetUpdateObject",string("Ustawiam obiekt sterowania dla obiektu: ") + name);
				return Script.ReturnTrue(tmpL);
			}else{
				tmpUp->Enable();
				LOG("LuaEntity","SetUpdateObject",string("Uaktywniam obiekt sterowania dla obiektu: ") + name);
				return Script.ReturnTrue(tmpL);
			}			
		}else{
			ELOG("LuaEntity","SetUpdateObject","Obiekt nie istnieje!");
			return Script.ReturnFalse(tmpL);
		}
	}else{ //else if i pozostale
		ELOG("LuaEntity","SetUpdateObject","Podana klasa nie istnieje!");
		return Script.ReturnFalse(tmpL);
	}
}
int LuaEntity::SetForceField(lua_State *tmpL){
	//nazwa, kierunekX, kierunekY, kiedynekZ, sila
	if(!Script.CheckInput(tmpL, 5)){
		ELOG("LuaEntity","SetForceField","Bledna liczba parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	if(!lua_isstring(tmpL, 1) || !lua_isnumber(tmpL, 2) || 
		!lua_isnumber(tmpL, 3) || !lua_isnumber(tmpL, 4) ||!lua_isnumber(tmpL, 5)){
			ELOG("LuaEntity","SetUpdateObject","Bledny typ parametrow!");
			return Script.ReturnFalse(tmpL);
	}
	std::string name = lua_tostring(tmpL, 1);
	float directionX = (float)lua_tonumber(tmpL, 2);
	float directionY = (float)lua_tonumber(tmpL, 3);
	float directionZ = (float)lua_tonumber(tmpL, 4);
	float force = (float)lua_tonumber(tmpL, 5);
	CEntityEx* ent = (CEntityEx*) EntityMgr.GetEntity(name);
	if(ent){
		ent->EnableForceField(D3DXVECTOR3(directionX, directionY, directionZ), force);
		return Script.ReturnTrue(tmpL);
	}else{
		ELOG("LuaEntity","SetForceField","Obiekt nie istnieje!");
		return Script.ReturnFalse(tmpL);
	}
}
int LuaEntity::EnableForceField(lua_State *tmpL){
	if(!Script.CheckInput(tmpL, 1)){
		ELOG("LuaEntity","EnableForceField","Bledna liczba parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	if(!lua_isstring(tmpL, 1)){
		ELOG("LuaEntity","EnableForceField","Bledny typ parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	std::string name = lua_tostring(tmpL, 1);
	CEntityEx* ent = (CEntityEx*) EntityMgr.GetEntity(name);
	if(ent){
		ent->GetForceField()->Enable(ent->GetActor());
		return Script.ReturnTrue(tmpL);
	}else{
		ELOG("LuaEntity","EnableForceField","Obiekt nie istnieje!");
		return Script.ReturnFalse(tmpL);
	}
}
int LuaEntity::DisableForceField(lua_State *tmpL){
	if(!Script.CheckInput(tmpL, 1)){
		ELOG("LuaEntity","DisableForceField","Bledna liczba parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	if(!lua_isstring(tmpL, 1)){
		ELOG("LuaEntity","DisableForceField","Bledny typ parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	std::string name = lua_tostring(tmpL, 1);
	CEntityEx* ent = (CEntityEx*) EntityMgr.GetEntity(name);
	if(ent){
		ent->GetForceField()->Disable();
		return Script.ReturnTrue(tmpL);
	}else{
		ELOG("LuaEntity","DisableForceField","Obiekt nie istnieje!");
		return Script.ReturnFalse(tmpL);
	}
}


int LuaEntity::SetTrigger(lua_State *tmpL){
	//nazwa, dimX, dimY, dimZ
	if(!Script.CheckInput(tmpL, 4)){
		ELOG("LuaEntity","SetTrigger","Bledna liczba parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	if(!lua_isstring(tmpL, 1) || !lua_isnumber(tmpL, 2) || 
		!lua_isnumber(tmpL, 3) || !lua_isnumber(tmpL, 4)){
			ELOG("LuaEntity","SetTrigger","Bledny typ parametrow!");
			return Script.ReturnFalse(tmpL);
	}
	std::string name = lua_tostring(tmpL, 1);
	float dimensionX = (float)lua_tonumber(tmpL, 2);
	float dimensionY = (float)lua_tonumber(tmpL, 3);
	float dimensionZ = (float)lua_tonumber(tmpL, 4);
	CEntityEx* ent = (CEntityEx*) EntityMgr.GetEntity(name);
	if(ent){
		ent->EnableTrigger(D3DXVECTOR3(dimensionX, dimensionY, dimensionZ));
		return Script.ReturnTrue(tmpL);
	}else{
		ELOG("LuaEntity","SetTrigger","Obiekt nie istnieje!");
		return Script.ReturnFalse(tmpL);
	}
}
int LuaEntity::EnableTrigger(lua_State *tmpL){
	if(!Script.CheckInput(tmpL, 1)){
		ELOG("LuaEntity","EnableTrigger","Bledna liczba parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	if(!lua_isstring(tmpL, 1)){
		ELOG("LuaEntity","EnableTrigger","Bledny typ parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	std::string name = lua_tostring(tmpL, 1);
	CEntityEx* ent = (CEntityEx*) EntityMgr.GetEntity(name);
	if(ent){
		ent->GetTrigger()->Enable();
		return Script.ReturnTrue(tmpL);
	}else{
		ELOG("LuaEntity","EnableTrigger","Obiekt nie istnieje!");
		return Script.ReturnFalse(tmpL);
	}
}
int LuaEntity::DisableTrigger(lua_State *tmpL){
	if(!Script.CheckInput(tmpL, 1)){
		ELOG("LuaEntity","DisableTrigger","Bledna liczba parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	if(!lua_isstring(tmpL, 1)){
		ELOG("LuaEntity","DisableTrigger","Bledny typ parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	std::string name = lua_tostring(tmpL, 1);
	CEntityEx* ent = (CEntityEx*) EntityMgr.GetEntity(name);
	if(ent){
		ent->GetTrigger()->Disable();
		return Script.ReturnTrue(tmpL);
	}else{
		ELOG("LuaEntity","DisableTrigger","Obiekt nie istnieje!");
		return Script.ReturnFalse(tmpL);
	}
}



int LuaEntity::SetBindObject(lua_State *tmpL){
	if(!Script.CheckInput(tmpL, 2)){
		ELOG("LuaEntity","SetBindObject","Bledna liczba parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	if(!lua_isstring(tmpL, 1) || !lua_isstring(tmpL, 2)){
		ELOG("LuaEntity","SetBindObject","Bledny typ parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	std::string name = lua_tostring(tmpL, 1);
	std::string name2 = lua_tostring(tmpL, 2);
	CEntityEx* ent = (CEntityEx*) EntityMgr.GetEntity(name);
	if(ent){
		CEntity* ent2 = (CEntity*) EntityMgr.GetEntity(name2);
		if(ent2){
			ent->SetBindObject(ent2);
			return Script.ReturnTrue(tmpL);
		}else{
			ELOG("LuaEntity","SetBindObject","Obiekt docelowy nie istnieje!");
			return Script.ReturnFalse(tmpL);
		}
	}else{
		ELOG("LuaEntity","SetBindObject","Obiekt zrodlowy nie istnieje!");
		return Script.ReturnFalse(tmpL);
	}
}
int LuaEntity::EnableUpdateObject(lua_State *tmpL){
	if(!Script.CheckInput(tmpL, 1)){
		ELOG("LuaEntity","EnableUpdateObject","Bledna liczba parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	if(!lua_isstring(tmpL, 1)){
		ELOG("LuaEntity","EnableUpdateObject","Bledny typ parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	std::string name = lua_tostring(tmpL, 1);
	CEntityEx* ent = (CEntityEx*) EntityMgr.GetEntity(name);
	if(ent){
		if(ent->GetUpdateObject() != NULL){
			ent->GetUpdateObject()->Enable();
			return Script.ReturnTrue(tmpL);
		}else{
			ELOG("LuaEntity","EnableUpdateObject","Obiekt nie istnieje!");
			return Script.ReturnFalse(tmpL);
		}
	}
	return Script.ReturnFalse(tmpL);
}
int LuaEntity::DisableUpdateObject(lua_State *tmpL){
	if(!Script.CheckInput(tmpL, 1)){
		ELOG("LuaEntity","DisableUpdateObject","Bledna liczba parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	if(!lua_isstring(tmpL, 1)){
		ELOG("LuaEntity","DisableUpdateObject","Bledny typ parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	std::string name = lua_tostring(tmpL, 1);
	CEntityEx* ent = (CEntityEx*) EntityMgr.GetEntity(name);
	if(ent){
		if(ent->GetUpdateObject() != NULL){
			ent->GetUpdateObject()->Disable();
			return Script.ReturnTrue(tmpL);
		}else{
			ELOG("LuaEntity","DisableUpdateObject","Obiekt nie istnieje!");
			return Script.ReturnFalse(tmpL);
		}
	}
	return Script.ReturnFalse(tmpL);
}
int LuaEntity::ClearForces(lua_State *tmpL){
	if(!Script.CheckInput(tmpL, 1)){
		ELOG("LuaEntity","ClearForces","Bledna liczba parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	if(!lua_isstring(tmpL, 1)){
		ELOG("LuaEntity","ClearForces","Bledny typ parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	std::string name = lua_tostring(tmpL, 1);
	CEntityEx* ent = (CEntityEx*) EntityMgr.GetEntity(name);
	if(ent){
		if(ent->GetUpdateObject() != NULL){
			ent->GetUpdateObject()->Stop();
			return Script.ReturnTrue(tmpL);
		}else{
			ELOG("LuaEntity","ClearForces","Obiekt nie istnieje!");
			return Script.ReturnFalse(tmpL);
		}
	}
	return Script.ReturnFalse(tmpL);
}
int LuaEntity::Show(lua_State *tmpL){
	if(!Script.CheckInput(tmpL, 1)){
		ELOG("LuaEntity","Show","Bledna liczba parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	if(!lua_isstring(tmpL, 1)){
		ELOG("LuaEntity","Show","Bledny typ parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	std::string name = lua_tostring(tmpL, 1);
	CEntity* ent = (CEntity*) EntityMgr.GetEntity(name);
	if(ent){
		if(ent != NULL){
			ent->Show();
			return Script.ReturnTrue(tmpL);
		}else{
			ELOG("LuaEntity","Show","Obiekt nie istnieje!");
			return Script.ReturnFalse(tmpL);
		}
	}
	return Script.ReturnFalse(tmpL);
}
int LuaEntity::Hide(lua_State *tmpL){
	if(!Script.CheckInput(tmpL, 1)){
		ELOG("LuaEntity","Hide","Bledna liczba parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	if(!lua_isstring(tmpL, 1)){
		ELOG("LuaEntity","Hide","Bledny typ parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	std::string name = lua_tostring(tmpL, 1);
	CEntity* ent = (CEntity*) EntityMgr.GetEntity(name);
	if(ent){
		if(ent != NULL){
			ent->Hide();
			return Script.ReturnTrue(tmpL);
		}else{
			ELOG("LuaEntity","Hide","Obiekt nie istnieje!");
			return Script.ReturnFalse(tmpL);
		}
	}
	return Script.ReturnFalse(tmpL);
}
int LuaEntity::SetTriggerCallback(lua_State* tmpL){
	if(!Script.CheckInput(tmpL, 3)){
		ELOG("LuaEntity","SetTriggerCallback","Bledna liczba parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	if(!lua_isstring(tmpL, 1) || !lua_isstring(tmpL, 2) || !lua_isnumber(tmpL, 3)){
		ELOG("LuaEntity","SetTriggerCallback","Bledny typ parametrow!");
		return Script.ReturnFalse(tmpL);
	}
	std::string name = lua_tostring(tmpL, 1);
	std::string procedureName = lua_tostring(tmpL, 2);
	int type = (int)lua_tointeger(tmpL, 3);
	CEntityEx* tmpEntity = (CEntityEx*) EntityMgr.GetEntity(name);
	if(tmpEntity){
		/*
		Trigger.onEnter = 1
		Trigger.onLeave = 2
		Trigger.onStay = 3
		*/
		switch(type){
		case 1:
			tmpEntity->SetTriggerProcedure(NX_TRIGGER_ON_ENTER, procedureName);
			break;
		case 2:
			tmpEntity->SetTriggerProcedure(NX_TRIGGER_ON_LEAVE, procedureName);
			break;
		case 3:
			tmpEntity->SetTriggerProcedure(NX_TRIGGER_ON_STAY, procedureName);
			break;
		default:
			ELOG("LuaEntity","SetTriggerCallback","Nie przypisano funkcji do zdarzenia: bledny parametr zdarzenia!");
			return Script.ReturnFalse(tmpL);
			break;
		}
		return Script.ReturnTrue(tmpL);
	}else{
		ELOG("LuaEntity","SetTriggerCallback","Nie przypisano funkcji do zdarzenia: obiekt nie istnieje!");
		return Script.ReturnFalse(tmpL);
	}
}