#pragma once
#include "stdfx.h"
enum RenderableShaderType{
	RST_SIMPLE,
	RST_NORMALMAP
};
class IRenderable{
protected:
	string name;
	RenderableShaderType type;
	bool visible;
public:
	virtual void Render()=0;
	virtual void Update()=0;
	virtual D3DXVECTOR3 GetPosition()=0;
	virtual string GetName(){ return name; }
	virtual RenderableShaderType GetType(){ return type; }
	virtual void Show(){visible = true;}
	virtual void Hide(){visible = false;}
};