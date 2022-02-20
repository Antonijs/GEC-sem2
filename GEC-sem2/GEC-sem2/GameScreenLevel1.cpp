#include <iostream>

#include "GameScreenLevel1.h"
#include "Texture2D.h"

using namespace std;

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) :GameScreen(renderer) {
	SetUpLevel();
}
GameScreenLevel1::~GameScreenLevel1() {
	delete m_background_texture;
	m_background_texture = nullptr;
}

void GameScreenLevel1::Renderer() {
	// Draw Backgound
	m_background_texture->Render(Vector2D(), SDL_FLIP_NONE);
	my_character1->Render();
	my_character2->Render();
}
void GameScreenLevel1::Update(float deltaTime, SDL_Event e) {
	my_character1->Update(deltaTime, e);
	my_character2->Update(deltaTime, e);

}

bool GameScreenLevel1::SetUpLevel() {
	// Load Texture
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/BackgroundMB.png")) {
		cout << "Failed to Load Background Texture" << endl;
		return false;
	}
	CharacterMario* tempCharM;
	CharacterLuidgi* tempCharL;

	tempCharM = new CharacterMario(m_renderer, "Images/Mario.png", Vector2D(64, 330));
	my_character1 = (Character*)tempCharM;
	tempCharM = nullptr;

	tempCharL = new CharacterLuidgi(m_renderer, "Images/Luigi.png", Vector2D(330, 330));
	my_character2 = (Character*)tempCharL;
	tempCharL = nullptr;

	return true;
}