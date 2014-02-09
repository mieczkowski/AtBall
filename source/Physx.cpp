#include "stdfx.h"
#include "Physx.h"
#include "Logger.h"

class MyOutputStream : public NxUserOutputStream{
	void reportError (NxErrorCode code, const char *message, const char* file, int line){
		if (code < NXE_DB_INFO){
			MessageBox(NULL, message, "SDK Error", MB_OK);
		}
	}
	NxAssertResponse reportAssertViolation (const char *message, const char *file,int line){
		assert(0);
		return NX_AR_CONTINUE;
	}
	void print (const char *message){
		ELOG("CPhysx [MyOutputStream]","Physx Error",message);
	}
}myOutputStream;

bool CPhysx::Init(void){
	NxPhysicsSDKDesc desc;
	NxSDKCreateError errorCode = NXCE_NO_ERROR;
	gPhysicsSDK = NxCreatePhysicsSDK(NX_PHYSICS_SDK_VERSION, 0, 0, desc, &errorCode);
	if(gPhysicsSDK == NULL) 
	{
		ELOG("PhysxMgr","Init","Nie mozna utworzyc obiektu PhysxSDK!");
		//printf("\nSDK create error (%d - %s).\nUnable to initialize the PhysX SDK, exiting the sample.\n\n", errorCode, getNxSDKCreateError(errorCode));
		return false;
	}

	myAlloc = new MyAllocator();
	gPhysicsSDK->getFoundationSDK().getRemoteDebugger()->connect ("localhost", 5425);
	gPhysicsSDK->setParameter(NX_SKIN_WIDTH, 0.01f);//0.01
	gPhysicsSDK->setParameter(NX_VISUALIZATION_SCALE, 1);
	gPhysicsSDK->setParameter(NX_VISUALIZE_BODY_AXES, 1);
	gPhysicsSDK->setParameter(NX_VISUALIZE_COLLISION_SHAPES, 1);
	gPhysicsSDK->setParameter(NX_VISUALIZE_CONTACT_NORMAL, 1);
	gPhysicsSDK->setParameter(NX_VISUALIZE_CONTACT_POINT, 1);
	SetCookingInterface();
	if(!gCooking){
		ELOG("PhysxMgr","Init","Nie mozna utworzyæ obiektu PhysxCooking!");
		return false;
	}else{
		if(myAlloc!=NULL) gCooking->NxInitCooking(myAlloc,0);
		else ELOG("PhysxMgr","Init","Brak obiektu myAlloc, nie wykonano NxInitCooking!");
	}
	LOG("PhysxMgr","Init","Pomyslnie zainicjowano PhysxMgr.");
	return true;
}
void CPhysx::Clear(void){
	LOG("PhysxMgr","Clear","Niszczenie obiektu.");
	if(gPhysicsSDK)	gPhysicsSDK->release();
}

