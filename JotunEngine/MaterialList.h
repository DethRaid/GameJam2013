#pragma once
#include "Material.h"
class MaterialList
{
public:
	static void addMaterial( std::string matName, 
		std::string shaderName, 
		std::string texName );
	static void addMaterial( Material m );
	static Material& getMaterial( int ind );
	static Material& getMaterial( std::string matName );
private:
	static std::vector<Material> materials;
};

