#include <iostream>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include <string>

#include "Constants.h"
#include "Commons.h"

#include "Texture2D.h"
#include "GameScreenManager.h"

using namespace std;

SDL_Window* g_window = nullptr;
SDL_Renderer* g_renderer = nullptr;
GameScreenManager* game_screen_manager;
Mix_Music* g_music = nullptr;

SCREENS g_current_screen;
Uint32 g_old_time;

bool InitSDL();
void CloseSDL();
bool Update();
void Render();
void LoadMusic(string path);

int main(int argc, char* args[]) {
    if (InitSDL()) {
        // Set Up Level
        game_screen_manager = new GameScreenManager(g_renderer, SCREEN_INTRO);

        // Set Up Time
        g_old_time = SDL_GetTicks();

        bool quit = false;
        while (!quit) {
            Render();
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

        // Setup Renderer
        g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);

        // Window Created?
        if (g_window == nullptr) {
            // Window Failed
            cout << "Window was not created. Error: " << SDL_GetError();
            return false;
        }

        // Renderer Created?
        if (g_renderer != nullptr) {
            //init PNG loading
            int imageFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imageFlags) & imageFlags)) {
                cout << "SDL_Image could not initialise. Error: " << IMG_GetError();
                return false;
            }
        }
        else {
            cout << "Renderer could not initialise. Error: " << SDL_GetError();
            return false;
        }    
        
        // Initialise Mixer
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
            cout << "Mixer could not initialise. Error: " << Mix_GetError();
            return false;
        }

        // Setup Succesfull
        return true;
    }
}

// Close Window
void CloseSDL() {
    // Destroy Music
    Mix_FreeMusic(g_music);
    g_music = nullptr;

    // Destroy Window
    SDL_DestroyWindow(g_window);
    g_window = nullptr;

    // Release Renderer
    SDL_DestroyRenderer(g_renderer);
    g_renderer = nullptr;

    // Destroy Game Screen Manager
    delete game_screen_manager;
    game_screen_manager = nullptr;

    // Quit SDL Subsystem
    IMG_Quit();
    SDL_Quit();
}

// Game Loop
bool Update() {
    // Update Time
    Uint32 new_time = SDL_GetTicks();

    // Event Handler
    SDL_Event e;

    // Get Events
    SDL_PollEvent(&e);

    g_current_screen = game_screen_manager->GetScreen();

    // Handle Events
    switch (e.type) {

        // Click Keyboard Events
    case SDL_KEYUP:
        switch (g_current_screen) {
        case SCREEN_INTRO:
            game_screen_manager = new GameScreenManager(g_renderer, SCREEN_MENU);
            break;

        case SCREEN_MENU:
            switch (e.key.keysym.sym) {
            case SDLK_1:
                game_screen_manager = new GameScreenManager(g_renderer, SCREEN_LEVEL1);
                break;

            case SDLK_2:
                game_screen_manager = new GameScreenManager(g_renderer, SCREEN_LEVEL2);
                break;
                
            case SDLK_3:
                game_screen_manager = new GameScreenManager(g_renderer, SCREEN_HIGHSCORES);
                break;
            }
            break;

        case SCREEN_LEVEL1:
        case SCREEN_LEVEL2:
            switch (e.key.keysym.sym) {
            case SDLK_ESCAPE:
                game_screen_manager = new GameScreenManager(g_renderer, SCREEN_MENU);
                break;
            }
            break;

        case SCREEN_GAMEOVER:
            switch (e.key.keysym.sym) {
            case SDLK_ESCAPE:
                game_screen_manager = new GameScreenManager(g_renderer, SCREEN_MENU);
                break;

            case SDLK_SPACE:
                game_screen_manager = new GameScreenManager(g_renderer, SCREEN_HIGHSCORES);
                break;
            }
            break;

        case SCREEN_HIGHSCORES:
            game_screen_manager = new GameScreenManager(g_renderer, SCREEN_MENU);
            break;
        }
        break;
    case SDL_QUIT:
        return true;
        break;
    }
    game_screen_manager->Update((float)(new_time - g_old_time) / 1000.0f, e);
    g_old_time = new_time;

    return false;
}

// Render Image
void Render() {
    // Clear Screen
    SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(g_renderer);

    game_screen_manager->Render();

    SDL_RenderPresent(g_renderer);
}