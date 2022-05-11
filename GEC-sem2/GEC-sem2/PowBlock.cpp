#include "PowBlock.h"
#include "Texture2D.h"
#include "LevelMap.h"

#include <iostream>
#include "string"

// Level 1
PowBlock::PowBlock(SDL_Renderer* renderer, LevelMap* map) {
	std::string imahePath = "Images/PowBlock.png";
	m_texture = new Texture2D(renderer);
	if (!m_texture->LoadFromFile(imahePath.c_str())) {
		std::cout << "Failed to load texture." << std::endl;
	}

	m_level_map = map;
	m_single_sprite_w = m_texture->GetWidth() / 3;
	m_single_sprite_h = m_texture->GetHeight();
	m_num_hits_left = 3;

	m_position = Vector2D((SCREEN_WIDTH * 0.5f) - m_single_sprite_w * 0.5f, 260);
	m_leftX_position = 7;
	m_rightX_position = 8;
	m_centralY_position = 8;

	m_level_map->ChangeTileAt(m_centralY_position, m_leftX_position, 1);
	m_level_map->ChangeTileAt(m_centralY_position, m_centralY_position, 1);
}
// Level 2
PowBlock::PowBlock(SDL_Renderer* renderer, Vector2D position, LevelMap* map) {
	std::string imahePath = "Images/PowBlock.png";
	m_texture = new Texture2D(renderer);
	if (!m_texture->LoadFromFile(imahePath.c_str())) {
		std::cout << "Failed to load texture." << std::endl;
	}

	m_level_map = map;
	m_single_sprite_w = m_texture->GetWidth() / 3;
	m_single_sprite_h = m_texture->GetHeight();
	m_num_hits_left = 3;

	m_leftX_position = (int)(position.x) / TILE_WIDTH;
	m_rightX_position = (int)(position.x + m_single_sprite_w) / TILE_WIDTH;
	m_centralY_position = (int)(position.y + (m_single_sprite_h / 2)) / TILE_HEIGHT;
	m_position = Vector2D(((m_leftX_position * TILE_WIDTH) + (TILE_WIDTH / 2)), ((m_centralY_position * TILE_HEIGHT) + 1));

	m_level_map->ChangeTileAt(m_centralY_position, m_leftX_position, 1);
	m_level_map->ChangeTileAt(m_centralY_position, m_rightX_position, 1);
}
PowBlock::~PowBlock() {
	m_renderer = nullptr;
	delete m_texture;
	m_texture = nullptr;
	m_level_map = nullptr;
}

void PowBlock::Render(SDL_Rect camera) {
	if (m_num_hits_left > 0) {
		int left = m_single_sprite_w * (m_num_hits_left - 1);
		SDL_Rect portion_of_sprite = { left, 0, m_single_sprite_w, m_single_sprite_h };
		SDL_Rect dest_rect = { (int)m_position.x - camera.x, (int)m_position.y - camera.y, m_single_sprite_w, m_single_sprite_h };
		m_texture->Render(portion_of_sprite, dest_rect, SDL_FLIP_NONE);
	}
}
void PowBlock::TakeHit() {
	m_num_hits_left--;
	if (m_num_hits_left <= 0) {
		m_num_hits_left = 0;
		m_level_map->ChangeTileAt(m_centralY_position, m_leftX_position, 0);
		m_level_map->ChangeTileAt(m_centralY_position, m_rightX_position, 0);
	}
}