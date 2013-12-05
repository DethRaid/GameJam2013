#pragma once

#include "Sound.h"

class SoundList
{
public:
	static void init( HINSTANCE instance );
	static Sound* loadSound( LPCWSTR sName );
	static Sound* getSound( LPCWSTR toFind );
	static void playSound( LPCWSTR toPlay );
private:
	static HINSTANCE hInst;
	static std::vector<Sound*> sounds;
};

