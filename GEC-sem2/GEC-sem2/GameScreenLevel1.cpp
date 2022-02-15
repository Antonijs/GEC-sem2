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
}
void GameScreenLevel1::Update(float deltaTime, SDL_Event e) {

}

bool GameScreenLevel1::SetUpLevel() {
	// Load Texture
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/test.bmp")) {
		cout << "Failed to Load Background Texture" << endl;
		return false;
	}
	return true;
}