#include "stdafx.h"
#include "Sound.h"


Sound::Sound( LPVOID mem, LPCWSTR lpName ) {
	memory = mem;
	name = lpName;
}

Sound::~Sound(void) {}

LPVOID Sound::getMemory() {
	return memory;
}

LPCWSTR Sound::getName() {
	return name;
}