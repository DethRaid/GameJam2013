#include "stdafx.h"
#include "Texture.h"


Texture::Texture(void) {
}

Texture::Texture( std::string texName ) {
	name = texName;
	data = stbi_load( name.c_str(), &width, &height, &comp, 0 );
	makeGLTexture();
}

Texture::~Texture(void) {
	delete[] data;
}

void Texture::giveData( GLubyte *newData, int newComp ) {
	delete[] data;
	data = newData;
	comp = newComp;
	int size = sizeof( data )/comp;
	width = height = sqrt( size );
}

void Texture::makeGLTexture() {
	glGenTextures( 1, &glid );

	glBindTexture( GL_TEXTURE_2D, glid );
	if( glIsTexture( glid ) ) {
		glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR  );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR  );
		glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE );

		GLfloat fLargest;
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &fLargest);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, fLargest);
		if( comp == 3 ) {
			gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGB, width, height, GL_RGB, GL_UNSIGNED_BYTE, data );
		} else if( comp == 4 ) {
			gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGBA, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data );
		}
	}
}
//May or may not work. Why is there a 32?
Color Texture::getPixelBilinear( float u, float v ) {
	u = u * width - 0.5;
	v = v * height - 0.5;
	int x = floor( u );
	int y = floor( v );
	float uRatio = u - x;
	float vRatio = v - y;
	float uOpposite = 1 - uRatio;
	float vOpposite = 1 - vRatio;
	Color c( 1, 1, 1, 1 );
	c.setR( (data[x + y*32] * uOpposite + data[x+4 + y*32] * uRatio) * vOpposite +
		(data[x + (y+4)*32] * uOpposite + data[x+4 + (y+4)*32] * uRatio) * vRatio);
	if( comp < 1 ) {
		c.setG(	(data[x + y*32]+1 * uOpposite + data[x+4 + y*32]+1 * uRatio) * vOpposite +
			(data[x + (y+4)*32]+1 * uOpposite + data[x+4 + (y+4)*32]+1 * uRatio) * vRatio );
	}
	if( comp < 2 ) {
		c.setB(	(data[x + y*32]+2 * uOpposite + data[x+4 + y*32]+2 * uRatio) * vOpposite +
			(data[x + (y+4)*32]+2 * uOpposite + data[x+4 + (y+4)*32]+2 * uRatio) * vRatio );
	}
	if( comp == 4 ) {
		c.setA(	(data[x + y*32]+3 * uOpposite + data[x+4 + y*32]+3 * uRatio) * vOpposite +
			(data[x + (y+4)*32]+3 * uOpposite + data[x+4 + (y+4)*32]+3 * uRatio) * vRatio );
	}
	return c;
}

std::string Texture::getName() {
	return name;
}

void Texture::setComp( int newComp ) {
	comp = newComp;
}

void Texture::bind() {
	glActiveTexture( GL_TEXTURE0 );
	glBindTexture( GL_TEXTURE_2D, glid );
}