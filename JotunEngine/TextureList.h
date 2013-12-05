#pragma once
#include "Texture.h"
class TextureList
{
public:
	static void addTexture( std::string texName );
	static Texture* getTextureByName( std::string texName );
private:
	static std::vector<Texture*> textures;
};

