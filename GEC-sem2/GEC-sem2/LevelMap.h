#pragma once
#ifndef _LEVELMAP_H
#define _LEVELMAP_H

#include "constants.h"

class LevelMap
{	
public:
	LevelMap(int map[MAP1_HEIGHT][MAP1_WIDTH]);
	LevelMap(int map[MAP2_HEIGHT][MAP2_WIDTH]);
	~LevelMap();

	int GetTileAt(unsigned int h, unsigned int w);
	void ChangeTileAt(unsigned int row, unsigned int colum, unsigned int new_value);
private:
	int** m_map;
	int m_height;
	int m_width;
};

#endif