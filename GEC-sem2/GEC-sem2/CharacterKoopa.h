#pragma once
#ifndef _CHARACTERKOOPA_H
#define _CHARACTERKOOPA_H

#include "Character.h"

class CharacterKoopa : Character
{
public:
	CharacterKoopa(SDL_Renderer* renderer, std::string imagePath, LevelMap* map, Vector2D start_position, FACING start_facing, float movement_speed);
	~CharacterKoopa();

	void Render()override;
	void Update(float deltaTime, SDL_Event e)override;

	void TakeDamage();
	void Jump();
private:
	void FlipRightwayUp();

	float m_single_sprite_w;
	float m_single_sprite_h;

	bool m_injured;
	float m_injured_time;

	float m_movement_speed;
};

#endif