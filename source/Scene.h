#pragma once
#include "stdfx.h"
#include "Renderable.h"
#include <map>
using namespace std;
class NxScene;
class NxSceneDesc;
class CScene{
public:
	CScene(){
		scene=NULL;
		sceneDesc=NULL;
	}
	CScene(const CScene &){}
	CScene& operator=(const CScene&){}
	~CScene(){}
	static CScene& GetInstance(){
		static CScene inst;
		return inst;
	}
public:
	bool Init();
	void Update();
	void Render(RenderableShaderType tmpType);
	void Clear();

	NxScene* GetPhysxScene(){
		return scene;
	}
	NxSceneDesc* GetPhysxSceneDesc(){
		return sceneDesc;
	}
	bool Add(IRenderable* object);
	void Del(string name, RenderableShaderType tmpType);
	void DelAll();
	IRenderable* Get(string name, RenderableShaderType tmpType);

private:
	NxScene* scene;
	NxSceneDesc* sceneDesc;
	/* Kazda mape obiektow renderujemy innym shaderem */
	map<string, class IRenderable*> simpleObjects;
	map<string, class IRenderable*> normalMapObjects;
};
#define Scene CScene::GetInstance()