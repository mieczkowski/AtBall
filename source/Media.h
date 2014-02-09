#pragma once
#include "stdfx.h"
#include <map>
using namespace std;
class CTexture;
class CMesh;

class CMedia{
public:
	CMedia(){}
	CMedia(const CMedia &){}
	CMedia& operator=(const CMedia&){}
	~CMedia(){}
public:
	static CMedia& GetInstance(){
		static CMedia inst;
		return inst;
	}
	void Clear();
	bool AddMesh(string name, CMesh* mesh);
	bool AddMesh(string name, string fileName);
	bool AddTexture(string name, CTexture* texture);
	bool AddTexture(string name, string fileName);
	CMesh* GetMesh(string name);
	CTexture* GetTexture(string name);
	void RemoveMesh(string name);
	void RemoveTexture(string name);
	void OnReset();
protected:
	map<string, class CMesh*> meshList;
	map<string, class CTexture*> textureList;
};
#define Media CMedia::GetInstance()