#include <iostream>

#include "GameScreenLevel1.h"
#include "Texture2D.h"
#include "Collisions.h"
#include "Character.h"
#include "CharacterMario.h"
#include "CharacterLuigi.h"
#include "LevelMap.h"

using namespace std;

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) :GameScreen(renderer) {
	m_level_map = nullptr;
	SetUpLevel();
}
GameScreenLevel1::~GameScreenLevel1() {
	delete m_background_texture;
	m_background_texture = nullptr;
}

void GameScreenLevel1::Renderer() {
	// Draw Backgound
	m_background_texture->Render(Vector2D(), SDL_FLIP_NONE);

	m_character_mario->Render();
	m_character_luigi->Render();
}
void GameScreenLevel1::Update(float deltaTime, SDL_Event e) {
	m_character_mario->Update(deltaTime, e);
	m_character_luigi->Update(deltaTime, e);

	if (Collisions::Instance()->Circle(m_character_mario->GetCollisionCircle(), m_character_luigi->GetCollisionCircle())) {
		cout << "Circle Hit" << endl;
	}
	if (Collisions::Instance()->Box(m_character_mario->GetCollisionBox(), m_character_luigi->GetCollisionBox())) {
		cout << "Box Hit" << endl;
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