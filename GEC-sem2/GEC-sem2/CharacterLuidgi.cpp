#include "CharacterLuidgi.h"
#include "Constants.h"

CharacterLuidgi::CharacterLuidgi(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position):Character(renderer, imagePath, start_position) {

}
CharacterLuidgi::~CharacterLuidgi(){

}
void CharacterLuidgi::Update(float deltaTime, SDL_Event e) {
	switch (e.type) {
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym) {
		case SDLK_LEFT:
			m_moving_left = true;
			break;
		case SDLK_RIGHT:
			m_moving_right = true;
			break;
		case SDLK_UP:
			Jump(deltaTime);
			break;
		}
		break;
	case SDL_KEYUP:
		switch (e.key.keysym.sym) {
		case SDLK_LEFT:
			m_moving_left = false;
			break;
		case SDLK_RIGHT:			
			m_moving_right = false;
			break;
		}
	}
	Character::Update(deltaTime, e);
}