/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: window.h
 */

#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <string>
#include <stdexcept>

#include <SDL2/SDL.h>

using namespace std;

class Window
{
public:
	static void init(const char* title, Uint32 width, Uint32 height);
	static void quit();

	static void eventHandler(const SDL_Event& event);

	static void clear();
	static void present();

	/* Function to control this object */
	static void resize(int width, int height);
	static void setTitle(const string& title);
	static void moveTo(int x, int y);
	static void show();
	static void hide();

	static void setClearColor(SDL_Color value);

	/* Function to get object states or statuses */
	static int posX();
	static int posY();
	static int width();
	static int height();
	static const SDL_Rect* rect();

	static bool isWindowed();
	static bool isFocused();

	static SDL_Window* window();
	static SDL_Renderer* renderer();
	static Uint32 ID();
private:
	Window() {};
	static SDL_Window* window_;
	static string title_;

	static SDL_Rect rect_;

	static SDL_Renderer* renderer_;
	static SDL_Color clearColor_;

	static bool isFocused_;
	static bool isWindowed_;
};

#endif	/* WINDOW_H */
