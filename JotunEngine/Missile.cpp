#include "stdafx.h"
#include "Missile.h"

Missile::Missile( Vector3 abovePos ) :
	RenderMesh( "Rokkit.obj", "Diffuse" ) {
	Util::debugOut<<"Initialized Missle's RenderMesh\n";
	TextureList::addTexture( "Rokkit.png" );
	Util::debugOut<<"Initialized Missile's texture\n";
	tex = TextureList::getTextureByName( "Rokkit.png" );
	transform.setPosition( abovePos + Vector3( 0, 30, 0 ) );
	Util::debugOut<<"Initialized position\n";
	timer = 0;
	range = 5;
	damage = 200;
	force = 2;
	type = 0;
	Util::debugOut<<"Why am I still checking here\n";
}

Missile::~Missile(void) {
	int j;
	j = 5;
}

void Missile::update() {
	transform.moveBy( Vector3( 0, -10.0f, 0 ) * Time::deltaTime );
}

void Missile::draw() {
	RenderMesh::draw();
}

float Missile::getRange() {
	return range;
}

float Missile::getDamage() {
	return damage;
}

float Missile::getForce() {
	return force;
}