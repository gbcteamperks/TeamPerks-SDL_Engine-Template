#pragma once
#ifndef _DEBUGMANAGER_H_
#define _DEBUGMANAGER_H_

#include <vector>
#include "SDL.h"

class DebugManager
{
private:
	static std::vector<SDL_Point> s_points;
	static std::vector<SDL_Color> s_colors;

	DebugManager();

public:

	static int s_debugMode;
	static void drawLine(const SDL_Point start, const SDL_Point end, const SDL_Color col);
	static void queueLine(const SDL_Point start, const SDL_Point end, const SDL_Color col);
	static void flushLines();
	static void drawRay(const SDL_Point start, const double angle, const double length, const SDL_Color col);
	static void quit();
};

#endif