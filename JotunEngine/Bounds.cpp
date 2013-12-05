#include "stdafx.h"
#include "Bounds.h"

Bounds::Bounds() {}

Bounds::Bounds( Vector3 org, Vector3 ext ) {
	origin = org;
	extends = ext;
}

Bounds::~Bounds() {}

void Bounds::giveOrigin( Vector3 org ) {
	origin = org;
}

void Bounds::giveExtends( Vector3 ext ) {
	extends = ext;
}

Vector3 Bounds::getOrigin() {
	return origin;
}

Vector3 Bounds::getExtends() {
	return extends;
}