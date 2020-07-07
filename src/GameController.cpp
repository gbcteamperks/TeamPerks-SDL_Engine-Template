#include "GameController.h"

GameController::GameController(SDL_GameController* controller):
	handle(controller), DPAD_UP(false), DPAD_DOWN(false), DPAD_LEFT(false), DPAD_RIGHT(false),
	START_BUTTON(false), BACK_BUTTON(false), LEFT_SHOULDER(false), RIGHT_SHOULDER(false),
	RIGHT_STICK_X(false), RIGHT_STICK_Y(false)
{}

GameController::~GameController()
= default;

void GameController::update()
{
    // DPAD Buttons
    DPAD_UP = SDL_GameControllerGetButton(handle, SDL_CONTROLLER_BUTTON_DPAD_UP);
    DPAD_DOWN = SDL_GameControllerGetButton(handle, SDL_CONTROLLER_BUTTON_DPAD_DOWN);
    DPAD_LEFT = SDL_GameControllerGetButton(handle, SDL_CONTROLLER_BUTTON_DPAD_LEFT);
    DPAD_RIGHT = SDL_GameControllerGetButton(handle, SDL_CONTROLLER_BUTTON_DPAD_RIGHT);

    // control buttons
    START_BUTTON = SDL_GameControllerGetButton(handle, SDL_CONTROLLER_BUTTON_START);
    BACK_BUTTON = SDL_GameControllerGetButton(handle, SDL_CONTROLLER_BUTTON_BACK);
    GUIDE_BUTTON = SDL_GameControllerGetButton(handle, SDL_CONTROLLER_BUTTON_GUIDE);

    // shoulders
    LEFT_SHOULDER = SDL_GameControllerGetButton(handle, SDL_CONTROLLER_BUTTON_LEFTSHOULDER);
    RIGHT_SHOULDER = SDL_GameControllerGetButton(handle, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER);

    // face buttons
    A_BUTTON[0] = A_BUTTON[1];
    B_BUTTON[0] = B_BUTTON[1];
    X_BUTTON[0] = X_BUTTON[1];
    Y_BUTTON[0] = Y_BUTTON[1];
    A_BUTTON[1] = SDL_GameControllerGetButton(handle, SDL_CONTROLLER_BUTTON_A);
    B_BUTTON[1] = SDL_GameControllerGetButton(handle, SDL_CONTROLLER_BUTTON_B);
    X_BUTTON[1] = SDL_GameControllerGetButton(handle, SDL_CONTROLLER_BUTTON_X);
    Y_BUTTON[1] = SDL_GameControllerGetButton(handle, SDL_CONTROLLER_BUTTON_Y);

    // sticks
    
    LEFT_STICK_X[1] = SDL_GameControllerGetAxis(handle, SDL_CONTROLLER_AXIS_LEFTX);
    LEFT_STICK_Y[1] = SDL_GameControllerGetAxis(handle, SDL_CONTROLLER_AXIS_LEFTY);

    if (LEFT_STICK_X[1] > deadZone || LEFT_STICK_X[1] < -deadZone)
    {
        LEFT_STICK_X[0] = LEFT_STICK_X[1];
    }
    if (LEFT_STICK_Y[1] > deadZone || LEFT_STICK_Y[1] < -deadZone)
    {
        LEFT_STICK_Y[0] = LEFT_STICK_Y[1];
    }

    LEFT_STICK_BUTTON = SDL_GameControllerGetButton(handle, SDL_CONTROLLER_BUTTON_LEFTSTICK);

    RIGHT_STICK_X = SDL_GameControllerGetAxis(handle, SDL_CONTROLLER_AXIS_RIGHTX);
    RIGHT_STICK_Y = SDL_GameControllerGetAxis(handle, SDL_CONTROLLER_AXIS_RIGHTY);
    RIGHT_STICK_BUTTON = SDL_GameControllerGetButton(handle, SDL_CONTROLLER_BUTTON_RIGHTSTICK);
}

glm::vec2 GameController::getLeftJoystickPosition()
{
    return glm::vec2(LEFT_STICK_X[0], LEFT_STICK_Y[0]);
}

bool GameController::Arealeased()
{
    if (A_BUTTON[0] == true && A_BUTTON[1] == false) 
    {
        return true;
    }
    return false;
}

bool GameController::Brealeased()
{
    if (B_BUTTON[0] == true && B_BUTTON[1] == false)
    {
        return true;
    }
    return false;
}

bool GameController::Xrealeased()
{
    if (X_BUTTON[0] == true && X_BUTTON[1] == false)
    {
        return true;
    }
    return false;
}

bool GameController::Yrealeased()
{
    if (Y_BUTTON[0] == true && Y_BUTTON[1] == false)
    {
        return true;
    }
    return false;
}
