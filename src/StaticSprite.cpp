#include "StaticSprite.h"

StaticSprite::StaticSprite(std::string spritePath, std::string name, float posX, float posY)
{
	this->name = name;
	TheTextureManager::Instance()->load(spritePath, name);

	auto size = TheTextureManager::Instance()->getTextureSize(name);
	setWidth(size.x);
	setHeight(size.y);

	getTransform()->position = glm::vec2(posX, posY);
	setType(STATICSPRITE);

}

StaticSprite::~StaticSprite()
{
}

void StaticSprite::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	// draw the ship
	TheTextureManager::Instance()->draw(name, x, y, 0, 255, true);
}

void StaticSprite::update()
{
}

void StaticSprite::clean()
{
}
