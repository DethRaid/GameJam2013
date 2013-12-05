#pragma once
#include "rendermesh.h"
class TemporalWarpField :
	public RenderMesh
{
public:
	TemporalWarpField( Vector3 pos );
	~TemporalWarpField(void);
	void draw();
	float getRange() {return radius;};
private:
	float radius;
};

