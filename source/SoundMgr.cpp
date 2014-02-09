#include "SoundMgr.h"
#include "Logger.h"
#include "Camera.h"
#include "Renderable.h"
CSoundMgr& CSoundMgr::GetInstance(){
	static CSoundMgr inst;
	return inst;
}
void CSoundMgr::Clear(){
	LOG("SoundMgr", "Clear", "Czyszczenie obiektu.");
	engine->stopAllSounds();
	if(sounds.empty() != true){
		for(map<string, CSound*>::iterator itr = sounds.begin(); itr != sounds.end(); itr++){
			LOG("SoundMgr","Clear",string("Usuwanie obiektu dzwieku: ") + itr->first);
			SAFE_DELETE(itr->second);
		}
		sounds.clear();
	}
	if(files.empty() != true) files.clear();
	
}
bool CSoundMgr::Init(){
	engine = createIrrKlangDevice();
	if(engine){
		//engine->setDefault3DSoundMinDistance(5.0f);
		LOG("SoundMgr","Init","Pomyslnie zainicjowano system dzwieku! ");
		return true;
	}else{
		ELOG("SoundMgr","Init","Nie mozna zainicjowac systemu dzwieku! ");
		return false;
	}
}
void CSoundMgr::PauseAll(){
	engine->setAllSoundsPaused(true);
// 	if(sounds.empty() != true){
// 		for(map<string, CSound*>::iterator itr = sounds.begin(); itr != sounds.end(); itr++){
// 			itr->second->Pause();
// 			
// 		}
// 	}
}
void CSoundMgr::ResumeAll(){
	engine->setAllSoundsPaused(false);
// 	if(sounds.empty() != true){
// 		for(map<string, CSound*>::iterator itr = sounds.begin(); itr != sounds.end(); itr++){
// 			itr->second->Resume();
// 		}
// 	}
}
bool CSoundMgr::Update(){
	map<string, CSound*>::iterator itr = sounds.begin();
	map<string, CSound*>::iterator itr2 = sounds.end();
	map<string, CSound*>::iterator itrTmp;
	while(itr != itr2){
		if(itr->second){
			if(itr->second->IsFinished() == true){
				SAFE_DELETE(itr->second);
				itrTmp = itr;
				++itr;
				sounds.erase(itrTmp);
			}else{
				itr->second->Update();
				itr++;
			}
		}else{
			ELOG("SoundMgr","Update",string("Dzwiek nie istnieje!") + itr->first);
			itr++;
		}
	}
	D3DXVECTOR3 camPos = Camera.GetPosition();
	D3DXVECTOR3 camLook = Camera.GetLookAt();
	engine->setListenerPosition(vec3df(camPos.x, camPos.y, camPos.z), vec3df(camLook.x, camLook.y, camLook.z));
	engine->update();
	return true;
}
void CSoundMgr::AddFile(string name, string filename){
	LOG("SoundMgr","AddFile",string("Dodaje plik do mapy: ") + filename);
	files[name] = filename;
}
string CSoundMgr::GetFile(string name){
	return files[name];
}
void CSoundMgr::DelFile(string name){
	files[name] = "";
}
bool CSoundMgr::Play2D(string name, string file, bool loop){
	string filename = files[file];
	if(filename != ""){
		if(name == ""){
			engine->play2D(filename.c_str(), loop, false);
			return true;
		}else{
			CSound *tmpSound = new CSound();
			if(tmpSound->Play(filename, loop) == true){
				sounds[name] = tmpSound;
				return true;
			}else{
				SAFE_DELETE(tmpSound);
				ELOG("SoundMgr","Play2D",string("Nie mozna odtworzyc dzwieku: ") + name);
				return false;
			}
		}
	}else{
		ELOG("SoundMgr","Play2D",string("Plik nie istnieje: ") + file);
		return false;
	}
}
bool CSoundMgr::Play3D(string name, string file, bool loop, IRenderable* followedObject, bool follow){
	string filename = files[file];
	if(filename != ""){
		if(followedObject != NULL){
			if(name == ""){
				D3DXVECTOR3 tmpPos = followedObject->GetPosition();
				engine->play3D(filename.c_str(), vec3df(tmpPos.x, tmpPos.y, tmpPos.z), loop, false, false);
				return true;
			}else{
				CSound3D *tmpSound = new CSound3D();
				if(tmpSound->Play(filename, loop, followedObject, follow) == true){
					sounds[name] = tmpSound;
					return true;
				}else{
					SAFE_DELETE(tmpSound);
					ELOG("SoundMgr","Play3D",string("Nie mozna odtworzyc dzwieku: ") + name);
					return false;
				}
			}
		}else{
			ELOG("SoundMgr","Play3D",string("Obiekt do sledzenia nie istnieje!: ") + file);
			return false;
		}		
	}else{
		ELOG("SoundMgr","Play3D",string("Plik nie istnieje: ") + file);
		return false;
	}
}
bool CSoundMgr::Play3D(string name, string file, bool loop, vec3df position){
	string filename = files[file];
	if(filename != ""){
		if(name == ""){
			engine->play3D(filename.c_str(), position, loop, false, false);
			return true;
		}else{
			CSound3D *tmpSound = new CSound3D();
			if(tmpSound->Play(filename, loop, position) == true){
				sounds[name] = tmpSound;
				return true;
			}else{
				SAFE_DELETE(tmpSound);
				ELOG("SoundMgr","Play3D",string("Nie mozna odtworzyc dzwieku: ") + name);
				return false;
			}
		}
	}else{
		ELOG("SoundMgr","Play3D",string("Plik nie istnieje: ") + file);
		return false;
	}
}

ISoundEngine* CSoundMgr::GetEngine(){
	return engine;
}

CSound* CSoundMgr::GetSound(string name){
	map<string, CSound*>::iterator itr = sounds.find(name);
	if(itr != sounds.end()){
		return itr->second;
	}else{
		return NULL;
	}
}