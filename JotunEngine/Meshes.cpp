#include "stdafx.h"
#include "Meshes.h"

std::vector<Mesh*> Meshes::meshes;

Mesh* Meshes::getMesh( std::string name ) {
	for( Mesh *m : meshes ) {
		if( m->getName() == name ) {
			return m;
		}
	}
	Mesh *m = new Mesh( name );
	meshes.push_back( m );
	return m;
}