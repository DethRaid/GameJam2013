#include "stdafx.h"
#include "BigMissile.h"


BigMissile::BigMissile( Vector3 pos ) : Missile( pos ) {
	range = 20;
	type = 2;
}

BigMissile::~BigMissile(void) {}