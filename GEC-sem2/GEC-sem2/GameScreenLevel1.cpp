#include <iostream>

#include "GameScreenLevel1.h"
#include "Texture2D.h"
#include "Collisions.h"

#include "Character.h"
#include "CharacterMario.h"
#include "CharacterLuigi.h"
#include "CharacterKoopa.h"

#include "LevelMap.h"
#include "PowBlock.h"

using namespace std;

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) :GameScreen(renderer) {
	m_level_map = nullptr;
	SetUpLevel();
}
GameScreenLevel1::~GameScreenLevel1() {
	delete m_background_texture;
	m_background_texture = nullptr;

	delete m_pow_block;
	m_pow_block = nullptr;

	m_enemies.clear();
}

void GameScreenLevel1::Renderer() {
	// Draw Backgound
	m_background_texture->Render(Vector2D(0, m_background_yPos), SDL_FLIP_NONE);
	m_pow_block->Render();

	m_character_mario->Render();
	m_character_luigi->Render();
}
void GameScreenLevel1::Update(float deltaTime, SDL_Event e) {
	// Do Screen Shake If Required
	if (m_screen_shake) {
		m_shake_time -= deltaTime;
		m_wobble++;
		m_background_yPos = sin(m_wobble);
		m_background_yPos *= 3.0f;

		// End Shake After Duration
		if (m_shake_time <= 0) {
			m_shake_time = false;
			m_background_yPos = 0.0f;
		}
	}

	UpdatePowBlock();

	m_character_mario->Update(deltaTime, e);
	m_character_luigi->Update(deltaTime, e);

	if (Collisions::Instance()->Circle(m_character_mario->GetCollisionCircle(), m_character_luigi->GetCollisionCircle())) {
		cout << "Circle Hit" << endl;
	}
	if (Collisions::Instance()->Box(m_character_mario->GetCollisionBox(), m_character_luigi->GetCollisionBox())) {
		cout << "Box Hit" << endl;
	}
}

void GameScreenLevel1::UpdatePowBlock() {
	if (Collisions::Instance()->Box(m_character_mario->GetCollisionBox(), m_pow_block->GetCollisionBox())) {
		if (m_pow_block->IsAvailable()) {
			if (m_character_mario->IsJumping()) {
				DoScreenShake();
				m_pow_block->TakeHit();
				m_character_mario->CancelJumping();
			}
		}
	}
	if (Collisions::Instance()->Box(m_character_luigi->GetCollisionBox(), m_pow_block->GetCollisionBox())) {
		if (m_pow_block->IsAvailable()) {
			if (m_character_luigi->IsJumping()) {
				DoScreenShake();
				m_pow_block->TakeHit();
				m_character_luigi->CancelJumping();
			}
		}
	}
}

bool GameScreenLevel1::SetUpLevel() {
	// Load Texture
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/BackgroundMB.png")) {
		cout << "Failed to Load Background Texture" << endl;
		return false;
	}
	SetLevelMap();
	m_pow_block = new PowBlock(m_renderer, m_level_map);

	m_screen_shake = false;
	m_background_yPos = 0.0f;

	CharacterMario* tempCharM;
	CharacterLuigi* tempCharL;

	tempCharM = new CharacterMario(m_renderer, "Images/Mario.png", Vector2D(64, 330), m_level_map);
	m_character_mario = (Character*)tempCharM;
	tempCharM = nullptr;

	tempCharL = new CharacterLuigi(m_renderer, "Images/Luigi.png", Vector2D(330, 330), m_level_map);
	m_character_luigi = (Character*)tempCharL;
	tempCharL = nullptr;

	return true;
}
void GameScreenLevel1::SetLevelMap() {
	int map[MAP_HEIGHT][MAP_WIDTH] = { {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
									   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
									   {1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1},
									   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
									   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
									   {0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0},
									   {1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
									   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
									   {0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0},
									   {1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1},
									   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
									   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
									   {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1} };
	
	// Clear Any Old Maps
	if (m_level_map != nullptr) {
		delete m_level_map;
	}

	//Set The New Map
	m_level_map = new LevelMap(map);
}

void GameScreenLevel1::DoScreenShake() {
	m_screen_shake = true;
	m_shake_time = SHAKE_DURATION;
	m_wobble = 0.0f;
}