#include "stdafx.h"
#include "Explosion.h"


Explosion::Explosion( Vector3 pos ) : RenderMesh( "Billboard.obj", "Diffuse" ) {
	TextureList::addTexture( "Explosion.png" );
	tex = TextureList::getTextureByName( "Explosion.png" );
	timer = 0;
	transform.setPosition( pos );
	transform.setRotation( Vector3( 0, 90 * float(rand())/float(RAND_MAX), 0 ) );
}

Explosion::~Explosion(void) {}

void Explosion::update() {
	timer += Time::deltaTime;
}

void Explosion::draw() {
	glPushMatrix();
	RenderMesh::draw();
	transform.setRotation( Vector3( 0, 90, 0 ) );
	RenderMesh::draw();
	transform.setRotation( Vector3( 0, 0, 0 ) );
	glPopMatrix();
}

float Explosion::getTimer() {
	return timer;
}