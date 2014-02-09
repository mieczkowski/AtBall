#include "stdfx.h"
#include "Logger.h"
#include "SoundMgr.h"
#include "Renderable.h"

/*
1. default: dzwiek na pozycji kamery (sluchacza) np muzyka w tle
2. position: okreslona pozycja jednorazowa (np uderzenie kamienia w cos i w tym
miejscu dzwiek jest)
3. follow: dzwiek pod¹¿a za obiektem (np jak turla sie kula czy obiekt coœ mówi)
*/
void CSound::Clear(){
	if(sound) sound->drop();
}
bool CSound::Update(){
	//tutaj nic nie trzeba uaktualniac (dzwiek 2d)
	return true;
}


bool CSound::Play(string filename, bool loop){
	sound = SoundMgr.GetEngine()->play2D(filename.c_str(),loop,false,true);
	if(!sound) return false;
	return true;
}

void CSound::Stop(){
	if(sound) sound->stop();
}
void CSound::StopLoop(){
	if(sound) sound->setIsLooped(false);
}
void CSound::Pause(){
	if(sound) sound->setIsPaused(true);
}

void CSound::Resume(){
	if(sound) sound->setIsPaused(false);
}

bool CSound::IsFinished(){
	return (sound)? sound->isFinished() : true;
}

bool CSound::IsPlaying(){
	return (sound)? (!sound->getIsPaused()) : false;
}

/******************************************/
CSound3D::CSound3D(){
	position.X = 0.0f; position.Y = 0.0f; position.Z = 0.0f;
	followedObject = NULL;
	follow = false;
}
bool CSound3D::Update(){
	if(follow == true && followedObject != NULL){
		D3DXVECTOR3 tmpPos = followedObject->GetPosition();
		position.X = tmpPos.x;
		position.Y = tmpPos.y;
		position.Z = tmpPos.z;
		sound->setPosition(position);
	}
 	return true;
}

bool CSound3D::Play(string filename, bool loop, IRenderable* _followedObject, bool _follow){
	if(_followedObject != NULL){
		D3DXVECTOR3 tmpPos = _followedObject->GetPosition();
		position.X = tmpPos.x;
		position.Y = tmpPos.y;
		position.Z = tmpPos.z;
		sound = SoundMgr.GetEngine()->play3D(filename.c_str(), position, loop, false, true);
		if(!sound) return false;
		followedObject = _followedObject;
		follow = _follow;
		return true;
	}else{
		ELOG("CSound3D","Play","Obiekt do sledzenia nie istnieje: ");
		return false;
	}
}
bool CSound3D::Play(string filename, bool loop, vec3df pos){
	position = pos;
	sound = SoundMgr.GetEngine()->play3D(filename.c_str(), position, loop, false, true);
	if(!sound) return false;
	//followedObject = NULL;
	follow = false;
	return true;
}
