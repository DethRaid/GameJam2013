#include "stdafx.h"
#include "TextureList.h"

std::vector<Texture*> TextureList::textures;

void TextureList::addTexture( std::string texName ) {
	for( Texture *t : textures ) {
		if( t->getName() == texName ) {
			return;
		}
	}
	Texture *t = new Texture( texName );
	textures.push_back( t );
}

Texture* TextureList::getTextureByName( std::string texName ) {
	for( Texture *t : textures ) {
		if( t->getName() == texName ) {
			return t;
		}
	}
	return NULL;
}