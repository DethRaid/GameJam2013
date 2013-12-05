#include "stdafx.h"
#include "Nikky.h"


Nikky::Nikky() : RenderMesh( "Nikky.obj", "Diffuse" ) {
	transform.setRotation( Vector3( 0, -45, 0 ) );
	TextureList::addTexture( "Nikky.png" );
	tex = TextureList::getTextureByName( "Nikky.png" );
	health = 100;
}

void Nikky::update() {
	if( force.magnitude() < 0.01 ) {
		transform.moveBy( Vector3( -.5581, 0, .8297 ) * Time::deltaTime );
	} else {
		transform.moveBy( force * Time::deltaTime );
		force.setY( force.getY() - 0.1 );
	}
	if( transform.getPosition().getY() < -1 ) {
		transform.getPosition().setY( 0 );
		force = Vector3::zero;
	}
}

void Nikky::loseHealth( float damage ) {
	health -= damage;
	int j;
	j = 5;
}

void Nikky::giveForce( Vector3 newForce ) {
	force = newForce;
}

float Nikky::getHealth() {
	return health;
}

Transform& Nikky::getTransform() {
	return transform;
}

Nikky::~Nikky() {
	PlaySound( L"Ow.wav", NULL, SND_ASYNC | SND_FILENAME | SND_NODEFAULT );
}