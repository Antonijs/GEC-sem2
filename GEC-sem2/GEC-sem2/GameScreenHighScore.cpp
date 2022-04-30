#include <iostream>

#include "GameScreenHighScore.h"
#include "Texture2D.h"

using namespace std;

GameScreenHighScore::GameScreenHighScore(SDL_Renderer* renderer) :GameScreen(renderer) {
	SetUpLevel();
}
GameScreenHighScore::~GameScreenHighScore() {
	delete m_background_texture;
	m_background_texture = nullptr;
}

void GameScreenHighScore::Renderer() {
	// Draw Backgound
	m_background_texture->Render(Vector2D(), SDL_FLIP_NONE);
}
void GameScreenHighScore::Update(float deltaTime, SDL_Event e) {

}

bool GameScreenHighScore::SetUpLevel() {
	// Load Texture
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/test.bmp")) {
		cout << "Failed to Load Background Texture" << endl;
		return false;
	}
	return true;
}