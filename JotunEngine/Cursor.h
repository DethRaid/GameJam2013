#pragma once
#include "RenderMesh.h"
#include "Camera.h"
class Cursor : public RenderMesh
{
public:
	Cursor(void);
	~Cursor(void);
	void update( Camera &cam );
};

