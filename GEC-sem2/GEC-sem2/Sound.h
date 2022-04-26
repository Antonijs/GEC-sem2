#pragma once
#ifndef _SOUND_H
#define _SOUND_H

#include <SDL.h>
#include <string>

#include "Commons.h"
#include <SDL_mixer.h>

class Sound
{
public:
	Sound() { m_sample = nullptr; }
	~Sound() { Free(); }

	void Play();
	bool Load(std::string path);
	void Free();
private:
	Mix_Chunk* m_sample;
};

#endif