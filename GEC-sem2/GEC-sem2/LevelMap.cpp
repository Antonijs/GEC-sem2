#include "LevelMap.h"

/*
* When Making a Map, Remember:
* 0 = Empty Space, 1 = Blocked/Occupied Space
*/

LevelMap::LevelMap(int map[MAP1_HEIGHT][MAP1_WIDTH]) {
	m_height = MAP1_HEIGHT;
	m_width = MAP1_WIDTH;

	// Allocate Memory For The Level Map
	m_map = new int* [m_height];
	for (unsigned int i = 0; i < m_height; i++) {
		m_map[i] = new int[m_width];
	}

	// Populate The Array
	for (unsigned int i = 0; i < m_height; i++) {
		for (unsigned int j = 0; j < m_width; j++) {
			m_map[i][j] = map[i][j];
		}
	}
}
LevelMap::LevelMap(int map[MAP2_HEIGHT][MAP2_WIDTH]) {
	m_height = MAP2_HEIGHT;
	m_width = MAP2_WIDTH;

	// Allocate Memory For The Level Map
	m_map = new int* [m_height];
	for (unsigned int i = 0; i < m_height; i++) {
		m_map[i] = new int[m_width];
	}

	// Populate The Array
	for (unsigned int i = 0; i < m_height; i++) {
		for (unsigned int j = 0; j < m_width; j++) {
			m_map[i][j] = map[i][j];
		}
	}
}
LevelMap::~LevelMap() {
	// Delete All Elements Of The Array
	for (unsigned int i = 0; i < m_height; i++) {
		delete[] m_map[i];
	}
	delete[] m_map;
}

int LevelMap::GetTileAt(unsigned int h, unsigned int w) {
	if (h < m_height && w < m_width) {
		return m_map[h][w];
	}
	return 0;
}

void LevelMap::ChangeTileAt(unsigned int row, unsigned int colum, unsigned int new_value) {
	if (row < m_height && colum < m_width) {
		m_map[row][colum] = new_value;
	}
}