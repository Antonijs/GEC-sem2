#include "LevelMap.h"

/*
* When Making a Map, Remember:
* 0 = Empty Space, 1 = Blocked/Occupied Space
*/

using namespace std;
// Level 1
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
//Level 2
LevelMap::LevelMap(string path, int height, int width) {
	m_height = height;
	m_width = width;

	int tempInt = 0;

	inFile.open(path);
	if (inFile.is_open()) {
		m_map = new int* [m_height];
		for (unsigned int i = 0; i < m_height; i++) {
			m_map[i] = new int[m_width];
		}
		for (unsigned int i = 0; i < m_height; i++) {
			for (unsigned int j = 0; j < m_width; j++) {
				inFile >> tempInt;
				cout << tempInt;
				m_map[i][j] = tempInt;
			}
			cout << endl;
		}
	}
	else {
		cerr << "File couldnot be open";
	}
}
LevelMap::~LevelMap() {
	// Delete All Elements Of The Array
	for (unsigned int i = 0; i < m_height; i++) {
		delete[] m_map[i];
	}
	delete[] m_map;

	inFile.close();
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