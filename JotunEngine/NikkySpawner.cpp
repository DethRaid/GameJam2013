#include "stdafx.h"
#include "NikkySpawner.h"

Nikky* NikkySpawner::newNikky() {
	Nikky *n = new Nikky();
	float randX = 10.0f * (float(rand())/float(RAND_MAX));
	float randY = 10.0f * (float(rand())/float(RAND_MAX));
	n->getTransform().setPosition( 17.266 + randX, 0, -50 + randY );
	return n;
}