#pragma once
#include "RenderMesh.h"
class ConsoleLight : public RenderMesh
{
public:
	ConsoleLight() {};
	ConsoleLight( int button );
	~ConsoleLight(void);
	void activate();
	void select();
	void deselect();
private:
	Texture *lit, *unlit, *selected;
};

