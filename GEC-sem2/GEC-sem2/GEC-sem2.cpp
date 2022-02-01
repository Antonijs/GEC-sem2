#include <iostream>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "constants.h"

using namespace std;

SDL_Window* g_window = nullptr;

bool InitSDL();
void CloseSDL();

int main(int argc, char* args[]) {
    if (InitSDL()) {
        SDL_Delay(5000);
    }

    CloseSDL();

    return 0;
}

bool InitSDL() {
    // Setup SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        //Setup Failed
        cout << "SDL did not initialise. ERROR: " << SDL_GetError();
        return false;
    }
    else {
        // Setup Passed
        g_window = SDL_CreateWindow("Games Engine Creation",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH,
            SCREEN_HEIGHT,
            SDL_WINDOW_SHOWN);

        // Window Created?
        if (g_window == nullptr) {
            // Window Failed
            cout << "Window was not created. Error: " << SDL_GetError();
            return false;
        }
        return true;
    }
}

void CloseSDL() {
    // Destroy the Window
    SDL_DestroyWindow(g_window);
    g_window = nullptr;

    // Quit SDL Subsystem
    IMG_Quit();
    SDL_Quit();
}