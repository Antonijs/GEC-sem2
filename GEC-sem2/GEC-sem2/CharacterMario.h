#pragma once
#ifndef _CHARACTERMARIO_H
#define _CHARACTERMARIO_H

#include "Character.h"

class CharacterMario :Character
{
public:
	CharacterMario(SDL_Renderer* renderer, Sound* sound, std::string imagePath, Vector2D start_position, LevelMap* map);
	~CharacterMario();

	void Update(float deltaTime, SDL_Event e);
};

#endif