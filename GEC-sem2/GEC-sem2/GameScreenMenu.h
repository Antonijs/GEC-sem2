#pragma once
#ifndef _GAMESCREENMENU_H
#define _GAMESCREENMENU_H

#include "GameScreen.h"
#include "Commons.h"

class Texture2D;

class GameScreenMenu : GameScreen
{
public:
	GameScreenMenu(SDL_Renderer* renderer);
	~GameScreenMenu();

	void Renderer() override;
	void Update(float deltaTime, SDL_Event e) override;
private:
	Texture2D* m_background_texture;

	bool SetUpLevel();
};

#endif