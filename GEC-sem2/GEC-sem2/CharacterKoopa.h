#pragma once
#ifndef _CHARACTERKOOPA_H
#define _CHARACTERKOOPA_H

#include "Character.h"

class CharacterKoopa : public Character
{
public:
	CharacterKoopa(SDL_Renderer* renderer, Sound* sound, std::string imagePath, LevelMap* map, Vector2D start_position, FACING start_facing, float movement_speed);
	~CharacterKoopa();

	void Render(SDL_Rect camera)override;
	void Update(float deltaTime, SDL_Event e)override;

	void TakeDamage();
	void Jump();

	void SetCanTurn(bool can_turn) { m_can_turn = can_turn; }
	bool GetCanTurn() { return m_can_turn; }
	bool GetInjured() { return m_injured; }
	void TurnAround();
private:
	void FlipRightwayUp();

	float m_single_sprite_w;
	float m_single_sprite_h;

	bool m_can_turn;
	bool m_turning;
	float m_turning_time;

	bool m_injured;
	float m_injured_time;

	float m_movement_speed;
};

#endif