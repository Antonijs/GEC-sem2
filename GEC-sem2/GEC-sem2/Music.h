#pragma once
#ifndef _MUSIC_H
#define _MUSIC_H

#include <SDL.h>
#include <string>

#include "Commons.h"
#include <SDL_mixer.h>

class Music
{
public:
	Music() { m_music = nullptr; }
	~Music() { Free(); }

	void Play();
	void Pause();
	bool Load(std::string path);
	void Free();
private:
	Mix_Music* m_music;
};

#endif