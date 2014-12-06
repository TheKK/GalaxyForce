/*
 * Author: KK <thumbd03803@gmail.com>
 *
 * File: gameActorController.cpp
 */

#include "gameActorController.h"

GameActorController::GameActorController():
	keyState_(SDL_GetKeyboardState(nullptr))
{
	settingFileName_ = DEFAULT_SETTING_FILE;
	if(!(readSettingFromFile(settingFileName_.c_str())))
		useDefaultSetting();
}

GameActorController::GameActorController(const char* filePath):
	keyState_(SDL_GetKeyboardState(nullptr))
{
	/* Use file to config button map */
	settingFileName_ = filePath;
	if(!(readSettingFromFile(settingFileName_.c_str())))
		useDefaultSetting();
}

GameActorController::~GameActorController()
{
	saveSettingToFile(settingFileName_.c_str());
}

void
GameActorController::updateState(const SDL_Event& event)
{
	enum Buttons whichButton;
	SDL_Scancode scancode;

	switch (event.type) {
	case SDL_KEYUP:
	case SDL_KEYDOWN:
		/* No repeat */
		if (event.key.repeat)
			return;

		scancode = event.key.keysym.scancode;

		if (scancode == buttonKeyMap_[BUTTON_UP])
			whichButton = BUTTON_UP;
		else if (scancode == buttonKeyMap_[BUTTON_DOWN])
			 whichButton = BUTTON_DOWN;
		else if (scancode == buttonKeyMap_[BUTTON_RIGHT])
			 whichButton = BUTTON_RIGHT;
		else if (scancode == buttonKeyMap_[BUTTON_LEFT])
			 whichButton = BUTTON_LEFT;
		else if (scancode == buttonKeyMap_[BUTTON_JUMP])
			 whichButton = BUTTON_JUMP;
		else if (scancode == buttonKeyMap_[BUTTON_EVADE])
			 whichButton = BUTTON_EVADE;
		else if (scancode == buttonKeyMap_[BUTTON_NORMAL_ATTACK])
			 whichButton = BUTTON_NORMAL_ATTACK;
		else if (scancode == buttonKeyMap_[BUTTON_SPECIAL_ATTACK])
			 whichButton = BUTTON_SPECIAL_ATTACK;

		if (event.key.state == SDL_PRESSED) {
			buttonPressed_[whichButton] = true;
			buttonReleased_[whichButton] = false;
		} else {
			buttonPressed_[whichButton] = false;
			buttonReleased_[whichButton] = true;
		}
		break;
	}
}

void
GameActorController::resetState()
{
	for (bool& e : buttonPressed_)
		e = false;

	for (bool& e : buttonReleased_)
		e = false;
}

bool
GameActorController::readSettingFromFile(const char* filePath)
{
	Json::Value root;
	Json::Reader reader;
	ifstream config;
	bool parseingSuccessful;
	string fullPath;

	/* Open file */
	fullPath = SDL_GetBasePath();
	fullPath += filePath;

	config.open(fullPath, ifstream::in);
	if (!config.is_open()) {
		LogLocator::GetService()->LogWarn(
			"[GameActorController] Setting file not found");
		return false;
	}

	/* Parse Json file */
	parseingSuccessful = reader.parse(config, root);
	config.close();
	if(!parseingSuccessful) {
		LogLocator::GetService()->LogWarn(
			"[GameActorController] Failed to parse json file: %s",
			reader.getFormattedErrorMessages().c_str());
		return false;
	}

	/* Get value */
	GET_SETTING_FROM_JSON(root, BUTTON_JUMP,		"Z");
	GET_SETTING_FROM_JSON(root, BUTTON_NORMAL_ATTACK,	"X");
	GET_SETTING_FROM_JSON(root, BUTTON_SPECIAL_ATTACK,	"S");
	GET_SETTING_FROM_JSON(root, BUTTON_EVADE,		"A");
	GET_SETTING_FROM_JSON(root, BUTTON_UP,			"Up");
	GET_SETTING_FROM_JSON(root, BUTTON_DOWN,		"Down");
	GET_SETTING_FROM_JSON(root, BUTTON_RIGHT,		"Right");
	GET_SETTING_FROM_JSON(root, BUTTON_LEFT,		"Left");

	LogLocator::GetService()->LogDebug(
		"[GameActorController] Setting read from %s successfully",
		filePath);

	return true;
}

bool
GameActorController::saveSettingToFile(const char* filePath)
{
	Json::Value root;
	Json::StyledStreamWriter writer;
	string str;
	ofstream output;

	/* Create file */
	output.open(filePath, ofstream::out);
	if (!output.is_open()) {
		LogLocator::GetService()->LogWarn(
			"[GameActorController] Can not write setting to file");

		return false;
	}

	/* Store current setting */
	SAVE_SETTING_TO_JSON(root, BUTTON_JUMP);
	SAVE_SETTING_TO_JSON(root, BUTTON_NORMAL_ATTACK);
	SAVE_SETTING_TO_JSON(root, BUTTON_SPECIAL_ATTACK);
	SAVE_SETTING_TO_JSON(root, BUTTON_EVADE);
	SAVE_SETTING_TO_JSON(root, BUTTON_UP);
	SAVE_SETTING_TO_JSON(root, BUTTON_DOWN);
	SAVE_SETTING_TO_JSON(root, BUTTON_RIGHT);
	SAVE_SETTING_TO_JSON(root, BUTTON_LEFT);

	writer.write(output, root);

	output.close();

	LogLocator::GetService()->LogDebug(
		"[GameActorController] Setting write to %s successfully",
		filePath);

	return true;
}

void
GameActorController::useDefaultSetting()
{
	LogLocator::GetService()->LogDebug(
		"[GameActorController] Use default mapping");

	buttonKeyMap_[BUTTON_JUMP] = 		SDL_SCANCODE_Z;
	buttonKeyMap_[BUTTON_NORMAL_ATTACK] = 	SDL_SCANCODE_X;
	buttonKeyMap_[BUTTON_SPECIAL_ATTACK] = 	SDL_SCANCODE_S;
	buttonKeyMap_[BUTTON_EVADE] = 		SDL_SCANCODE_A;

	buttonKeyMap_[BUTTON_UP] = 		SDL_SCANCODE_UP;
	buttonKeyMap_[BUTTON_DOWN] = 		SDL_SCANCODE_DOWN;
	buttonKeyMap_[BUTTON_RIGHT] = 		SDL_SCANCODE_RIGHT;
	buttonKeyMap_[BUTTON_LEFT] = 		SDL_SCANCODE_LEFT;
}

bool
GameActorController::getButtonState(enum Buttons which) const
{
	return keyState_[buttonKeyMap_[which]];
}

bool
GameActorController::ifButtonPressed(enum Buttons which) const
{
	return buttonPressed_[which];
}

bool
GameActorController::ifButtonReleased(enum Buttons which) const
{
	return buttonReleased_[which];
}
