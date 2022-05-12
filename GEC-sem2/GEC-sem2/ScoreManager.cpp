#include "ScoreManager.h"

using namespace std;

ScoreManager::ScoreManager(string path) {
	m_path = path;
	ReadScore();
}
ScoreManager::~ScoreManager() {

}

void ScoreManager::AddScore(int score) {
	outFile.open(m_path);
	if (outFile.is_open()) {
		bool found = false;
		int buffer1, buffer2;
		for (int i = 0; i < TOP_SIZE; i++) {
			if (!found) {
				if (score > m_scores[i] || m_scores[i] == NULL) {
					found = true;
					buffer1 = m_scores[i];
					m_scores[i] = score;
				}
			}
			else {
				buffer2 = m_scores[i];
				m_scores[i] = buffer1;
				buffer1 = buffer2;
			}
			if (m_scores[i] != NULL) {
				outFile << m_scores[i] << endl;
			}
		}
	}
	ReadScore();
	outFile.close();
}

void ScoreManager::ReadScore() {
	m_top = 0;
	inFile.open(m_path);
	if (inFile.is_open()) {
		string buffer;
		while (getline(inFile, buffer)) {
			int score = stoi(buffer);
			m_scores[m_top] = score;

			m_top++;
		}
	}
	inFile.close();
}