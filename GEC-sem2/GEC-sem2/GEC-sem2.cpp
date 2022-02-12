#include <iostream>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "Constants.h"
#include "Commons.h"

#include "Texture2D.h"

using namespace std;

SDL_Window* g_window = nullptr;
SDL_Renderer* g_renderer = nullptr;
Texture2D* g_texture = nullptr;

bool InitSDL();
void CloseSDL();
bool Update();
void Render();

int main(int argc, char* args[]) {
    if (InitSDL()) {
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

        g_texture = new Texture2D(g_renderer);
        if (!g_texture->LoadFromFile("Images/test.bmp")) {
            return false;
        }

        // Setup Succesfull
        return true;
    }
}

// Close Window
void CloseSDL() {
    // Destroy Window
    SDL_DestroyWindow(g_window);
    g_window = nullptr;

    // Release Renderer
    SDL_DestroyRenderer(g_renderer);
    g_renderer = nullptr;

    // Release Texture
    delete g_texture;
    g_texture = nullptr;

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
        break;
        // Click Window 'X' Button to Quit
    case SDL_QUIT:
        return true;
        break;
    }
    return false;
}

// Render Image
void Render() {
    // Clear Screen
    SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(g_renderer);

    g_texture->Render(Vector2D(),SDL_FLIP_NONE);

    SDL_RenderPresent(g_renderer);
}