#pragma once
#ifndef _GAMESCREENMANAGER_H
#define _GAMESCREENMANAGER_H

#include <SDL.h>

#include "Commons.h"

class GameScreen;

class GameScreenManager
{
public:
	GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen);
	~GameScreenManager();

	void Render();
	void Update(float deltaTime, SDL_Event e);
	void ChangeScreen(SCREENS new_screen);
	SCREENS GetScreen() { return m_current_screen_name; }
private:
	SDL_Renderer* m_renderer;
	GameScreen* m_current_screen;

	SCREENS m_current_screen_name;

	void Free();
};

#endif