#pragma once
#include "Vector3.h"
class Bounds
{
public:
	Bounds();
	Bounds( Vector3 org, Vector3 ext );
	~Bounds(void);
	void giveOrigin( Vector3 org );
	void giveExtends( Vector3 ext );
	Vector3 getOrigin();
	Vector3 getExtends();
private:
	//the bounding box extends from bounds-extends to bounds+extends
	Vector3 origin, extends;
};