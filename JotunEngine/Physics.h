#pragma once
#include "Bounds.h"
#include "RenderMesh.h"
#include "Vector3.h"

class Ray
{
public:
	Ray( Vector3 pos, Vector3 dir );
	Vector3 getOrigin();
	Vector3 getDirection();
private:
	Vector3 prigin, direction;
};

class Physics
{
public:
	static bool raycast( Ray *ray, RenderMesh *geom, Vector3 *hitPos );	
	static bool raycast( Ray *ray, Bounds *geom );
};