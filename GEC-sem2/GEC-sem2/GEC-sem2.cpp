#include <iostream>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "constants.h"

using namespace std;

SDL_Window* g_window = nullptr;
SDL_Renderer* g_renderer = nullptr;
SDL_Texture* g_texture = nullptr;



bool InitSDL();
void CloseSDL();
bool Update();
void Render();
SDL_Texture* LoadTextureFromFile(string path);
void FreeTexture();


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

        g_texture = LoadTextureFromFile("Images/test.bmp");
        if (g_texture == nullptr) {
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

    // Clear Texture
    FreeTexture();

    // Release Renderer
    SDL_DestroyRenderer(g_renderer);
    g_renderer = nullptr;

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

    // Set Texture Render Position
    SDL_Rect renderLocation = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

    //Render Screen
    SDL_RenderCopyEx(g_renderer, g_texture, NULL, &renderLocation, 0, NULL, SDL_FLIP_NONE);

    SDL_RenderPresent(g_renderer);
}

// Load Textures
SDL_Texture* LoadTextureFromFile(string path) {
    //Remove Memory Used For Previous Texture
    FreeTexture();

    SDL_Texture* p_texture = nullptr;

    // Load Image
    SDL_Surface* p_surface = IMG_Load(path.c_str());
    if (p_surface != nullptr) {
        // Create Texture From Pixels on Surface
        p_texture = SDL_CreateTextureFromSurface(g_renderer, p_surface);
        if (p_texture == nullptr) {
            cout << "Unable to create texture from surface. Error: " << SDL_GetError();
        }
        // Remove Loaded Surface (now that we have a texture)
        SDL_FreeSurface(p_surface);
    }
    else {
        cout << "Unable to create texture from surface. Error: " << SDL_GetError();
    }
    // Return Texture
    return p_texture;
}

void FreeTexture() {
    // Check If Texture Exists Before Removing It
    if (g_texture != nullptr) {
        SDL_DestroyTexture(g_texture);
        g_texture = nullptr;
    }
}