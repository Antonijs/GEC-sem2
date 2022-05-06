#pragma once
#ifndef _GAMESCREEN_H
#define _GAMESCREEN_H

#include <SDL.h>

class Music;
class Sound;

class GameScreen
{
public:
	GameScreen(SDL_Renderer* renderer);
	~GameScreen();

	virtual void Renderer();
	virtual void Update(float deltaTime, SDL_Event e);

	bool m_loose;
	int m_score;
protected:
	SDL_Renderer* m_renderer;
	Music* m_music;
	Sound* m_sound;
};

#endif