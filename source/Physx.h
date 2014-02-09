#pragma once

#include <NxPhysics.h>
#include <NxCharacter.h>
#include <NxCooking.h>
#include <NxStream.h>
#include <PhysXLoader.h>
#include "MyAllocator.h"

#if defined(WIN32) || defined(LINUX) || defined(__CELLOS_LV2__)
	#if NX_SDK_VERSION_NUMBER >= 250
		#define COOKING_INTERFACE 1
	#endif
#endif

class CPhysx
{
public:
	CPhysx(void){
		gPhysicsSDK=NULL;
		gCooking=NULL;
		myAlloc=NULL;
	}
	CPhysx(const CPhysx &){}
	CPhysx& operator=(const CPhysx&){}
	~CPhysx(void){}

public:
	static CPhysx& GetInstance(){
		static CPhysx inst;
		return inst;
	}
	bool Init();
	void Clear();
	void SetCookingInterface(){gCooking = NxGetCookingLib(NX_PHYSICS_SDK_VERSION);}
	NxPhysicsSDK* GetPhysicsSDK(){return gPhysicsSDK;}
	NxCookingInterface* GetCookingInterface(){return gCooking;}
	MyAllocator* GetAllocator(){return myAlloc;}

private:
	NxPhysicsSDK* gPhysicsSDK;
	NxCookingInterface* gCooking;
	MyAllocator* myAlloc;
};
#define Physx CPhysx::GetInstance()