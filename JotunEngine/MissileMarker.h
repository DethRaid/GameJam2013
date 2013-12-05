#pragma once
#include "rendermesh.h"
#include "Time.h"
class MissileMarker :
	public RenderMesh
{
public:
	MissileMarker( int controller );
	~MissileMarker(void);
	void update();
	void draw( Vector3 cameraPos );
private:
	int player;
};

