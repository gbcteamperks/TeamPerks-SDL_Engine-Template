#include "MathManager.h"

glm::vec2 MathManager::Distance(glm::vec2 pos1, glm::vec2 pos2)
{
	glm::vec2 temp;
	temp.x = pos2.x - pos1.x;
	temp.y = pos2.y - pos1.y;
	return temp;
}

double MathManager::AngleBetweenPoints(glm::vec2 pos1, glm::vec2 pos2)
{
	glm::vec2 dis = Distance(pos1, pos2);
	return atan2(dis.y, dis.x)* 180/3.1416;  //in degrees
}

void MathManager::SetDeltas(const double angle, double& dx, double& dy, double fx, double fy)
{
	dx = SetDeltaX(angle, fx);
	dy = SetDeltaY(angle, fy);
}

double MathManager::SetDeltaX(const double angle, double fx)
{
	return cos(angle) * fx;
}

double MathManager::SetDeltaY(const double angle, double fy)
{
	return sin(angle) * fy;
}

double MathManager::Deg2Rad(const double angle)
{
	return angle * (M_PI / 180.0);
}

double MathManager::Rad2Deg(const double angle)
{
	return angle * (180.0 / M_PI);
}


double MathManager::Angle180(double a)
{ // Constrains an angle between -180 and 180.
	a = fmod(a + 180.0, 360.0);
	if (a < 0)
		a += 360.0;
	return a - 180.0;
}

double MathManager::Angle360(double a)
{ // Constrains an angle between 0 and 360.
	a = fmod(a, 360.0);
	if (a < 0)
		a += 360.0;
	return a;
}

double MathManager::LerpD(double a, double b, double factor)
{
	return ((1.0 - factor) * a) + (factor * b);
}

double MathManager::LerpRad(double a, double b, double factor)
{
	double result;
	double diff = b - a;
	if (diff < -M_PI)
	{
		b += M_PI * 2;
		result = LerpD(a, b, factor);
		if (result >= M_PI * 2)
			result -= M_PI * 2;
	}
	else if (diff > M_PI)
	{
		b -= M_PI * 2;
		result = LerpD(a, b, factor);
		if (result < 0.0)
			result += M_PI * 2;
	}
	else
		result = LerpD(a, b, factor);
	return result;
}