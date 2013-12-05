#include "stdafx.h"
#include "ParticleSystem.h"


ParticleSystem::ParticleSystem(void) : RenderMesh( "Plane.obj", "Diffuse" ) {
	timeSinceLastParticle = 0;
	maxParticles = 25;
	scaleFac = 0.1f;
	particleStartSize = 5;
	vertexes = new float[maxParticles * 4 * 3];
	randomVelocities = new float[maxParticles * 3];
	//the average position of each particle, for scaling
	averagePos = new float[maxParticles * 3];
	TextureList::addTexture( "Smoke.png" );
	tex = TextureList::getTextureByName( "Smoke.png" );
	for( int i = 0; i < maxParticles * 3; i++ ) {
		randomVelocities[i] = float(rand())/float( RAND_MAX );
	}
}


ParticleSystem::~ParticleSystem(void) {}

void ParticleSystem::update() {
	//move particles up (position.z += Time::deltaTime)
	//if it's been enough time (.25 seconds), spawn another particle
	//do this by moving the last particle to a new position
	//all particles happen in world space
	//vertexPos = particleSystem's position + offset
	//rotate particles?
	//max of 25 particles?
	//apply random movement
	for( int i = 0; i < maxParticles*4; i++ ) {
		vertexes[(i*3)+1] += 0.25 * Time::deltaTime;
	}
	timeSinceLastParticle += Time::deltaTime;
	if( timeSinceLastParticle > 0.3f ) {
		timeSinceLastParticle = 0;
		int start = (maxParticles - 1) * 4;
		Vector3 vert( transform.getPosition() - 
			Vector3( -particleStartSize, -particleStartSize, 0 ) );
		for( int i = 0; i < 3; i++ ) {
			vertexes[start*3 + 1] = vert[i];
		}
		start += 3;

		vert = Vector3( transform.getPosition() - 
			Vector3( -particleStartSize, particleStartSize, 0 ) );
		for( int i = 0; i < 3; i++ ) {
			vertexes[start*3 + 1] = vert[i];
		}
		start += 3;
		
		vert = Vector3( transform.getPosition() - 
			Vector3( particleStartSize, particleStartSize, 0 ) );
		for( int i = 0; i < 3; i++ ) {
			vertexes[start*3 + 1] = vert[i];
		}
		start += 3;
		
		vert = Vector3( transform.getPosition() - 
			Vector3( particleStartSize, -particleStartSize, 0 ) );
		for( int i = 0; i < 3; i++ ) {
			vertexes[start*3 + 1] = vert[i];
		}
	}
	for( int i = 0; i < maxParticles * 4 * 3; i++ ) {
		vertexes[i] += randomVelocities[maxParticles/4];
		vertexes[i] *= min( scaleFac * Time::deltaTime, 1 );
	}
}

void ParticleSystem::draw() {
	glDisable( GL_CULL_FACE );
	tex->bind();
	glBegin( GL_QUADS );
	for( int i = 0; i < maxParticles * 4 * 3; i+= 3 ) {
		glVertex3fv( &vertexes[i] );
	}
	glEnd();
	glEnable( GL_CULL_FACE );
}