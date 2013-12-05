#include "stdafx.h"
#include "NuclearMissile.h"


NuclearMissile::NuclearMissile( Vector3 pos ) : Missile( pos ) {
	range = 50;
	force = 50;
}

NuclearMissile::~NuclearMissile(void)
{}