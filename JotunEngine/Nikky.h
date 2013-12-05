#pragma once
#include "rendermesh.h"
#include "Time.h"
#include "Transform.h"
class Nikky :
	public RenderMesh
{
public:
	Nikky();
	~Nikky();
	void update();
	void loseHealth( float damage );
	void giveForce( Vector3 newForce );
	float getHealth();
	Transform& getTransform();
private:
	float health;
	Vector3 force;
};