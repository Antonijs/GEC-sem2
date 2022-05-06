#pragma once
#ifndef _GAMESCREENLEVEL1_H
#define _GAMESCREENLEVEL1_H

#include "GameScreen.h"
#include "Commons.h"
#include <vector>

class Texture2D;
class Music;
class Character;
class LevelMap;
class PowBlock;
class CharacterKoopa;
class CharacterCoin;

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
	Music* m_music;
	Character* m_character_mario;
	Character* m_character_luigi;
	LevelMap* m_level_map;
	PowBlock* m_pow_block;
	std::vector<CharacterKoopa*> m_enemies;
	std::vector<CharacterCoin*>m_coins;

	SDL_Rect m_camera;

	bool SetUpLevel();
	void SetLevelMap();

	void DoScreenShake();

	void UpdateEnemies(float deltaTime, SDL_Event e);
	void UpdateCoins(float deltaTime, SDL_Event e);

	void CreateKoopa(Vector2D position, FACING direction, float speed);
	void CreateCoin(Vector2D position);

	bool m_screen_shake;
	float m_shake_time;
	float m_wobble;
	float m_background_yPos;

	float m_spawn_time;

	float m_score;
};

#endif