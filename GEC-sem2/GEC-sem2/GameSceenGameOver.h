#pragma once
#ifndef _GAMESCREENGAMEOVER_H
#define _GAMESCREENGAMEOVER_H

#include "GameScreen.h"
#include "Commons.h"

class Texture2D;

class GameScreenGameOver : GameScreen
{
public:
	GameScreenGameOver(SDL_Renderer* renderer);
	~GameScreenGameOver();

	void Renderer() override;
	void Update(float deltaTime, SDL_Event e) override;
private:
	Texture2D* m_background_texture;

	bool SetUpLevel();
};

#endif