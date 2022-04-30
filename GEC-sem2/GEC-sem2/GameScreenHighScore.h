#pragma once
#ifndef _GAMESCREENHIGHSCORE_H
#define _GAMESCREENHIGHSCORE_H

#include "GameScreen.h"
#include "Commons.h"

class Texture2D;

class GameScreenHighScore : GameScreen
{
public:
	GameScreenHighScore(SDL_Renderer* renderer);
	~GameScreenHighScore();

	void Renderer() override;
	void Update(float deltaTime, SDL_Event e) override;
private:
	Texture2D* m_background_texture;

	bool SetUpLevel();
};

#endif