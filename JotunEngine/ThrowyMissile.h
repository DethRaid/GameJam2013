#pragma once
#include "missile.h"
class ThrowyMissile :
	public Missile
{
public:
	ThrowyMissile( Vector3 pos );
	~ThrowyMissile(void);
};

