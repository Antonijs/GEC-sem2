#include <iostream>

#include "GameSceenGameOver.h"
#include "Texture2D.h"
#include "Sound.h"

using namespace std;

GameScreenGameOver::GameScreenGameOver(SDL_Renderer* renderer) :GameScreen(renderer) {
	cout << "GameOver Screen" << endl;
	SetUpLevel();
	cout << "Esc) - MainMenu\nSpace) - HighScore" << endl;
}
GameScreenGameOver::~GameScreenGameOver() {
	delete m_background_texture;
	m_background_texture = nullptr;
	cout << "exiting GameOver Screens" << endl;
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

	if (m_sound->Load("Audio/GameOver.wav")) {
		m_sound->Play();
	}

	return true;
}