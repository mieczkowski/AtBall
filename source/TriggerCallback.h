#pragma once
#include "Physx.h"
class CTriggerCallback : public NxUserTriggerReport{ 
	void onTrigger(NxShape& triggerShape, NxShape& otherShape, NxTriggerFlag status);
};
