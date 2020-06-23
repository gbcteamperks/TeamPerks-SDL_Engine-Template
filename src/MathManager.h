#pragma once
#ifndef _MATHMANAGER_H_
#define _MATHMANAGER_H_

#include <algorithm>
#include <cmath>
#include "SDL.h"
#include <glm/vec2.hpp>


class MathManager
{
public: // Public methods.
	static glm::vec2 Distance(glm::vec2 pos1, glm::vec2 pos2);
	static double AngleBetweenPoints(glm::vec2 pos1, glm::vec2 pos2);
	static void SetDeltas(const double angle, double& dx, double& dy, double fx = 1.0, double fy = 1.0);
	static double SetDeltaX(const double angle, double fx = 1.0);
	static double SetDeltaY(const double angle, double fy = 1.0);
	static double Deg2Rad(const double angle);
	static double Rad2Deg(const double angle);
	static double Angle180(double a);
	static double Angle360(double a);
	static double LerpD(double first, double second, double perc);
	static double LerpRad(double a, double b, double factor);

private: // Private properties.
	MathManager() {}
};

typedef MathManager MAMA;

#endif