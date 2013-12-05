#include "stdafx.h"
#include "MaterialList.h"

std::vector<Material> MaterialList::materials;

void MaterialList::addMaterial( std::string matName,
							   std::string shaderName,
							   std::string texName ) {
	if( getMaterial( matName ).getName() == "NULL" ) {
		materials.push_back( Material( matName, shaderName, texName ) );
	}
}

void MaterialList::addMaterial( Material m ) {
	if( getMaterial( m.getName() ).getName() == "NULL" ) {
		materials.push_back( m );
	}
}

Material& MaterialList::getMaterial( std::string name ) {
	for( Material &m : materials ) {
		if( m.getName() == name )
			return m;
	}
	return Material( "NULL", "NULL", "NULL" );
}