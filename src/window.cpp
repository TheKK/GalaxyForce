/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: window.cpp
 */

#include "window.h"

SDL_Window* Window::window_ = nullptr;
string Window::title_;

SDL_Renderer* Window::renderer_ = nullptr;
SDL_Color Window::clearColor_ = {31, 31, 31, 255};

bool Window::isFocused_ = false;
bool Window::isWindowed_ = true;

void
Window::init(const char* title, Uint32 width, Uint32 height)
{
	title_ = title;

	/* Create and setup new SDL window, and check error */
	window_ = SDL_CreateWindow(
		title_.c_str(),
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		width, height,
		SDL_WINDOW_SHOWN
		);
	if (window_ == nullptr) {
		string errMsg("SDL window error: ");
		errMsg += SDL_GetError();
		throw runtime_error(errMsg);
	}

	/* Create and setup new SDL renderer, and check error */
	renderer_ = SDL_CreateRenderer(
		window_,
		-1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
		);
	if (renderer_ == nullptr) {
		string errMsg("SDL renderer error: ");
		errMsg += SDL_GetError();
		throw runtime_error(errMsg);
	}

	/* Make fullscreen fit physical screen */
	SDL_RenderSetLogicalSize(renderer_, width, height);
}

void
Window::quit()
{
	SDL_DestroyWindow(window_);
	window_ = nullptr;

	SDL_DestroyRenderer(renderer_);
	renderer_ = nullptr;
}

void
Window::eventHandler(const SDL_Event& event)
{
	switch (event.type) {
	case SDL_WINDOWEVENT:
		if (event.window.windowID == ID()) {
			switch (event.window.event) {
				//Get mouse focus
			case SDL_WINDOWEVENT_ENTER:
				isFocused_ = true;
				break;
				//Lost mouse focus
			case SDL_WINDOWEVENT_LEAVE:
				isFocused_ = false;
				break;
			}
		}
	}
}

void
Window::clear()
{
	SDL_SetRenderDrawColor(renderer_,
			       clearColor_.r,
			       clearColor_.g,
			       clearColor_.b,
			       clearColor_.a);
	SDL_RenderClear(renderer_);
}

void
Window::present()
{
	SDL_RenderPresent(renderer_);
}

void
Window::resize(int width, int height)
{
	SDL_SetWindowSize(window_, width, height);
}

void
Window::setTitle(const string& title)
{
	SDL_SetWindowTitle(window_, title.c_str());
}

void
Window::moveTo(int x, int y)
{
	SDL_SetWindowPosition(window_, x, y);
}

void
Window::show()
{
	SDL_ShowWindow(window_);
}

void
Window::hide()
{
	SDL_HideWindow(window_);
}

void
Window::setClearColor(SDL_Color value)
{
	clearColor_ = value;
}

int
Window::posX()
{
	int xToReturn;
	SDL_GetWindowPosition(window_, &xToReturn, nullptr);
	return xToReturn;
}


int
Window::posY()
{
	int yToReturn;
	SDL_GetWindowPosition(window_, nullptr, &yToReturn);
	return yToReturn;
}

int
Window::width()
{
	int wToReturn;
	SDL_GetWindowSize(window_, &wToReturn, nullptr);
	return wToReturn;
}

int
Window::height()
{
	int hToReturn;
	SDL_GetWindowSize(window_, nullptr, &hToReturn);
	return hToReturn;
}

SDL_Rect
Window::rect()
{
	SDL_Rect rectToReturn;
	SDL_GetWindowSize(window_, &rectToReturn.w, &rectToReturn.h);
	SDL_GetWindowPosition(window_, &rectToReturn.x, &rectToReturn.y);
	return rectToReturn;
}

bool
Window::isWindowed()
{
	return isWindowed_;
}

bool
Window::isFocused()
{
	return isFocused_;
}

SDL_Window*
Window::window()
{
	return window_;
}

SDL_Renderer*
Window::renderer()
{
	return renderer_;
}

Uint32
Window::ID()
{
	return SDL_GetWindowID(window_);
}
