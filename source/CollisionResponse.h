#pragma once
#include "stdfx.h"
#include "NxUserContactReport.h"

class CCollisionResponse : public NxUserContactReport{
	void onContactNotify(NxContactPair& pair, NxU32 events);
};
