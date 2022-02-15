#include "GameScreenManager.h"

#include "GameScreen.h"
#include "GameScreenMenu.h"
#include "GameScreenLevel1.h"


GameScreenManager::GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen) {
	m_renderer = renderer;
	m_current_screen = nullptr;

	ChangeScreen(startScreen);
}
GameScreenManager::~GameScreenManager() {
	m_renderer = nullptr;
	delete m_current_screen;
	m_current_screen = nullptr;
}

void GameScreenManager::Render() {
	m_current_screen->Renderer();
}
void GameScreenManager::Update(float deltaTime, SDL_Event e) {
	m_current_screen->Update(deltaTime, e);
}
void GameScreenManager::ChangeScreen(SCREENS new_screen) {
	// Clear Up Old Screen
	if (m_current_screen != nullptr) {
		delete m_current_screen;
	}

	GameScreenMenu* tempScreenM;
	GameScreenLevel1* tempScreenL1;

	switch (new_screen)
	{
	case SCREEN_MENU:
		tempScreenM = new GameScreenMenu(m_renderer);
		m_current_screen = (GameScreen*)tempScreenM;
		tempScreenM = nullptr;
		break;
	case SCREEN_LEVEL1:
		tempScreenL1 = new GameScreenLevel1(m_renderer);
		m_current_screen = (GameScreen*)tempScreenL1;
		tempScreenL1 = nullptr;
		break;
	default:;
	}
}