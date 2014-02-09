#include "Scene.h"
#include "Physx.h"
#include "CollisionResponse.h"
#include "Logger.h"
#include "TriggerCallback.h"
#include "Game.h"

bool CScene::Init(){
	if(!Physx.GetPhysicsSDK())	{
		ELOG("Scene","Init","Brak obiektu PhysxSDK!");
		return false;
	}

	sceneDesc = new NxSceneDesc();

	sceneDesc->gravity = NxVec3(0.0f, -9.81f, 0.0f);
	sceneDesc->userContactReport = new CCollisionResponse();
	sceneDesc->userTriggerReport = new CTriggerCallback();
	if(sceneDesc->isValid()){
		scene = Physx.GetPhysicsSDK()->createScene(*sceneDesc);
	}else{
		ELOG("Scene","Init","Nie mozna by³o utworzyæ Physx Scene, nieprawid³owy sceneDesc!");
		return false;
	}

	if(!scene){
		ELOG("Scene","Init","Nie mozna by³o utworzyæ Physx Scene!");
		return false;
	}

	LOG("Scene","Init","Pomyslnie utworzono CScene");

	NxPlaneShapeDesc planeDesc;
	NxActorDesc actorDesc;


	planeDesc.normal = NxVec3(0.0f,1.0f,0.0f);
	planeDesc.d = -250.0f;

	actorDesc.shapes.pushBack(&planeDesc);
	actorDesc.name = "bottomPlaneX8764XFYTFE";

	NxActor *planeActor = scene->createActor(actorDesc);
	return true;
}

void CScene::Clear(){
	if(simpleObjects.empty() == false) simpleObjects.clear();
	if(normalMapObjects.empty() == false) normalMapObjects.clear();
	Physx.GetPhysicsSDK()->releaseScene(*scene);
	scene=NULL;
	return;
}

void CScene::Update(){
	if(Game.GetStatus() == game){
		scene->simulate(1.0f/60.0f);
		scene->flushStream();
		scene->fetchResults(NX_RIGID_BODY_FINISHED, true);
	}	
	if(simpleObjects.empty() == false){
		for(map<string, IRenderable*>::iterator itr = simpleObjects.begin(); itr != simpleObjects.end(); itr++){
			if(itr->second){
				itr->second->Update();
			}
		}
	}
	if(normalMapObjects.empty() == false){
		for(map<string, IRenderable*>::iterator itr = normalMapObjects.begin(); itr != normalMapObjects.end(); itr++){
			if(itr->second){
				itr->second->Update();
			}
		}
	}
	return;
}

void CScene::Render(RenderableShaderType tmpType){
	map<string, class IRenderable*> *tmpMap;
	switch(tmpType){
		case RST_NORMALMAP:
			tmpMap = &normalMapObjects;
			break;
		case RST_SIMPLE:
			tmpMap = &simpleObjects;
			break;
		default:
			return;
	}

	if(tmpMap->empty() == false){
		for(map<string, IRenderable*>::iterator itr = tmpMap->begin(); itr != tmpMap->end(); itr++){
			if(itr->second){
				itr->second->Render();
			}else{
				ELOG("Scene","Render",string("Nie da sie wyrenderowaæ obiektu: " + itr->second->GetName()));
			}
		}
	}
}

bool CScene::Add(IRenderable* object){
	map<string, class IRenderable*> *tmpMap;
	switch(object->GetType()){
		case RST_NORMALMAP:
			tmpMap = &normalMapObjects;
			break;
		case RST_SIMPLE:
			tmpMap = &simpleObjects;
			break;
		default:
			return false;
	}
	pair<map<string, IRenderable*>::iterator, bool> ret;
	ret = tmpMap->insert(pair<string, IRenderable*>(object->GetName(), object));
	if(ret.second == false){
		ELOG("CScene","AddObject",string("Nie mozna dodaæ obiektu do mapy sceny! Nazwa: ") + object->GetName());
		return false;
	}else{
		LOG("CScene","AddObject",string("Dodano obiekt do mapy sceny, Nazwa: ") + object->GetName());
		return true;
	}
}

IRenderable* CScene::Get(string name, RenderableShaderType tmpType){
	map<string, class IRenderable*> *tmpMap;
	switch(tmpType){
		case RST_NORMALMAP:
			tmpMap = &normalMapObjects;
			break;
		case RST_SIMPLE:
			tmpMap = &simpleObjects;
			break;
		default:
			return NULL;
	}

	map<string, IRenderable*>::iterator itr = tmpMap->find(name);
	if(itr != tmpMap->end()){
		return itr->second;
	}else{
		ELOG("CScene","GetObject",string("Obiekt nie istnieje! Nazwa: ") + name);
		return NULL;
	}
}

void CScene::Del(string name, RenderableShaderType tmpType){
	map<string, class IRenderable*> *tmpMap;
	switch(tmpType){
		case RST_NORMALMAP:
			tmpMap = &normalMapObjects;
			break;
		case RST_SIMPLE:
			tmpMap = &simpleObjects;
			break;
		default:
			return;
	}

	map<string, IRenderable*>::iterator itr = tmpMap->find(name);
	if(itr != tmpMap->end()){
		LOG("CScene","RemoveObject",string("Usuwam obiekt ! Nazwa: ") + name);
		//SAFE_DELETE(itr->second);
		simpleObjects.erase(itr);
	}
	return;
}
void CScene::DelAll(){
	if(simpleObjects.empty() == false)	simpleObjects.clear();
	if(normalMapObjects.empty() == false)	normalMapObjects.clear();
}
