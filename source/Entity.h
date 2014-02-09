#pragma once
#include "stdfx.h"
#include "Renderable.h"
#include "Updateable.h"
#include "Physx.h"
#include <map>
using namespace std;

enum FcShapeType{FC_BOX, FC_SPHERE, FC_NONE};
enum PhysxShapeType{PX_BOX, PX_CAPSULE, PX_SPHERE, PX_TRIANGLE, PX_CONVEX, PX_NONE};
class CMesh;
class CTexture;
class CFrustrumShape;
class CForceField;
class CTrigger;
class CAnimation;
//podstawowa klasa jednostki bez obslugi aktora PhysX'owego
class CEntity : public IRenderable{
public:
	CEntity(string _name);
	~CEntity(){}
	virtual void Clear(){}
	virtual void Render();
	virtual void RenderEx();
	virtual void RenderEx(D3DXMATRIX world);
	virtual void Update();
	virtual bool SetMesh(string meshName);
	virtual CMesh* GetMesh(){return mesh;}
	virtual bool SetTexture(string textureName);
	virtual CTexture* GetTexture(){ return texture; }
	virtual D3DXVECTOR3 GetPosition();
	virtual void SetStartPosition(D3DXVECTOR3 tmpStartPosition);
	virtual void SetStartRotation(D3DXVECTOR3 tmpRotation);
	virtual void SetStartScale(D3DXVECTOR3 tmpScale);
	virtual D3DXMATRIX GetMatrix();
	virtual D3DXMATRIX GetRotationMatrix();
	virtual bool SetNormalMap(string name, IRenderable* entity);
	virtual CTexture* GetNormalMap(){ return normalMap; }
	virtual void SetAnimation(float x, float y, float z);
protected:
	CMesh* mesh;
	CTexture* texture;
	FcShapeType fcShapeType;
	D3DXMATRIX matRotate, matTranslate, matScale;
	D3DXVECTOR3 position;
	D3DXVECTOR3 scale;
	D3DXVECTOR3 rotation;
	CFrustrumShape* frustrumShape;
	CTexture* normalMap;
	D3DXVECTOR3 rotationSpeed;
};

//rozszerzona klasa jednostki, zawiera aktora PhysX'owego
class CEntityEx : public CEntity{
public:
	CEntityEx(string _name);
	~CEntityEx(){ Clear(); }
	virtual void Clear();

	virtual void Update();
	virtual void SetUpdateObject(IUpdateable* obiect){updateObject = obiect;}
	virtual IUpdateable* GetUpdateObject(){return updateObject;}
	virtual void Render();
	virtual void RenderEx(); //wlasciwa metoda renderujaca (wywolywana przez Render() )

	virtual bool SetMesh(string meshName);

	virtual D3DXVECTOR3 GetPosition();

	virtual void Show();
	virtual void Hide();

	virtual NxMaterial* GetMaterial();
	virtual void SetStartRotation(D3DXVECTOR3 tmpRotation);
	virtual void SetPhysxShape(PhysxShapeType type){physxShapeType = type;}
	virtual PhysxShapeType GetPhysxShape(){return physxShapeType;}
	virtual NxShapeDesc* GetShapeDesc();
	virtual NxActor* GetActor(){return actor;}
	
	virtual D3DXMATRIX GetMatrix();

	virtual void SetCallbackProcedure(NxContactPairFlag flag, string name){callbackProcedures[flag] = name;}
	virtual string GetCallbackProcedure(NxContactPairFlag flag){return callbackProcedures[flag];}
	virtual void SetTriggerProcedure(NxShapeFlag flag, string name){triggerProcedures[flag] = name;}
	virtual string GetTriggerProcedure(NxShapeFlag flag){return triggerProcedures[flag];}

	virtual void SetDynamic(bool _dynamic){dynamic = _dynamic;}

	void EnableForceField(D3DXVECTOR3 direction, float force);
	CForceField* GetForceField(){return forceField;}

	void EnableTrigger(D3DXVECTOR3 dim);
	CTrigger* GetTrigger(){return trigger;}

	void SetBindObject(CEntity* ent);
	CEntity* GetBindObject(){return bindObject;}
protected:
	NxActor* actor;
	IUpdateable* updateObject;
	bool dynamic;
	PhysxShapeType physxShapeType;
	NxMaterialIndex materialIndex;
	NxQuat rotationQuat;
	CForceField* forceField;
	CTrigger* trigger;
	map<NxContactPairFlag, string> callbackProcedures;
	map<NxShapeFlag, string> triggerProcedures;
	CEntity* bindObject;

	bool outOfScene, outOfScene2;
};

