#include "TitleSprite.h"

TitleSprite::TitleSprite()
{
	TheTextureManager::Instance()->load("../Assets/textures/MonsterSlayerTitle.png", "titleSprite");

	auto size = TheTextureManager::Instance()->getTextureSize("titleSprite");
	setWidth(size.x);
	setHeight(size.y);

	getTransform()->position = glm::vec2(400.0f, 200.0f);
	setType(TITLESPRITE);

}

TitleSprite::~TitleSprite()
{
}

void TitleSprite::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	// draw the ship
	TheTextureManager::Instance()->draw("titleSprite", x, y, 0, 255, true);
}

void TitleSprite::update()
{
}

void TitleSprite::clean()
{
}
