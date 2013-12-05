#pragma once
#include "rendermesh.h"
#include "Time.h"
class Explosion :
	public RenderMesh
{
public:
	Explosion( Vector3 pos );
	~Explosion(void);
	void update();
	void draw();
	float getTimer();
private:
	float timer;
};

