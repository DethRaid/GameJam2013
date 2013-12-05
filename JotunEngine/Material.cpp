#include "stdafx.h"
#include "Material.h"

Material::Material(void) {
	//No one should use a material without the proper values
	//Anyone who doesn't deserves whatever errors they get
}

Material::Material( std::string matName, 
				   std::string shaderName, 
				   std::string texName ) {
	if( matName == "NULL" ) {
		return;	//empty material. It was created as an error message. Let it live
	}
	shader = Shaders::getShaderByName( shaderName );
	texture = TextureList::getTextureByName( texName );
	diffuse = Color( 1, 1, 1, 1 );
	specularPower = 1;
	name = matName;
	shaderDiffuse = shader->getVariable( "diffuseUpload" );
}

Material::~Material(void) {}

void Material::setActive() {
	glUseProgram( shader->id() );
	glUniform4f( shaderDiffuse, 
		diffuse.getR(), diffuse.getG(), diffuse.getB(), diffuse.getA() );
}

void Material::setName( std::string newName ) {
	name = newName;
}

void Material::setShader( Shader *newShader ) {
	shader = newShader;
	shaderDiffuse = shader->getVariable( "diffuseUpload" );
}

void Material::setColor( Color newColor ) {
	diffuse = newColor;
}

void Material::setTexture( Texture *newTexture ) {
	texture = newTexture;
}

void Material::setSpeclarPower( float newSpecular ) {
	specularPower = newSpecular;
}

std::string Material::getName() {
	return name;
}

Color& Material::getColor() {
	return diffuse;
}

Shader* Material::getShader() {
	return shader;
}

Texture* Material::getTexture() {
	return texture;
}

float Material::getSpecularPower() {
	return specularPower;
}