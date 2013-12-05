#include "stdafx.h"
#include "Terrain.h"


Terrain::Terrain(void) : RenderMesh( "Terrain.obj", "Terrain" ) {
	//heightMap = new Texture();
	//heightMap->giveData( genHeightMap(), 1 );
	TextureList::addTexture( "Terrain.jpg" );
	giveTex( TextureList::getTextureByName( "Terrain.jpg" ) );
}

Terrain::~Terrain(void) {
}

GLubyte* Terrain::genHeightMap() {
	Vector3 vert;
	int numVerts = mesh->getVertCount();
	GLubyte *data = new GLubyte( numVerts*3 );
	for( int i = 0; i < numVerts; i++ ) {
		vert = mesh->getVert( i, &vert );
		data[i] = vert.getY();
	}
	return data;
}

GLubyte Terrain::getHeigthAt( Vector3 pos ) {
	return heightMap->getPixelBilinear( pos.getX()/width, pos.getZ()/length ).getR();
}