#pragma once
#ifndef _CHARACTERLUIGI_M
#define _CHARACTERLUIGI_M

#include "Character.h"

class CharacterLuigi :Character
{
public:
	CharacterLuigi(SDL_Renderer* renderer, Sound* sound, std::string imagePath, Vector2D start_position, LevelMap* map);
	~CharacterLuigi();

	void Update(float deltaTime, SDL_Event e);
};

#endif