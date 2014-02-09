#include "Media.h"
#include "Logger.h"
#include "Mesh.h"
#include "Texture.h"
void CMedia::Clear(void){
	LOG("MediaMgr","Clear","Niszczenie obiektu.");
	if(textureList.empty() == false){
		for(map<string, CTexture*>::iterator itr = textureList.begin(); itr != textureList.end(); itr++){
			LOG("MediaMgr","Clear",string("Usuwanie tekstury: ") + itr->first);
			SAFE_DELETE(itr->second);
		}
		textureList.clear();
	}	
	if(meshList.empty() == false){
		for(map<string, CMesh*>::iterator itr = meshList.begin(); itr != meshList.end(); itr++){
			LOG("MediaMgr","Clear",string("Usuwanie mesha: ") + itr->first);
			SAFE_DELETE(itr->second);
		}
		meshList.clear();
	}	
}
bool CMedia::AddMesh(string name, string fileName){
	CMesh* tmpMesh = new CMesh();
	if(tmpMesh->Load(fileName)==false) return false;
	return AddMesh(name, tmpMesh);
}
bool CMedia::AddMesh(string name, CMesh *mesh){
	pair<map<string, CMesh*>::iterator, bool> ret;
	ret = meshList.insert(pair<string, CMesh*>(name, mesh));
	if(ret.second == false){
		ELOG("MediaMgr","AddMesh",string("Nie mozna dodaæ mesha do mapy! Nazwa: ") + name);
		return false;
	}else{
		LOG("MediaMgr","AddMesh",string("Dodano mesha do mapy , Nazwa: ") + name);
		return true;
	}
}
bool CMedia::AddTexture(string name, string fileName){
	CTexture* tmpTexture = new CTexture();
	if(tmpTexture->Load(fileName) == false){
		ELOG("MediaMgr","AddTexture",string("Nie mozna zaladowac textury! Nazwa: ") + name);
		return false;
	}
	return AddTexture(name, tmpTexture);
}
bool CMedia::AddTexture(string name, CTexture *texture)
{
	pair<map<string, CTexture*>::iterator, bool> ret;
	ret = textureList.insert(pair<string, CTexture*>(name, texture));
	if(ret.second == false){
		ELOG("MediaMgr","AddTexture",string("Nie mozna dodaæ tekstury do mapy! Nazwa: ") + name);
		return false;
	}else{
		LOG("MediaMgr","AddTexture",string("Dodano teksture do mapy , Nazwa: ") + name);
		return true;
	}
}

CMesh* CMedia::GetMesh(string name){
	map<string, CMesh*>::iterator itr = meshList.find(name);
	if(itr != meshList.end()){
		return itr->second;
	}else{
		ELOG("MediaMgr","GetMesh",string("Obiekt mesh nie istnieje! Nazwa: ") + name);
		return NULL;
	}
}

CTexture* CMedia::GetTexture(string name){
	map<string, CTexture*>::iterator itr = textureList.find(name);
	if(itr != textureList.end()){
		return itr->second;
	}else{
		ELOG("MediaMgr","GetTexture",string("Obiekt texture nie istnieje! Nazwa: ") + name);
		return NULL;
	}
}

void CMedia::RemoveMesh(string name){
	map<string, CMesh*>::iterator itr = meshList.find(name);
	if(itr != meshList.end()){
		LOG("MediaMgr","RemoveMesh",string("Usuwam mesha! Nazwa: ") + name);
		itr->second->Clear();
		SAFE_DELETE(itr->second);
		meshList.erase(itr);
	}
	return;
}

void CMedia::RemoveTexture(string name){
	map<string, CTexture*>::iterator itr = textureList.find(name);
	if(itr != textureList.end()){
		LOG("MediaMgr","RemoveTexture",string("Usuwam texture! Nazwa: ") + name);
		itr->second->Clear();
		SAFE_DELETE(itr->second);
		textureList.erase(itr);
	}
	return;
}
void CMedia::OnReset(){
	if(textureList.empty() == false){
		for(map<string, CTexture*>::iterator itr = textureList.begin(); itr != textureList.end(); itr++){
			itr->second->Reload();
		}
	}
}