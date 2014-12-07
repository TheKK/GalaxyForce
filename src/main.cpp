/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: main.cpp
 */

#include <stdexcept>
#include <string>
#include <SDL.h>
#include <SDL_image.h>

#include "gameState.h"
#include "logLocator.h"
#include "sdlLog.h"
#include "soundEngine.h"
#include "timer.h"
#include "userEvent.h"
#include "window.h"
#include "ludumGameState.h"

#ifndef SDL_ASSERT_LEVEL
	#define SDL_ASSERT_LEVEL	3
#else
	#undef SDL_ASSERT_LEVEL
	#define SDL_ASSERT_LEVEL	3
#endif

#define GAME_FPS	60.0

using namespace std;

void PrintVersionInfo()
{
	SDL_version compiled;
	SDL_version linked;

	SDL_VERSION(&compiled);
	SDL_GetVersion(&linked);

	LogLocator::GetService()->LogInfo(
		"compiled against SDL version %d.%d.%d.\n",
		compiled.major, compiled.minor, compiled.patch);

	LogLocator::GetService()->LogInfo(
		"Linked against SDL version %d.%d.%d.\n",
		linked.major, linked.minor, linked.patch);

	LogLocator::GetService()->LogInfo(
		"SDL_image linked version %d.%d.%d\n",
		IMG_Linked_Version()->major,
		IMG_Linked_Version()->minor,
		IMG_Linked_Version()->patch
	);
}

void
InitSystem()
{
	/* Initialize SDL, SDL2_image and SDL2_ttf */
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		string errMsg("Error while initialize SDL2 subsystem: ");
		errMsg += SDL_GetError();
		throw runtime_error(errMsg);
	}

	if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) < 0) {
		string errMsg("Error while initialize SDL2_image: ");
		errMsg += IMG_GetError();
		throw runtime_error(errMsg);
	}

	/* Window setup */
	Window::init("Galaxy Force", 640, 360);

	/* Register user events */
	UserEvent::Init();
	SoundEngine::Init();

	/* Regist SDL as our log system */
	LogLocator::Init();
	LogLocator::Register(new SDLLog());

	/* Make game "pixelate" */
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");

	srand(time(nullptr));

	PrintVersionInfo();
}

void
CleanUp()
{
	LogLocator::GetService()->LogDebug("Exit successes");

	delete (LogLocator::GetService());
	LogLocator::Register(nullptr);

	SoundEngine::Quit();
	Window::quit();

	SDL_Quit();
	IMG_Quit();
}

void
ChangeState(GameState** state)
{
	GameState* newState = nullptr;

	switch ((*state)->next()) {
	case GAME_STATE_MAIN:
	case GAME_STATE_QUIT:
		newState = nullptr;
		break;
	case GAME_STATE_TEST:
		newState = new LudumGameState();
		break;
	default:
		LogLocator::GetService()->LogError("GameState trasform error");
		break;
	}

	delete *state;

	if(newState)
		*state = newState;
	else
		*state = nullptr;
}

int
main(int argc, char* argv[])
{
	Timer timer;
	SDL_Event event;
	GameState* gameState;

	try {
		/* The creation of world... */
		InitSystem();

		gameState = new LudumGameState();

		/* The cycle of life... */
		while (gameState) {
			timer.Start();

			/* EventHandler */
			while (SDL_PollEvent(&event))
				gameState->eventHandler(event);

			gameState->update();

			Window::clear();
			gameState->render();
			Window::present();

			if (gameState->hasNext())
				ChangeState(&gameState);

			if (timer.GetTicks() < (1000.0 / (double) GAME_FPS)) {
				SDL_Delay((1000.0 / (double) GAME_FPS) -
					  timer.GetTicks());
			}
		}
	} catch (runtime_error& e) {
		cerr << e.what() << endl;
	}

	CleanUp();

	return 0;
}
