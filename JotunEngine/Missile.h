#pragma once
#include "RenderMesh.h"
#include "ParticleSystem.h"
#include "SmokeParticle.h"
#include "Time.h"
class Missile : public RenderMesh
{
public:
	Missile( Vector3 abovePos );
	~Missile(void);
	void update();
	void draw();
	float getRange();
	float getDamage();
	float getForce();
	int type;
protected:
	float timer;
	float range, damage, force;
	ParticleSystem *pSystem;
	std::vector<SmokeParticle*> particles;
};

