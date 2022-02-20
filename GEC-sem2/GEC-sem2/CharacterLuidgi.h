#pragma once
#ifndef _CHARACTERLUIDGI_M
#define _CHARACTERLUIDGI_M

#include "Character.h"

class CharacterLuidgi :Character
{
public:
	CharacterLuidgi(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position);
	~CharacterLuidgi();

	void Update(float deltaTime, SDL_Event e);
};

#endif