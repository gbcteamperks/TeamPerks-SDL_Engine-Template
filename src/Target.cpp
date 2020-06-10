#include "Target.h"
#include "TextureManager.h"


Target::Target()
{
	TheTextureManager::Instance()->load("../Assets/Sprites/magicenemy-projectile.png","circle");

	auto size = TheTextureManager::Instance()->getTextureSize("circle");
	//setWidth(size.x);
	//setHeight(size.y);
	//getTransform()->position = glm::vec2(100.0f, 100.0f);

	setType(PROJECTILE);
}

Target::~Target()
= default;

void Target::draw()
{
	// alias for x and y
	auto x = getTransform()->position.x = m_x;
	auto y = getTransform()->position.y = m_y;

	// draw the target
	TheTextureManager::Instance()->draw("circle", x, y, 0, 255, true);
}


void Target::setXY(int x, int y)
{
	m_x = x;
	m_y = y;
}

void Target::update()
{
}

void Target::clean()
{
}
