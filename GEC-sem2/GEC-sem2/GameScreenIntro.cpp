#include <iostream>

#include "GameScreenIntro.h"
#include "Texture2D.h"

using namespace std;

GameScreenIntro::GameScreenIntro(SDL_Renderer* renderer) :GameScreen(renderer) {
	SetUpLevel();
}
GameScreenIntro::~GameScreenIntro() {
	delete m_background_texture;
	m_background_texture = nullptr;
}

void GameScreenIntro::Renderer() {
	// Draw Backgound
	m_background_texture->Render(Vector2D(), SDL_FLIP_NONE);
}
void GameScreenIntro::Update(float deltaTime, SDL_Event e) {

}

bool GameScreenIntro::SetUpLevel() {
	// Load Texture
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/test.bmp")) {
		cout << "Failed to Load Background Texture" << endl;
		return false;
	}
	return true;
}