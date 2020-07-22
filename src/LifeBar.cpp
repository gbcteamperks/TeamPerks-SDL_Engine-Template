#include "LifeBar.h"
#include "TextureManager.h"

LifeBar::LifeBar()
{
	TextureManager::Instance()->load("../Assets/textures/AbilitiesLights.png", "LifeBar");
	
}

LifeBar::~LifeBar()
= default;

void LifeBar::draw()
{
	TextureManager::Instance()->draw("LifeBar", src, 0.0, 255, SDL_FLIP_NONE, {30, 600, 160, 150, });
}

void LifeBar::update(Player* player)
{
	if (player->getAbilitiesList().size() == 1) {
		src = { 0, 0, 400, 325 };
	}
	else if (player->getAbilitiesList().size() == 2)
	{
		src = { 400 * (1 + player->getAbilitieCounter()), 0, 400, 325 };
	}
	else if (player->getAbilitiesList().size() == 3)
	{
		src = { 400 * (3 + player->getAbilitieCounter()), 0, 400, 325 };
	}
	else if (player->getAbilitiesList().size() == 4)
	{
		src = { 400 * (6 + player->getAbilitieCounter()), 0, 400, 325 };
	}
}

void LifeBar::clean()
{
}
