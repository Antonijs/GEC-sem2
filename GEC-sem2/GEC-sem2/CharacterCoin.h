#pragma once
#ifndef _CHARACTERCOIN_H
#define _CHARACTERCOIN_H

#include "Character.h"

class CharacterCoin : public Character
{
public:
	CharacterCoin(SDL_Renderer* renderer, Sound* sound, std::string imagePath, LevelMap* map, Vector2D start_position);
	~CharacterCoin();

	void Render(SDL_Rect camera)override;
	void Update(float deltaTime, SDL_Event e)override;
private:
	float m_single_sprite_w;
	float m_single_sprite_h;

	float m_frame_delay;
	int m_current_frame;
	bool m_animate_backward;
};

#endif