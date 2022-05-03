#include "GameScreen.h"

GameScreen::GameScreen(SDL_Renderer* renderer) { 
	m_renderer = renderer;
	m_loose = false;
	m_score = 0;
}
GameScreen::~GameScreen() { m_renderer = nullptr; }

void GameScreen::Renderer() {}
void GameScreen::Update(float deltaTime, SDL_Event e) {}