#pragma once
class Sound
{
public:
	Sound( LPVOID mem, LPCWSTR lpName );
	~Sound(void);
	LPVOID getMemory();
	LPCWSTR getName();
private:
	LPVOID memory;
	LPCWSTR name;
};

