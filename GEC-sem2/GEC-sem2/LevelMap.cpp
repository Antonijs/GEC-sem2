#include "LevelMap.h"

/*
* When Making a Map, Remember:
* 0 = Empty Space, 1 = Blocked/Occupied Space
*/

LevelMap::LevelMap(int map[MAP_HEIGHT][MAP_WIDTH]) {
	// Allocate Memory For The Level Map
	m_map = new int* [MAP_HEIGHT];
	for (unsigned int i = 0; i < MAP_HEIGHT; i++) {
		m_map[i] = new int[MAP_WIDTH];
	}

	// Populate The Array
	for (unsigned int i = 0; i < MAP_HEIGHT; i++) {
		for (unsigned int j = 0; j < MAP_WIDTH; j++) {
			m_map[i][j] = map[i][j];
		}
	}
}
LevelMap::~LevelMap() {
	// Delete All Elements Of The Array
	for (unsigned int i = 0; i < MAP_HEIGHT; i++) {
		delete[] m_map[i];
	}
	delete[] m_map;
}

int LevelMap::GetTileAt(unsigned int h, unsigned int w) {
	if (h < MAP_HEIGHT && w < MAP_WIDTH) {
		return m_map[h][w];
	}
	return 0;
}