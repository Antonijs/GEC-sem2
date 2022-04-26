#include "Music.h"

#include <iostream>

using namespace std;

void Music::Play() {
    if (Mix_PlayingMusic() == 0) {
        Mix_PlayMusic(m_music, -1);
    }
    else {
        Mix_ResumeMusic();
    }
}
void Music::Pause() {
    if (Mix_PausedMusic() == 0) {
        Mix_PauseMusic();
    }
}
bool Music::Load(std::string path) {
    Free();

    m_music = Mix_LoadMUS(path.c_str());
    if (m_music == nullptr) {
        cout << "Failed to load music. Error: " << Mix_GetError() << endl;
    }

    return m_music != nullptr;
}
void Music::Free() {
    if (m_music != nullptr) {
        Mix_FreeMusic(m_music);
        m_music = nullptr;
    }
}