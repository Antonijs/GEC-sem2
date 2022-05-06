#include <iostream>

#include "GameScreenLevel2.h"
#include "Texture2D.h"
#include "Music.h"
#include "Collisions.h"

#include "Character.h"
#include "CharacterMario.h"
#include "CharacterLuigi.h"
#include "CharacterKoopa.h"
#include "CharacterCoin.h"

#include "LevelMap.h"
#include "PowBlock.h"
#include "Sound.h"

using namespace std;

GameScreenLevel2::GameScreenLevel2(SDL_Renderer* renderer) :GameScreen(renderer) {
	cout << "Level 2 Screen" << endl;
	m_level_map = nullptr;
	SetUpLevel();
	cout << "Press Esc to exit to MainMenu" << endl;
}
GameScreenLevel2::~GameScreenLevel2() {
	delete m_background_texture;
	m_background_texture = nullptr;

	delete m_pow_block;
	m_pow_block = nullptr;

	m_enemies.clear();
	m_coins.clear();
	cout << "Exiting Level 2 Screen" << endl;
}

void GameScreenLevel2::Renderer() {
	// Draw Enemies
	for (int i = 0; i < m_enemies.size(); i++) {
		m_enemies[i]->Render(m_camera);
	}
	// Draw Coins
	for (int i = 0; i < m_coins.size(); i++) {
		m_coins[i]->Render(m_camera);
	}

	// Draw Backgound
	m_background_texture->Render(Vector2D(0, m_background_yPos), m_camera, SDL_FLIP_NONE);

	// Drow PowBlock
	m_pow_block->Render(m_camera);

	// Draw Characters
	if (m_character_mario != nullptr) {
		m_character_mario->Render(m_camera);
	}
	if (m_character_luigi != nullptr) {
		m_character_luigi->Render(m_camera);
	}
}
void GameScreenLevel2::Update(float deltaTime, SDL_Event e) {
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
	// Spawn New Koopa
	m_spawn_time -= deltaTime;
	if (m_spawn_time <= 0) {
		m_spawn_time = KOOPA_SPAWN_RATE;
		CreateKoopa(Vector2D(150, 32), FACING_RIGHT, KOOPA_SPEED);
		CreateKoopa(Vector2D(325, 32), FACING_LEFT, KOOPA_SPEED);
	}

	UpdatePowBlock();
	UpdateCoins(deltaTime, e);
	UpdateEnemies(deltaTime, e);

	// -----------------
	//cout << "Current Score Is: " << m_score << endl;
	// -----------------

	if (m_character_mario != nullptr && m_character_luigi != nullptr) {
		m_character_mario->Update(deltaTime, e);
		m_character_luigi->Update(deltaTime, e);

		float averagePos = (m_character_mario->GetPosition().x + m_character_luigi->GetPosition().x) / 2;

		m_camera.x = averagePos - (m_camera.w / 2);
	}
	else if (m_character_mario != nullptr) {
		m_character_mario->Update(deltaTime, e);

		m_camera.x = m_character_mario->GetPosition().x - (m_camera.w / 2);
	}
	else if (m_character_luigi != nullptr) {
		m_character_luigi->Update(deltaTime, e);

		m_camera.x = m_character_luigi->GetPosition().x - (m_camera.w / 2);
	}
	else {
		m_loose = true;

		m_camera.x = 0;
	}

	if (m_camera.x < 0) {
		m_camera.x = 0;
	}
	else if (m_camera.x > LEVEL2_WIDTH - m_camera.w) {
		m_camera.x = LEVEL2_WIDTH - m_camera.w;
	}
}

void GameScreenLevel2::UpdatePowBlock() {
	if (m_character_mario != nullptr) {
		if (Collisions::Instance()->Box(m_character_mario->GetCollisionBox(), m_pow_block->GetCollisionBox())) {
			if (m_pow_block->IsAvailable()) {
				if (m_character_mario->IsJumping()) {
					DoScreenShake();
					m_pow_block->TakeHit();
					m_character_mario->CancelJumping();
				}
			}
		}
	}
	if (m_character_luigi != nullptr) {
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
}

bool GameScreenLevel2::SetUpLevel() {
	// Load Texture
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/BackgroundMB2.png")) {
		cout << "Failed to Load Background Texture" << endl;
		return false;

	}
	

	m_music = new Music();
	if (m_music->Load("Audio/MarioUnderworld.mp3")) {
		m_music->Play();
	}
	else {
		cout << "Failed to Load Music" << endl;
	}

	m_camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	m_score = 0;

	SetLevelMap();
	m_pow_block = new PowBlock(m_renderer, m_level_map);

	CreateKoopa(Vector2D(150, 32), FACING_RIGHT, KOOPA_SPEED);
	CreateKoopa(Vector2D(325, 32), FACING_LEFT, KOOPA_SPEED);
	m_spawn_time = KOOPA_SPAWN_RATE;

	CreateCoin(Vector2D(150, 32));
	CreateCoin(Vector2D(325, 32));

	m_screen_shake = false;
	m_background_yPos = 0.0f;

	CharacterMario* tempCharM;
	CharacterLuigi* tempCharL;

	tempCharM = new CharacterMario(m_renderer, m_sound, "Images/Mario.png", Vector2D(64, 330), m_level_map);
	m_character_mario = (Character*)tempCharM;
	tempCharM = nullptr;

	tempCharL = new CharacterLuigi(m_renderer, m_sound, "Images/Luigi.png", Vector2D(330, 330), m_level_map);
	m_character_luigi = (Character*)tempCharL;
	tempCharL = nullptr;

	return true;
}
void GameScreenLevel2::SetLevelMap() {
	int map[MAP2_HEIGHT][MAP2_WIDTH] = { {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
									     {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
									     {1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1},
									     {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
									     {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
									     {0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0},
									     {1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
									     {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
									     {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
									     {1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1},
									     {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
									     {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
									     {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1} };

	// Clear Any Old Maps
	if (m_level_map != nullptr) {
		delete m_level_map;
	}

	//Set The New Map
	m_level_map = new LevelMap(map);
}

void GameScreenLevel2::DoScreenShake() {
	m_screen_shake = true;
	m_shake_time = SHAKE_DURATION;
	m_wobble = 0.0f;

	for (unsigned int i = 0; i < m_enemies.size(); i++) {
		m_enemies[i]->TakeDamage();
	}
}

void GameScreenLevel2::UpdateEnemies(float deltaTime, SDL_Event e) {
	if (!m_enemies.empty()) {
		int enemyIndexToDelete = -1;
		for (unsigned int i = 0; i < m_enemies.size(); i++) {
			// Check If Enemy Is On Bottom Row Of Tiles
			if (m_enemies[i]->GetPosition().y > 300.0f) {
				// Is Enemy Off Screen To Left/Right?
				if (m_enemies[i]->GetPosition().x < (float)(-m_enemies[i]->GetCollisionBox().width * 0.5f) ||
					m_enemies[i]->GetCollisionBox().x > SCREEN_WIDTH - (float)(m_enemies[i]->GetCollisionBox().width * 0.55f)) {
					m_enemies[i]->SetAlive(false);
				}
			}
			// Now Do The Update
			m_enemies[i]->Update(deltaTime, e);

			if (m_enemies[i]->GetPosition().x < 0.0f + m_enemies[i]->GetCollisionBox().width * 0.25f ||
				m_enemies[i]->GetPosition().x > SCREEN_WIDTH - m_enemies[i]->GetCollisionBox().width * 0.75f) {
				if (m_enemies[i]->GetCanTurn()) {
					m_enemies[i]->TurnAround();
					m_enemies[i]->SetCanTurn(false);
				}
			}
			else {
				m_enemies[i]->SetCanTurn(true);
			}

			// Check To See If Enemy Collides With Player
			if ((m_enemies[i]->GetPosition().y > 300.0f || m_enemies[i]->GetPosition().y <= 64.0f) &&
				(m_enemies[i]->GetPosition().x < 64.0f || m_enemies[i]->GetPosition().x > SCREEN_WIDTH - 96.0f)) {
				// Ignore Collisions If Behind Pipe
			}
			else {
				if (m_character_mario != nullptr) {
					if (Collisions::Instance()->Circle(m_enemies[i]->GetCollisionCircle(), m_character_mario->GetCollisionCircle())) {
						if (m_enemies[i]->GetInjured()) {
							m_enemies[i]->SetAlive(false);
						}
						else {
							delete m_character_mario;
							m_character_mario = nullptr;
						}
					}
				}
				if (m_character_luigi != nullptr) {
					if (Collisions::Instance()->Circle(m_enemies[i]->GetCollisionCircle(), m_character_luigi->GetCollisionCircle())) {
						if (m_enemies[i]->GetInjured()) {
							m_enemies[i]->SetAlive(false);
						}
						else {
							delete m_character_luigi;
							m_character_luigi = nullptr;
						}
					}
				}
			}
			// If Enemy Is No Longer Alive Then Schedule It For Deletion
			if (!m_enemies[i]->GetAlive()) {
				enemyIndexToDelete = i;
			}
			// Remove Dead Enemies -1 Each Update
			if (enemyIndexToDelete != -1) {
				m_enemies.erase(m_enemies.begin() + enemyIndexToDelete);
			}
		}
	}
}
void GameScreenLevel2::UpdateCoins(float deltaTime, SDL_Event e) {
	if (!m_coins.empty()) {
		int coinIndexToDelete = -1;
		for (unsigned int i = 0; i < m_coins.size(); i++) {
			// Check If Coin Is On Bottom Row Of Tiles
			if (m_coins[i]->GetPosition().y > 300.0f) {
				// Is Coin Off Screen To Left/Right?
				if (m_coins[i]->GetPosition().x < (float)(-m_coins[i]->GetCollisionBox().width * 0.5f) ||
					m_coins[i]->GetCollisionBox().x > SCREEN_WIDTH - (float)(m_coins[i]->GetCollisionBox().width * 0.55f)) {
					m_coins[i]->SetAlive(false);
				}
			}
			// Now Do The Update
			m_coins[i]->Update(deltaTime, e);

			// Check To See If Coins Collides With Player
			if ((m_coins[i]->GetPosition().y > 300.0f || m_coins[i]->GetPosition().y <= 64.0f) &&
				(m_coins[i]->GetPosition().x < 64.0f || m_coins[i]->GetPosition().x > SCREEN_WIDTH - 96.0f)) {
				m_coins[i]->SetAlive(false);
			}
			else {
				if (m_character_mario != nullptr) {

					if (Collisions::Instance()->Circle(m_coins[i]->GetCollisionCircle(), m_character_mario->GetCollisionCircle())) {
						m_coins[i]->SetAlive(false);

						if (m_sound->Load("Audio/CoinPickup.wav")) {
							m_sound->Play();
						}
					}
				}
				if (m_character_luigi != nullptr) {
					if (Collisions::Instance()->Circle(m_coins[i]->GetCollisionCircle(), m_character_luigi->GetCollisionCircle())) {
						m_coins[i]->SetAlive(false);

						if (m_sound->Load("Audio/CoinPickup.wav")) {
							m_sound->Play();
						}
					}
				}
			}
			// If Enemy Is No Longer Alive Then Schedule It For Deletion
			if (!m_coins[i]->GetAlive()) {
				coinIndexToDelete = i;
			}
			// Remove Dead Enemies -1 Each Update
			if (coinIndexToDelete != -1) {
				m_score++;
				m_coins.erase(m_coins.begin() + coinIndexToDelete);
			}
		}
	}
}

void GameScreenLevel2::CreateKoopa(Vector2D position, FACING direction, float speed) {
	CharacterKoopa* tempEnK;

	tempEnK = new CharacterKoopa(m_renderer, m_sound, "Images/Koopa.png", m_level_map, position, direction, speed);

	m_enemies.push_back(tempEnK);

	tempEnK = nullptr;
}
void GameScreenLevel2::CreateCoin(Vector2D position) {
	CharacterCoin* tempCoin;

	tempCoin = new CharacterCoin(m_renderer, m_sound, "Images/Coin.png", m_level_map, position);

	m_coins.push_back(tempCoin);

	tempCoin = nullptr;
}