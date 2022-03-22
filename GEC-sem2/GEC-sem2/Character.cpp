#include "Character.h"
#include "Texture2D.h"
#include "Constants.h"
#include "LevelMap.h"

using namespace std;

Character::Character(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, LevelMap* map) {
	m_renderer = renderer;
	m_position = start_position;
	m_current_level_map = map;
	m_texture = new Texture2D(m_renderer);
	if (!m_texture->LoadFromFile(imagePath)) {
		cout << "Failed to Load Background Texture" << endl;
	}
	m_facing_direction = FACING_RIGHT;
	m_moving_left = false;
	m_moving_right = false;
	m_jumping = false;
	m_can_jump = false;
	m_alive = true;
	m_collision_radius = 15.0f;
}
Character::~Character() {
	m_renderer = nullptr;
	delete m_texture;
	m_texture = nullptr;
}

void Character::Render() {
	if (m_facing_direction == FACING_RIGHT) {
		m_texture->Render(m_position, SDL_FLIP_NONE);
	}
	else {
		m_texture->Render(m_position, SDL_FLIP_HORIZONTAL);
	}
}
void Character::Update(float deltaTime, SDL_Event e) {
	// Collision Position Variables
	int centralX_position = (int)(m_position.x + (m_texture->GetWidth() * 0.5)) / TILE_WIDTH;
	int foot_position = (int)(m_position.y + m_texture->GetHeight()) / TILE_HEIGHT;

	// Deal With Gravity
	if (m_current_level_map->GetTileAt(foot_position, centralX_position) == 0) {
		AddGravity(deltaTime);
	}
	else {
		// Collided With Ground So We Can Jump Again
		m_can_jump = true;
	}

	// Gravity And Jumping
	if (m_jumping) {
		// Adjust Position
		m_position.y -= m_jump_force * deltaTime;
		// Reduce Jump Force
		m_jump_force -= JUMP_FORCE_DECREMET * deltaTime;

		if (m_jump_force <= 0.0f) {
			m_jumping = false;
		}
	}

	// Make movement smooth
	if (m_moving_left) {
		MoveLeft(deltaTime);
	}
	else if (m_moving_right) {
		MoveRight(deltaTime);
	}
}

void Character::SetPosition(Vector2D new_position) {
	m_position = new_position;
}
Vector2D Character::GetPosition() {
	return m_position;
}

void Character::MoveLeft(float deltaTime) {
	m_position.x -= MOVEMENT_SPEED * deltaTime;
	m_facing_direction = FACING_LEFT;
}
void Character::MoveRight(float deltaTime) {
	m_position.x += MOVEMENT_SPEED * deltaTime;
	m_facing_direction = FACING_RIGHT;
}
void Character::Jump(float deltaTime) {
	if (!m_jumping) {
		m_jump_force = INITIAL_JUMP_FORCE;
		m_jumping = true;
		m_can_jump = false;
	}
}
void Character::AddGravity(float deltaTime) {
	if (m_position.y + m_texture->GetHeight() < SCREEN_HEIGHT) {
		m_position.y += GRAVITY * deltaTime;
	}
	else {
		m_can_jump = true;
	}
}

Circle2D Character::GetCollisionCircle() {
	return Circle2D(m_position.x, m_position.y, m_collision_radius);
}
Rect2D Character::GetCollisionBox() {
	return Rect2D(m_position.x, m_position.y, m_texture->GetWidth(), m_texture->GetHeight());
}