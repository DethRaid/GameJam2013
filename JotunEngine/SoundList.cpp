#include "stdafx.h"
#include "SoundList.h"

std::vector<Sound*> SoundList::sounds;
HINSTANCE SoundList::hInst;

void SoundList::init( HINSTANCE instance ) {
	hInst = instance;
}

Sound* SoundList::loadSound( LPCWSTR sName ) {
	HRSRC hResInfo = FindResource( hInst, sName, L"WAVE" );
	HANDLE hRes = LoadResource( hInst, hResInfo );
	return new Sound( LockResource( hRes ), sName );
}

Sound* SoundList::getSound( LPCWSTR toFind ) {
	for( Sound* s : sounds ) {
		if( s->getName() == toFind ) {
			return s;
		}
	}
	Sound *s = loadSound( toFind );
	sounds.push_back( s );
	return s;
}

void SoundList::playSound( LPCWSTR toPlay ) {
	sndPlaySound( getSound( toPlay )->getName(), SND_MEMORY | SND_ASYNC | SND_NOSTOP );	
}