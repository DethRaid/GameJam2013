#include "stdafx.h"
#include "MissileMarker.h"

MissileMarker::MissileMarker( int controller ) :
	RenderMesh( "Cone.obj", "Rim" ) {
	player = controller;
}

MissileMarker::~MissileMarker(void) {}

void MissileMarker::update() {
	//player 0 uses the arrow keys. Player 1 uses the WASD keys
	if( player == 0 ) {
		if( Input::up ) {
			transform.moveBy( Vector3( -5, 0, -5 ) * Time::deltaTime );
		} else if( Input::down ) {
			transform.moveBy( Vector3( 5, 0, 5 ) * Time::deltaTime );
		}
		if( Input::right ) {
			transform.moveBy( Vector3( 5, 0, -5 ) * Time::deltaTime );
		} else if( Input::left ) {
			transform.moveBy( Vector3( -5, 0, 5 ) * Time::deltaTime );
		}
	} else if( player == 1 ) {
		if( Input::w ) {
			transform.moveBy( Vector3( -5, 0, -5 ) * Time::deltaTime );
		} else if( Input::s ) {
			transform.moveBy( Vector3( 5, 0, 5 ) * Time::deltaTime );
		}
		if( Input::d ) {
			transform.moveBy( Vector3( 5, 0, -5 ) * Time::deltaTime );
		} else if( Input::a ) {
			transform.moveBy( Vector3( -5, 0, 5 ) * Time::deltaTime );
		}
	}
}

void MissileMarker::draw( Vector3 cameraPos ) {
	if( tex != NULL ) {
		tex->bind();
	}
	Vector3 color( player == 0 ? 0 : 1, 0, player == 1 ? 0 : 1 );
	Shaders::getShaderByGLID( glShader )->setVariable( "diffuseUpload", color );
	Shaders::getShaderByGLID( glShader )->setVariable( "cameraPos", cameraPos );
	glPushMatrix();
	glTranslatef( transform.getPosition().getX(), 
		transform.getPosition().getY(), 
		transform.getPosition().getZ() );
	glRotatef( transform.getRotation().getY(), 0, 1, 0 );
	mesh->render();
	glPopMatrix();	
}