#include "Sound.h"
#include <iostream>

void Sound::Play() {
	Mix_PlayChannel(-1, m_sample, 0);
}
bool Sound::Load(std::string path) {
	Free();

	m_sample = Mix_LoadWAV(path.c_str());
	if (m_sample == nullptr) {
		std::cout << "Failed to load sound. Error: " << Mix_GetError() << std::endl;
	}

	return m_sample != nullptr;
}
void Sound::Free() {
	if (m_sample != nullptr) {
		Mix_FreeChunk(m_sample);
		m_sample = nullptr;
	}
}