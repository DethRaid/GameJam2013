#pragma once
#include "Color.h"
#include "Shader.h"
#include "Shaders.h"
#include "Texture.h"
#include "TextureList.h"
class Material
{
public:
	Material(void);
	Material( std::string matName, 
		std::string shaderName,
		std::string texName );
	~Material(void);

	void setActive();

	void setName( std::string newName );
	void setShader( Shader *newShader );
	void setColor( Color newColor );
	void setTexture( Texture *newTexture );
	void setSpeclarPower( float newSpecular );

	std::string getName();
	Color& getColor();
	Shader* getShader();
	Texture* getTexture();
	float getSpecularPower();
protected:
	GLuint shaderDiffuse;
	Texture *texture;
	Color diffuse;
	float specularPower;
	Shader *shader;
	std::string name;
};