#pragma once
#ifndef __GAME_CONTROLLER__
#define __GAME_CONTROLLER__

#include <SDL.h>
#include <glm/vec2.hpp>

struct GameController
{
	GameController(SDL_GameController* controller);
	~GameController();

	void update();
	glm::vec2 getLeftJoystickPosition();
	bool Arealeased();
	bool Brealeased();
	bool Xrealeased();
	bool Yrealeased();
	SDL_GameController* handle;

	// DPAD Buttons
	bool DPAD_UP;
	bool DPAD_DOWN;
	bool DPAD_LEFT;
	bool DPAD_RIGHT;

	// control buttons
	bool START_BUTTON;
	bool BACK_BUTTON;
	bool GUIDE_BUTTON;

	// shoulder buttons
	bool LEFT_SHOULDER;
	bool RIGHT_SHOULDER;

	// face buttons
	bool A_BUTTON[2] = { false,false };
	bool B_BUTTON[2] = { false,false };
	bool X_BUTTON[2] = { false,false };
	bool Y_BUTTON[2] = { false,false };

	// left stick
	Sint16 LEFT_STICK_X[2];
	Sint16 LEFT_STICK_Y[2];
	bool LEFT_STICK_BUTTON;
	int deadZone = 5000;

	// right stick
	Sint16 RIGHT_STICK_X;
	Sint16 RIGHT_STICK_Y;
	bool RIGHT_STICK_BUTTON;
};

#endif /* defined (__GAME_CONTROLLER__) */