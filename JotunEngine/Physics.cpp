#include "stdafx.h"
#include "Physics.h"

bool Physics::raycast( Ray *ray, RenderMesh *geom, Vector3 *hitPos ) {
	if( !raycast( ray, &geom->getBounds() ) ) {
		return false;
	}
	return false;
}

bool Physics::raycast( Ray *ray, Bounds *geom ) {
	return false;
}