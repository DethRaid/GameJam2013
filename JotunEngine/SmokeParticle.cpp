#include "stdafx.h"
#include "SmokeParticle.h"


SmokeParticle::SmokeParticle( Vector3 startPos ) {
	position = startPos;
	verts[0] = Vector3( -5, -5, 0 );
	verts[1] = Vector3( -5, 5, 0 );
	verts[2] = Vector3( 5, 5, 0 );
	verts[3] = Vector3( 5, -5, 0 );
	TextureList::addTexture( "Smoke.png" );
	tex = TextureList::getTextureByName( "Smoke.png" );
	yRot = rand() % 180;
	timer = 0;
}

SmokeParticle::~SmokeParticle(void) {}

void SmokeParticle::draw() {
	tex->bind();
	glPushMatrix();
	glScalef( timer + 1, timer + 1, timer + 1 );
	glRotatef( yRot, 0, 90, 0 );
	glTranslatef( position.getX(), position.getY(), position.getZ() );
	for( int i = 0; i < 4; i++ ) {
		glVertex3f( verts[i].getX(), verts[i].getY(), verts[i].getZ() );
	}
	glPopMatrix();
}

void SmokeParticle::update() {
	timer += Time::deltaTime;
}