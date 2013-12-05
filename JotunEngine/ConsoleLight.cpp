#include "stdafx.h"
#include "ConsoleLight.h"


ConsoleLight::ConsoleLight( int button ) {
	TextureList::addTexture( "LitButton.png" );
	TextureList::addTexture( "UnlitButton.png" );
	TextureList::addTexture( "SelectedButton.png" );
	lit = TextureList::getTextureByName( "LitButton.png" );
	unlit = TextureList::getTextureByName( "UnlitButton.png" );
	selected = TextureList::getTextureByName( "SelectedButton.png" );
	tex = unlit;
	std::string mName = "Light";
	char *buf = new char[2];
	sprintf_s( buf, 2, "%d", button );
	mName +=  buf;
	mName += ".obj";
	mesh = Meshes::getMesh( mName );
	glShader = Shaders::loadShader( "Diffuse" );
	calculateBounds();
}

ConsoleLight::~ConsoleLight(void) {}

void ConsoleLight::activate() {
	tex = lit;
}

void ConsoleLight::select() {
	tex = selected;
}

void ConsoleLight::deselect() {
	tex = lit;
}