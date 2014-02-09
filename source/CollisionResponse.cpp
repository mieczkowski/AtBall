#include "CollisionResponse.h"
#include "Script.h"
#include "Game.h"
#include "Entity.h"
#include "EntityMgr.h"
#include "Logger.h"
void CCollisionResponse::onContactNotify(NxContactPair& pair, NxU32 events){
	// 	string type0 = (string)pair.actors[0]->userData;
	// 	string type1 = (string)pair.actors[1]->userData;
	// bottomPlaneX8764XFYTFE
	if(pair.actors[0]->getName() != "bottomPlaneX8764XFYTFE" && pair.actors[1]->getName() != "bottomPlaneX8764XFYTFE"){
		if(!pair.isDeletedActor[0] && !pair.isDeletedActor[1]){
			CEntityEx* ent0 = (CEntityEx*) EntityMgr.GetEntity(pair.actors[0]->getName());
			CEntityEx* ent1 = (CEntityEx*) EntityMgr.GetEntity(pair.actors[1]->getName());
			if(ent0 != NULL && ent1 != NULL){
				if(events & NX_NOTIFY_ON_START_TOUCH){
					string procedure = ent0->GetCallbackProcedure(NX_NOTIFY_ON_START_TOUCH);
					if(procedure != ""){
						Script.CallFunction(Game.GetActualLevel(), procedure, ent0->GetName(), ent1->GetName());
					}
					procedure = ent1->GetCallbackProcedure(NX_NOTIFY_ON_START_TOUCH);
					if(procedure != ""){
						Script.CallFunction(Game.GetActualLevel(), procedure, ent1->GetName(), ent0->GetName());
					}
				}
				if(events & NX_NOTIFY_ON_END_TOUCH){
					string procedure = ent0->GetCallbackProcedure(NX_NOTIFY_ON_END_TOUCH);
					if(procedure != ""){
						Script.CallFunction(Game.GetActualLevel(), procedure, ent0->GetName(), ent1->GetName());
					}
					procedure = ent1->GetCallbackProcedure(NX_NOTIFY_ON_END_TOUCH);
					if(procedure != ""){
						Script.CallFunction(Game.GetActualLevel(), procedure, ent1->GetName(), ent0->GetName());
					}
				}
				if(events & NX_NOTIFY_ON_TOUCH){
					string procedure = ent0->GetCallbackProcedure(NX_NOTIFY_ON_TOUCH);
					if(procedure != ""){
						Script.CallFunction(Game.GetActualLevel(), procedure, ent0->GetName(), ent1->GetName());
					}
					procedure = ent1->GetCallbackProcedure(NX_NOTIFY_ON_TOUCH);
					if(procedure != ""){
						Script.CallFunction(Game.GetActualLevel(), procedure, ent1->GetName(), ent0->GetName());
					}
				}
				if(events & NX_NOTIFY_ON_IMPACT){
					string procedure = ent0->GetCallbackProcedure(NX_NOTIFY_ON_IMPACT);
					if(procedure != ""){
						Script.CallFunction(Game.GetActualLevel(), procedure, ent0->GetName(), ent1->GetName());
					}
					procedure = ent1->GetCallbackProcedure(NX_NOTIFY_ON_IMPACT);
					if(procedure != ""){
						Script.CallFunction(Game.GetActualLevel(), procedure, ent1->GetName(), ent0->GetName());
					}
				}
				if(events & NX_NOTIFY_ON_START_TOUCH_FORCE_THRESHOLD){
					string procedure = ent0->GetCallbackProcedure(NX_NOTIFY_ON_START_TOUCH_FORCE_THRESHOLD);
					if(procedure != ""){
						Script.CallFunction(Game.GetActualLevel(), procedure, ent0->GetName(), ent1->GetName());
					}
					procedure = ent1->GetCallbackProcedure(NX_NOTIFY_ON_START_TOUCH_FORCE_THRESHOLD);
					if(procedure != ""){
						Script.CallFunction(Game.GetActualLevel(), procedure, ent1->GetName(), ent0->GetName());
					}
				}
				if(events & NX_NOTIFY_ON_END_TOUCH_FORCE_THRESHOLD){
					string procedure = ent0->GetCallbackProcedure(NX_NOTIFY_ON_END_TOUCH_FORCE_THRESHOLD);
					if(procedure != ""){
						Script.CallFunction(Game.GetActualLevel(), procedure, ent0->GetName(), ent1->GetName());
					}
					procedure = ent1->GetCallbackProcedure(NX_NOTIFY_ON_END_TOUCH_FORCE_THRESHOLD);
					if(procedure != ""){
						Script.CallFunction(Game.GetActualLevel(), procedure, ent1->GetName(), ent0->GetName());
					}
				}
				if(events & NX_NOTIFY_ON_TOUCH_FORCE_THRESHOLD){
					string procedure = ent0->GetCallbackProcedure(NX_NOTIFY_ON_TOUCH_FORCE_THRESHOLD);
					if(procedure != ""){
						Script.CallFunction(Game.GetActualLevel(), procedure, ent0->GetName(), ent1->GetName());
					}
					procedure = ent1->GetCallbackProcedure(NX_NOTIFY_ON_TOUCH_FORCE_THRESHOLD);
					if(procedure != ""){
						Script.CallFunction(Game.GetActualLevel(), procedure, ent1->GetName(), ent0->GetName());
					}
				}
			}
		}
	}
}