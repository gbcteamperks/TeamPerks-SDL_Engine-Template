#include "LifeBar.h"
#include "TextureManager.h"

LifeBar::LifeBar()
{
	TextureManager::Instance()->load("../Assets/textures/LifeBar.png", "LifeBar");
}

LifeBar::~LifeBar()
= default;

void LifeBar::draw()
{
	TextureManager::Instance()->draw("LifeBar", 30, 600, 0.0, 255, SDL_FLIP_NONE, 160, 150);
}

void LifeBar::update(GameObject* player)
{
}

void LifeBar::clean()
{
}
