#include "stdafx.h"
#include "Cursor.h"

Cursor::Cursor(void) : RenderMesh( "Plane.obj", "Diffuse" ) {
	TextureList::addTexture( "Cursor.png" );
	tex = TextureList::getTextureByName( "Cursor.png" );
}

void Cursor::update( Camera &cam ) {
	Vector3 mousePos = Input::mousePosition;
	mousePos.setX( (2 * mousePos.getX() / cam.getScreenX()) - 1 );
	mousePos.setZ( -.002 );
	mousePos.setY( -((2 * mousePos.getY() / cam.getScreenY()) - 1)/2 );
	transform.setPosition( mousePos );
	if( Input::p ) {
		int j;
		j = 54;
	}
}

Cursor::~Cursor(void) {}