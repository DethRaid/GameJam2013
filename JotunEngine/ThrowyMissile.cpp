#include "stdafx.h"
#include "ThrowyMissile.h"

ThrowyMissile::ThrowyMissile( Vector3 pos ) : Missile( pos ) {
	force = 5;
	type = 1;
}

ThrowyMissile::~ThrowyMissile(void) {}