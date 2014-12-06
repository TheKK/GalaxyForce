/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: renderable.cpp
 */

#include "renderable.h"

uint32_t Renderable::objectCount_ = 0;

Renderable::Renderable()
{
	objectCount_++;
	//SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION,
		     //"Renderable object cound: %d\n", objectCount_);
}

Renderable::~Renderable()
{
	objectCount_--;
	//SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION,
		     //"Renderable object cound: %d\n", objectCount_);
}

SDL_Texture*
Renderable::loadTexture(const char* filePath, SDL_Renderer* renderer,
			Uint8 r, Uint8 g, Uint8 b)
{
	SDL_assert(renderer != nullptr);

	SDL_Surface* loadedImage = nullptr;
	SDL_Texture* tex = nullptr;
	string fullPath;

	fullPath = SDL_GetBasePath();
	fullPath += filePath;

	loadedImage = IMG_Load(fullPath.c_str());
	if (loadedImage == nullptr) {
		string errMsg("IMG error while opening: ");
		errMsg += IMG_GetError();
		SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, errMsg.c_str());
		return nullptr;
	}

	SDL_SetColorKey(loadedImage, SDL_TRUE,
			SDL_MapRGB(loadedImage->format, r, g, b));

	tex = SDL_CreateTextureFromSurface(renderer, loadedImage);
	if (tex == nullptr) {
		string errMsg("SDL error while converting surface: ");
		errMsg += SDL_GetError();
		SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, errMsg.c_str());
	}

	SDL_SetTextureBlendMode(tex, SDL_BLENDMODE_BLEND);

	SDL_FreeSurface(loadedImage);

	return tex;
}

void
Renderable::setRenderer(SDL_Renderer* renderer)
{
	targetRenderer_ = renderer;
}

void
Renderable::hide()
{
	visable_ = false;
}

void
Renderable::show()
{
	visable_ = true;
}

void
Renderable::setVisable(bool value)
{
	visable_ = value;
}

bool
Renderable::isVisable() const
{
	return visable_;
}
