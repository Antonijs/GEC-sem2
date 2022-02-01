#include <iostream>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "constants.h"

using namespace std;

// Window Global
SDL_Window* g_window = nullptr;

bool InitSDL();
void CloseSDL();
bool Update();

int main(int argc, char* args[]) {
    if (InitSDL()) {
        bool quit = false;

        while (!quit) {
            quit = Update();
        }
    }

    CloseSDL();

    return 0;
}

// Open Window
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

// Close Window
void CloseSDL() {
    // Destroy Window
    SDL_DestroyWindow(g_window);
    g_window = nullptr;

    // Quit SDL Subsystem
    IMG_Quit();
    SDL_Quit();
}

// Game Loop
bool Update() {
    // Event Handler
    SDL_Event e;

    // Get Events
    SDL_PollEvent(&e);

    // Handle Events
    switch (e.type) {

        // Click Keyboard Events
    case SDL_KEYUP:
        switch (e.key.keysym.sym) {
            // Click Keyboard 'X' Button to Quit
        case SDLK_x:
            return true;
            break;
        }
        // Click Window 'X' Button to Quit
    case SDL_QUIT:
        return true;
        break;
    }
    return false;
}