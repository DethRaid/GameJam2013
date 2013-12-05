#pragma once

#include "Color.h"

class Texture
{
public:
	Texture(void);
	Texture( std::string texName );
	~Texture(void);
	void giveData( GLubyte *newData, int newComp );
	Color getPixelBilinear( float u, float v );
	std::string getName();
	void setComp( int newComp );
	void bind();
private:
	void makeGLTexture();
	std::string name;
	int width, height, comp;
	GLuint glid;
	GLubyte *data;
};

