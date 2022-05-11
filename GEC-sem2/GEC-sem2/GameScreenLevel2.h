#pragma once
#ifndef _GAMESCREENLEVEL2_H
#define _GAMESCREENLEVEL2_H

#include "GameScreen.h"
#include "Commons.h"
#include <vector>
#include <iostream>
#include <fstream>

class Texture2D;
class Character;
class LevelMap;
class PowBlock;
class CharacterKoopa;
class CharacterCoin;
class ScoreManager;

class GameScreenLevel2 : GameScreen
{
public:
	GameScreenLevel2(SDL_Renderer* renderer);
	~GameScreenLevel2();

	void Renderer() override;
	void Update(float deltaTime, SDL_Event e) override;

	void UpdatePowBlock();
private:
	Texture2D* m_background_texture;
	Character* m_character_mario;
	Character* m_character_luigi;
	LevelMap* m_level_map;
	ScoreManager* m_score_manager;
	std::vector<CharacterKoopa*> m_enemies;
	std::vector<CharacterCoin*>m_coins;
	std::vector<PowBlock*>m_pow_blocks;

	SDL_Rect m_camera;

	std::ifstream inFile;
	std::ofstream outFile;

	bool SetUpLevel();
	void SetLevelMap();

	void DoScreenShake();

	void UpdateEnemies(float deltaTime, SDL_Event e);
	void UpdateCoins(float deltaTime, SDL_Event e);

	void CreateKoopa(Vector2D position, FACING direction, float speed);
	void CreateCoin(Vector2D position);
	void CreatePowBlock(Vector2D position);

	bool m_screen_shake;
	float m_shake_time;
	float m_wobble;
	float m_background_yPos;

	float m_spawn_time;

	float m_score;
};

#endif