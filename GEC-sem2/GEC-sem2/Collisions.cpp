#include "Collisions.h"
#include "Character.h"

// Initialise instance to 'nullptr'
Collisions* Collisions::m_instance = nullptr;

Collisions::Collisions() {}
Collisions::~Collisions() {
	m_instance = nullptr;
}

