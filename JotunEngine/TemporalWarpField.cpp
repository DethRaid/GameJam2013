#include "stdafx.h"
#include "TemporalWarpField.h"


TemporalWarpField::TemporalWarpField( Vector3 pos ) : 
	RenderMesh( "Sphere.obj", "Rim" ) {
	radius = 10;
	transform.setPosition( pos );
}

TemporalWarpField::~TemporalWarpField(void)
{}

void TemporalWarpField::draw() {
	Shaders::getShaderByName( shaderName )->setVariable( 
		"diffuseUpload", Vector3( 0.5, 1, 0.5 ) );
	RenderMesh::draw();
}