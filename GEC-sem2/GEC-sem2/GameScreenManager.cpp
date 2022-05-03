#include "GameScreenManager.h"

#include "GameScreen.h"
#include "GameScreenIntro.h"
#include "GameScreenMenu.h"
#include "GameScreenLevel1.h"
#include "GameScreenLevel2.h"
#include "GameSceenGameOver.h"
#include "GameScreenHighScore.h"


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
	if (m_current_screen->m_loose) {
		ChangeScreen(SCREEN_GAMEOVER);
	}
}
void GameScreenManager::ChangeScreen(SCREENS new_screen) {
	// Clear Up Old Screen
	if (m_current_screen != nullptr) {
		delete m_current_screen;
	}

	GameScreenIntro* tempScreenI;
	GameScreenMenu* tempScreenM;
	GameScreenLevel1* tempScreenL1;
	GameScreenLevel2* tempScreenL2;
	GameScreenGameOver* tempScreenGO;
	GameScreenHighScore* tempScreenHS;

	switch (new_screen)
	{
	case SCREEN_INTRO:
		tempScreenI = new GameScreenIntro(m_renderer);
		m_current_screen = (GameScreen*)tempScreenI;
		tempScreenI = nullptr;
		break;
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
	case SCREEN_LEVEL2:
		tempScreenL2 = new GameScreenLevel2(m_renderer);
		m_current_screen = (GameScreen*)tempScreenL2;
		tempScreenL2 = nullptr;
		break;
	case SCREEN_GAMEOVER:
		tempScreenGO = new GameScreenGameOver(m_renderer);
		m_current_screen = (GameScreen*)tempScreenGO;
		tempScreenGO = nullptr;
		break;
	case SCREEN_HIGHSCORES:
		tempScreenHS = new GameScreenHighScore(m_renderer);
		m_current_screen = (GameScreen*)tempScreenHS;
		tempScreenHS = nullptr;
		break;
	default:;
	}
	m_current_screen_name = new_screen;
}