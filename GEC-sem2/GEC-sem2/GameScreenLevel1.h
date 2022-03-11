#pragma once
#ifndef _GAMESCREENLEVEL1_H
#define _GAMESCREENLEVEL1_H

#include "GameScreen.h"
#include "Commons.h"

class Texture2D;
class Character;
class LevelMap;
class PowBlock;

class GameScreenLevel1 : GameScreen
{
public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	void Renderer() override;
	void Update(float deltaTime, SDL_Event e) override;

	void UpdatePowBlock();
private:
	Texture2D* m_background_texture;
	Character* m_character_mario;
	Character* m_character_luigi;
	LevelMap* m_level_map;
	PowBlock* m_pow_block;

	bool SetUpLevel();
	void SetLevelMap();

	void DoScreenShake();

	bool m_screen_shake;
	float m_shake_time;
	float m_wobble;
	float m_background_yPos;
};

#endif