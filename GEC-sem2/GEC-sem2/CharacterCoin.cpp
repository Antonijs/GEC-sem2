#include "CharacterCoin.h"

#include "constants.h"
#include "Texture2D.h"

CharacterCoin::CharacterCoin(SDL_Renderer* renderer, std::string imagePath, LevelMap* map, Vector2D start_position) :
	Character(renderer, imagePath, start_position, map) {
	m_position = start_position;
	
	m_single_sprite_w = m_texture->GetWidth() / 3;
	m_single_sprite_h = m_texture->GetHeight();

	m_moving_left = false;
	m_moving_right = false;

	m_current_frame = 0;
	m_frame_delay = ANIMATION_DELAY;
	m_animate_backward = false;
}
CharacterCoin::~CharacterCoin() {

}

void CharacterCoin::Render() {
	// Get The Portion Of The Sprite Sheet You Want To Draw
	int left = m_current_frame * m_single_sprite_w;
	SDL_Rect portion_of_sprite = { left, 0, m_single_sprite_w, m_single_sprite_h };

	// Determine Where You Want It Drawn
	SDL_Rect destRect = { (int)(m_position.x), (int)(m_position.y), m_single_sprite_w, m_single_sprite_h };

	m_texture->Render(portion_of_sprite, destRect, SDL_FLIP_NONE);
}
void CharacterCoin::Update(float deltaTime, SDL_Event e) {
	Character::Update(deltaTime, e);
	m_frame_delay -= deltaTime;
	if (m_frame_delay <= 0.0f) {
		m_frame_delay = ANIMATION_DELAY;

		m_current_frame++;

		if (m_current_frame > 2) {
			m_current_frame = 0;
			m_animate_backward = true;
		}
	}
}