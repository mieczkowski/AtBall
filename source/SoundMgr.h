#pragma once
#include "stdfx.h"
#include <map>
#include "inc/irrklang/irrKlang.h"
using namespace irrklang;
class CSound;
class IRenderable;
class CSoundMgr{
private:
	CSoundMgr(){ Init(); }
	CSoundMgr(const CSoundMgr &){}
	CSoundMgr& operator=(const CSoundMgr&){}
public:
	~CSoundMgr(){}
	static CSoundMgr& GetInstance();
	void Clear();

	bool Init();
	bool Update();
	void PauseAll();
	void ResumeAll();
	void AddFile(string name, string filename);
	string GetFile(string name);
	void DelFile(string name);
	CSound* GetSound(string name);
	bool Play2D(string name, string file, bool loop);
	bool Play3D(string name, string file, bool loop, IRenderable* followedObject, bool follow = false);
	bool Play3D(string name, string file, bool loop, vec3df position);

	ISoundEngine* GetEngine();
protected:
	ISoundEngine* engine;
	map<string, string> files;
	map<string, CSound*> sounds;
};

#define SoundMgr CSoundMgr::GetInstance()

class CSound{
public:
	CSound(){sound = NULL;}
	~CSound(){Clear();}
	virtual void Clear();
	virtual bool Update();
	virtual bool Play(string filename, bool loop);
	virtual void Stop();
	virtual void StopLoop();
	virtual void Pause();
	virtual void Resume();
	virtual bool IsFinished();
	virtual bool IsPlaying();
protected:
	ISound* sound;
};
class CSound3D : public CSound{
public:
	CSound3D();
	~CSound3D(){}
	bool Update();
	bool Play(string filename, bool loop, IRenderable* _followedObject, bool _follow = false);
	bool Play(string filename, bool loop, vec3df pos);

	vec3df position;
	IRenderable* followedObject;
	bool follow;

};

