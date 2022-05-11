#include <iostream>

#include "GameScreenHighScore.h"
#include "Texture2D.h"
#include "ScoreManager.h"

using namespace std;

GameScreenHighScore::GameScreenHighScore(SDL_Renderer* renderer) :GameScreen(renderer) {
	cout << "HighScore Screen" << endl;
	SetUpLevel();
	cout << "Press any Button to return to MainMenu" << endl;
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
	m_score_manager = new ScoreManager("Data/Top10.txt");
	m_top_scores = m_score_manager->GetScores();
	for (int i = 0; i < TOP_SIZE; i++) {
		cout << i + 1 << "\t|" << m_top_scores[i] << endl;
	}

	return true;
}