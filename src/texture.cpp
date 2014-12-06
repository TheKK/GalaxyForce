/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: texture.cpp
 */

#include "texture.h"

Texture::Texture()
{
}

Texture::Texture(const char* filePath, SDL_Renderer* renderer,
		 Uint8 r, Uint8 g, Uint8 b)
{
	load(filePath, renderer, r, g, b);
}

Texture::~Texture()
{
	release_();
}

void
Texture::load(const char* filePath, SDL_Renderer* renderer,
	      Uint8 r, Uint8 g, Uint8 b)
{
	setRenderer(renderer);
	texture_ = loadTexture(filePath, renderer, r, g, b);
}

void
Texture::rotate(double value)
{
	degree_ += value;
	if (degree_ > 360.0)
		degree_ -= 360.0;
	else if (degree_ < 0)
		degree_ = 360 - degree_;
}

void
Texture::setAlpha(Uint8 value)
{
	SDL_SetTextureAlphaMod(texture_, value);
	alpha_ = value;
}

SDL_Texture*
Texture::object() const
{
	return texture_;
}

void
Texture::setBlendMode(SDL_BlendMode mode)
{
	SDL_assert_paranoid(texture_ != nullptr);

	SDL_SetTextureBlendMode(texture_, mode);
}

void
Texture::render(const SDL_Rect& rect)
{
	if (!visable_)
		return;

	SDL_RenderCopyEx(targetRenderer_, texture_, nullptr, &rect,
			 degree_, nullptr, SDL_FLIP_NONE);
}

void
Texture::renderEx(const SDL_Rect& rect, SDL_Point* rotateCenter)
{
	if (!visable_)
		return;

	SDL_RenderCopyEx(targetRenderer_, texture_, nullptr, &rect,
			 degree_, rotateCenter, SDL_FLIP_NONE);
}

void
Texture::renderFullWindow()
{
	if (!visable_)
		return;

	SDL_RenderCopyEx(targetRenderer_, texture_, nullptr, nullptr,
			 degree_, nullptr, SDL_FLIP_NONE);
}

void
Texture::release_()
{
	if (texture_ != nullptr)
		SDL_DestroyTexture(texture_);
	texture_ = nullptr;
}
