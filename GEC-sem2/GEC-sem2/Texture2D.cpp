#include "Texture2D.h"

#include <iostream>

#include <SDL_image.h>

using namespace std;

Texture2D::Texture2D(SDL_Renderer* renderer) {
	m_renderer = renderer;
}
Texture2D::~Texture2D() {
	Free();
	
	m_renderer = nullptr;
}

bool Texture2D::LoadFromFile(std::string path) {
    //Remove Memory Used For Previous Texture
    Free();

    m_texture = nullptr;

    // Load Image
    SDL_Surface* p_surface = IMG_Load(path.c_str());
    if (p_surface != nullptr) {
        SDL_SetColorKey(p_surface, SDL_TRUE, SDL_MapRGB(p_surface->format, 0, 0xFF, 0xFF));

        // Create Texture From Pixels on Surface
        m_texture = SDL_CreateTextureFromSurface(m_renderer, p_surface);
        if (m_texture == nullptr) {
            cout << "Unable to create texture from surface. Error: " << SDL_GetError();
        }
        else {
            m_width = p_surface->w;
            m_height = p_surface->h;
        }
        // Remove Loaded Surface (now that we have a texture)
        SDL_FreeSurface(p_surface);
    }
    else {
        cout << "Unable to create texture from surface. Error: " << SDL_GetError();
    }
    // Return Whether Process Was Successful
    return m_texture != nullptr;
}
void Texture2D::Free() {
	if (m_texture != nullptr) {
		SDL_DestroyTexture(m_texture);
		m_texture = nullptr;
		m_width = 0;
		m_height = 0;
	}
}
void Texture2D::Render(Vector2D newPosition, SDL_RendererFlip flip, double angle) {
	// Set Texture Render Position
	SDL_Rect renderLocation = { newPosition.x, newPosition.y, m_width, m_height };

	//Render Screen
	SDL_RenderCopyEx(m_renderer, m_texture, NULL, &renderLocation, 0, NULL, flip);
}