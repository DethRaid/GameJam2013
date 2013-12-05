#pragma once
#include "RenderMesh.h"
#include "Time.h"
class ParticleSystem : public RenderMesh
{
public:
	ParticleSystem(void);
	~ParticleSystem(void);
	void update();
	void draw();
private:
	float timeSinceLastParticle;
	float scaleFac;
	float particleStartSize;
	float *vertexes;
	float *randomVelocities;
	float *averagePos;
	int maxParticles;
};

