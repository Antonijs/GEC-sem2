#pragma once
#ifndef _GAMESCREENINTRO_H
#define _GAMESCREENINTRO_H

#include "GameScreen.h"
#include "Commons.h"

class Texture2D;

class GameScreenIntro : GameScreen
{
public:
	GameScreenIntro(SDL_Renderer* renderer);
	~GameScreenIntro();

	void Renderer() override;
	void Update(float deltaTime, SDL_Event e) override;
private:
	Texture2D* m_background_texture;

	bool SetUpLevel();
};

#endif