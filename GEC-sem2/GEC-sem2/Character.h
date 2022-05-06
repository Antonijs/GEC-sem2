#pragma once
#ifndef _CHARACTER_H
#define _CHARACTER_H

#include <iostream>
#include <string>
#include <SDL.h>

#include "Commons.h"

class Texture2D;
class LevelMap;
class Sound;


class Character
{
public:
	Character(SDL_Renderer* renderer, Sound* sound, std::string imagePath, Vector2D start_position, LevelMap* map);
	~Character();

	virtual void Render(SDL_Rect camera);
	virtual void Update(float deltaTime, SDL_Event e);

	void SetPosition(Vector2D new_position);
	Vector2D GetPosition();

	Circle2D GetCollisionCircle();
	Rect2D GetCollisionBox();

	bool IsJumping() { return m_jumping; }
	void CancelJumping() { m_jumping = false; }

	void SetAlive(bool isAlive) { m_alive = isAlive; }
	bool GetAlive() { return m_alive; }
private:
	LevelMap* m_current_level_map;
protected:
	SDL_Renderer* m_renderer;
	Vector2D m_position;
	Texture2D* m_texture;
	FACING m_facing_direction;

	SDL_Rect m_source;
	SDL_Rect m_destination;

	Sound* m_sound;

	bool m_alive;

	bool m_moving_left;
	bool m_moving_right;

	bool m_jumping;
	bool m_can_jump;
	float m_jump_force;

	float m_collision_radius;

	virtual void MoveLeft(float deltaTime);
	virtual void MoveRight(float deltaTime);
	virtual void Jump(float deltaTime);
	virtual void AddGravity(float deltaTime);
};

#endif