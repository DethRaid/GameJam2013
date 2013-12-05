#include "stdafx.h"
#include "RenderMesh.h"

RenderMesh::RenderMesh(void) {
	glShader = 0;
}

RenderMesh::RenderMesh( std::string sMeshName, std::string sShaderName ) {
	mesh = Meshes::getMesh( sMeshName );
	shaderName = sShaderName;
	glShader = Shaders::loadShader( sShaderName );
	calculateBounds();
}

void RenderMesh::calculateBounds() {
	int maxVerts = mesh->getVertCount();
	Vector3 vert;
	float maxX = -1000, minX = 1000, 
		maxY = -1000, minY = 100, 
		maxZ = -1000, minZ = 1000;
	for( int i = 0; i < maxVerts; i++ ) {
		vert = mesh->getVert( i, &vert );
		if( vert.getX() > maxX ) {
			maxX = vert.getX();
		} else if( vert.getX() < minX ) {
			minX = vert.getX();
		}
		if( vert.getY() > maxY ) {
			maxY = vert.getY();
		} else if( vert.getY() < minY ) {
			minY = vert.getY();
		}
		if( vert.getZ() > maxZ ) {
			maxZ = vert.getZ();
		} else if( vert.getZ() < minZ ) {
			minZ = vert.getZ();
		}
	}
	Vector3 center, extends;
	float xDist = maxX - minX;
	float yDist = maxY - minY;
	float zDist = maxZ - minZ;
	extends.setX( xDist/2 );
	extends.setY( yDist/2 );
	extends.setZ( zDist/2 );
	center.setX( minX + center.getX() );
	center.setY( minY + center.getY() );
	center.setZ( minZ + center.getZ() );
	bounds.giveOrigin( center );
	bounds.giveExtends( extends );
}

RenderMesh::~RenderMesh(void) {
}

void RenderMesh::setShader() {
	glUseProgram( glShader );
}

void RenderMesh::setShader( GLuint s ) {
	glUseProgram( s );
}

void RenderMesh::draw() {
	if( tex != NULL ) {
		tex->bind();
	}
	glPushMatrix();
	glTranslatef( transform.getPosition().getX(), 
		transform.getPosition().getY(), 
		transform.getPosition().getZ() );
	glRotatef( transform.getRotation().getY(), 0, 1, 0 );
	mesh->render();
	glPopMatrix();
}

void RenderMesh::giveTex( Texture *t ) {
	tex = t;
}

Bounds& RenderMesh::getBounds() {
	return bounds;
}

Transform& RenderMesh::getTransform() {
	return transform;
}