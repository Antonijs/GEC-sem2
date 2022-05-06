#pragma once
#ifndef SCOREMANAGER_H
#define SCOREMANAGER_H

#include "constants.h"

#include <iostream>
#include <fstream>
#include <string>

class ScoreManager
{
public:
	ScoreManager(std::string path);
	~ScoreManager();

	int* GetScores() { return m_scores; }
	void AddScore(int score);
	void ReadScore();
private:
	std::ifstream inFile;
	std::ofstream outFile;

	int m_scores[TOP_SIZE];
	int m_top;

	std::string m_path;
};

#endif