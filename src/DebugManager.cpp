#include "DebugManager.h"
#include "Game.h"
#include "MathManager.h"
void DebugManager::drawLine(const SDL_Point start, const SDL_Point end, const SDL_Color col)
{
}

void DebugManager::queueLine(const SDL_Point start, const SDL_Point end, const SDL_Color col)
{
	s_points.push_back(start);
	s_points.push_back(end);
	s_colors.push_back(col);
}

void DebugManager::flushLines()
{
	for (unsigned i = 0, j = 0; i < s_points.size(); i += 2, j++) 
	{
		drawLine(s_points[i], s_points[i + 1], s_colors[j]);
	}
	quit();
}

void DebugManager::drawRay(const SDL_Point start, const double angle, const double length, const SDL_Color col)
{
	double dX, dY;
	MAMA::SetDeltas(angle, dX, dY, length, length);
	drawLine({ (int)start.x, (int)start.y }, { (int)(start.x + dX),(int)(start.y + dY) }, col);
}

void DebugManager::quit()
{
	s_points.clear();
	s_colors.clear();
	s_points.shrink_to_fit();
	s_colors.shrink_to_fit();
}

int DebugManager::s_debugMode = 0;
std::vector<SDL_Point>DebugManager::s_points;
std::vector<SDL_Color>DebugManager::s_colors;
