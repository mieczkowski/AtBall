#include "TriggerCallback.h"
#include "Logger.h"
#include "Game.h"
#include "Script.h"
#include "Entity.h"
#include "EntityMgr.h"
void CTriggerCallback::onTrigger(NxShape &triggerShape, NxShape &otherShape, NxTriggerFlag status){
	string ent0Name, ent1Name;
	ent0Name = triggerShape.getActor().getName();
	ent1Name = otherShape.getActor().getName();
	CEntityEx* ent0 = (CEntityEx*) EntityMgr.GetEntity(string(ent0Name));
	CEntityEx* ent1 = (CEntityEx*) EntityMgr.GetEntity(string(ent1Name));
	if(ent0 != NULL && ent1 != NULL){
		if(status & NX_TRIGGER_ON_ENTER){
			string procedure = ent0->GetTriggerProcedure(NX_TRIGGER_ON_ENTER);
			if(procedure != ""){
				Script.CallFunction(Game.GetActualLevel(), procedure, ent0->GetName(), ent1->GetName());
			}
			procedure = ent1->GetTriggerProcedure(NX_TRIGGER_ON_ENTER);
			if(procedure != ""){
				Script.CallFunction(Game.GetActualLevel(), procedure, ent1->GetName(), ent0->GetName());
			}
		}
		if(status & NX_TRIGGER_ON_LEAVE){
			string procedure = ent0->GetTriggerProcedure(NX_TRIGGER_ON_LEAVE);
			if(procedure != ""){
				Script.CallFunction(Game.GetActualLevel(), procedure, ent0->GetName(), ent1->GetName());
			}
			procedure = ent1->GetTriggerProcedure(NX_TRIGGER_ON_LEAVE);
			if(procedure != ""){
				Script.CallFunction(Game.GetActualLevel(), procedure, ent1->GetName(), ent0->GetName());
			}
		}       
		if(status & NX_TRIGGER_ON_STAY){
			string procedure = ent0->GetTriggerProcedure(NX_TRIGGER_ON_STAY);
			if(procedure != ""){
				Script.CallFunction(Game.GetActualLevel(), procedure, ent0->GetName(), ent1->GetName());
			}
			procedure = ent1->GetTriggerProcedure(NX_TRIGGER_ON_STAY);
			if(procedure != ""){
				Script.CallFunction(Game.GetActualLevel(), procedure, ent1->GetName(), ent0->GetName());
			}
		}
	}
}
