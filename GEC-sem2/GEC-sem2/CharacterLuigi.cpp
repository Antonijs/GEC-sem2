#include "CharacterLuigi.h"
#include "LevelMap.h"

CharacterLuigi::CharacterLuigi(SDL_Renderer* renderer, Sound* sound, std::string imagePath, Vector2D start_position, LevelMap* map) :
	Character(renderer, sound, imagePath, start_position, map){

}
CharacterLuigi::~CharacterLuigi(){

}

void CharacterLuigi::Update(float deltaTime, SDL_Event e) {
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