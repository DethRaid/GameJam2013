#pragma once
#include "rendermesh.h"
#include "Color.h"
#include "Texture.h"
class Terrain :
	public RenderMesh
{
public:
	Terrain(void);
	~Terrain(void);
	GLubyte *genHeightMap();
	GLubyte getHeigthAt( Vector3 pos );
private:
	GLfloat width, length;
	Texture *heightMap;
};

