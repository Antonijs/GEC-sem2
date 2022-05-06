#include "CharacterKoopa.h"

#include "constants.h"
#include "Texture2D.h"


CharacterKoopa::CharacterKoopa(SDL_Renderer* renderer, Sound* sound, std::string imagePath, LevelMap* map, Vector2D start_position, FACING start_facing, float movement_speed) :
	Character(renderer, sound, imagePath, start_position, map) {
	m_facing_direction = start_facing;
	m_movement_speed = movement_speed;
	m_position = start_position;
	m_injured = false;

	m_can_turn = true;

	m_single_sprite_w = m_texture->GetWidth() / 2;
	m_single_sprite_h = m_texture->GetHeight();
}
CharacterKoopa::~CharacterKoopa() {

}

void CharacterKoopa::Render(SDL_Rect camera) {
	// Variable That Hold Left Position Of The Sprite We Want To Draw
	int left = 0.0f;

	// If Injured Set Left Position As Left Position Of The Second Image Of The Sprite Sheet
	if (m_injured) {
		left = m_single_sprite_w;
	}

	// Get The Portion Of The Sprite Sheet You Want To Draw
	SDL_Rect portion_of_sprite = { left, 0, m_single_sprite_w, m_single_sprite_h };

	// Determine Where You Want It Drawn
	SDL_Rect destRect = { (int)m_position.x - camera.x, (int)m_position.y - camera.y, m_single_sprite_w, m_single_sprite_h };

	// Then Draw It Facing The Correct Direction
	if (m_facing_direction == FACING_RIGHT) {
		m_texture->Render(portion_of_sprite, destRect, SDL_FLIP_NONE);
	}
	else {
		m_texture->Render(portion_of_sprite, destRect, SDL_FLIP_HORIZONTAL);
	}
}
void CharacterKoopa::Update(float deltaTime, SDL_Event e) {
	// Use The Code Within The Base Class
	Character::Update(deltaTime, e);

	if (!m_injured && !m_turning) {
		// Enemy Is Not Injured So Move
		if (m_facing_direction == FACING_LEFT) {
			m_moving_left = true;
			m_moving_right = false;
		}
		else if (m_facing_direction == FACING_RIGHT) {
			m_moving_right = true;
			m_moving_left = false;
		}
	}
	else {
		// We Should Not Be Moving When Injured Or Turning
		m_moving_left = false;
		m_moving_right = false;

		// Count Down The Injured Time And Turning Time
		m_turning_time -= deltaTime;
		m_injured_time -= deltaTime;

		if (m_injured_time <= 0.0 && m_turning_time <= 0.0) {
			FlipRightwayUp();
		}
	}
}

void CharacterKoopa::TurnAround() {
	m_turning = true;
	m_turning_time = TURNING_TIME;
}

void CharacterKoopa::TakeDamage() {
	m_injured = true;
	m_injured_time = INJURED_TIME;
	Jump();
}
void CharacterKoopa::Jump() {
	if (!m_jumping) {
		m_jump_force = INITIAL_JUMP_FORCE_SMALL;
		m_jumping = true;
		m_can_jump = false;
	}
}

void CharacterKoopa::FlipRightwayUp() {
	if (m_facing_direction == FACING_RIGHT) {
		m_facing_direction = FACING_LEFT;
	}
	else {
		m_facing_direction = FACING_RIGHT;
	}
	m_turning = false;
	m_injured = false;
	Jump();
}