#pragma once
class IUpdateable{
public:	
	virtual void Update()=0;
	virtual void Enable(){enable = true;}
	virtual void Disable(){enable = false;}
	virtual void Stop()=0;
protected:
	bool enable;
};