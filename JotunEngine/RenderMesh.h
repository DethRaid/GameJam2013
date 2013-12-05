#pragma once

#include "renderobject.h"
#include "Bounds.h"
#include "Input.h"
#include "Mesh.h"
#include "Meshes.h"
#include "Shaders.h"
#include "Texture.h"
#include "TextureList.h"
#include "Transform.h"

class RenderMesh :
	protected RenderObject
{
public:
	RenderMesh(void);
	RenderMesh( std::string sMeshName, std::string sShaderName );	//tell the constructor which mesh and shader to use
	~RenderMesh(void);
	void giveTex( Texture *t );
	void draw();
	void setShader();
	void setShader( GLuint s );
	Bounds& getBounds();
	Transform& getTransform();
protected:
	void calculateBounds();
	std::string shaderName;
	GLuint glShader;
	Bounds bounds;
	Mesh *mesh;
	Texture *tex;
	Transform transform;
};

