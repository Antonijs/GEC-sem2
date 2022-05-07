#include "TextRenderer.h"
#include <iostream>

using namespace std;

TextRenderer::TextRenderer(SDL_Renderer* renderer) {
	m_renderer = renderer;
}
TextRenderer::~TextRenderer() {
	Free();
	m_renderer = nullptr;
}

void TextRenderer::Render(int x, int y) {
	m_text_rect.x = x;
	m_text_rect.y = y;

	SDL_RenderCopy(m_renderer, m_texture, NULL, &m_text_rect);
}
bool TextRenderer::LoadFont(const string path, int font_size, const string message, SDL_Color colour) {
	Free();

	m_font = TTF_OpenFont(path.c_str(), font_size);
	if (!m_font) {
		cout << "Unable to create font. Error " << TTF_GetError();
		return false;
	}
	SDL_Surface* surface = TTF_RenderText_Solid(m_font, message.c_str(), colour);
	if (!surface) {
		cout << "Unable to create surface. Error " << TTF_GetError();
		return false;
	}
	m_texture = SDL_CreateTextureFromSurface(m_renderer, surface);
	if (!m_texture) {
		cout << "Unable to create texture from surface. Error " << TTF_GetError();
		return false;
	}
	TTF_CloseFont(m_font);
	SDL_FreeSurface(surface);

	SDL_QueryTexture(m_texture, nullptr, nullptr, &m_text_rect.w, &m_text_rect.h);
	return m_texture;
}
void TextRenderer::Free() {
	if (m_texture != nullptr) {
		SDL_DestroyTexture(m_texture);
		m_texture = nullptr;
	}
}