#include "GameScreen.h"
#include "Music.h"
#include "Sound.h"

GameScreen::GameScreen(SDL_Renderer* renderer) { 
	m_renderer = renderer;
	m_loose = false;
	m_score = 0;

	m_music = new Music();
	m_sound = new Sound();
}
GameScreen::~GameScreen() {
	m_renderer = nullptr;
	
	delete m_music;
	m_music = nullptr;
	delete m_sound;
	m_sound = nullptr;
}

void GameScreen::Renderer() {}
void GameScreen::Update(float deltaTime, SDL_Event e) {}