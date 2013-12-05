#pragma once
#include "Texture.h"
#include "TextureList.h"
#include "Time.h"
#include "Vector3.h"
class SmokeParticle
{
public:
	SmokeParticle( Vector3 startPos );
	~SmokeParticle(void);
	void draw();
	void update();
private:
	float timer;
	float yRot;
	Texture *tex;
	Vector3 verts[4];
	Vector3 position;
};

