#pragma once
#ifndef _TEXTRENDERER_H
#define _TEXTRENDERER_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class TextRenderer
{
public:
	TextRenderer(SDL_Renderer* renderer);
	~TextRenderer();

	void Render(int x, int y);
	bool LoadFont(const std::string path, int font_size, const std::string message, SDL_Color colour);
	void Free();
private:
	SDL_Renderer* m_renderer;
	SDL_Texture* m_texture;
	mutable SDL_Rect m_text_rect;
	TTF_Font* m_font;
};

#endif