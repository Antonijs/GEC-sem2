#include <iostream>

#include "GameSceenGameOver.h"
#include "Texture2D.h"

using namespace std;

GameScreenGameOver::GameScreenGameOver(SDL_Renderer* renderer) :GameScreen(renderer) {
	SetUpLevel();
}
GameScreenGameOver::~GameScreenGameOver() {
	delete m_background_texture;
	m_background_texture = nullptr;
}

void GameScreenGameOver::Renderer() {
	// Draw Backgound
	m_background_texture->Render(Vector2D(), SDL_FLIP_NONE);
}
void GameScreenGameOver::Update(float deltaTime, SDL_Event e) {

}

bool GameScreenGameOver::SetUpLevel() {
	// Load Texture
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/test.bmp")) {
		cout << "Failed to Load Background Texture" << endl;
		return false;
	}
	return true;
}