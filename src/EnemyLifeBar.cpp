#include "EnemyLifeBar.h"
#include "TextureManager.h"

EnemyLifeBar::EnemyLifeBar()
{
	TextureManager::Instance()->load("../Assets/textures/EnemyLifeBarRed.png", "EnemyLifeBarRed");
	TextureManager::Instance()->load("../Assets/textures/EnemyLifeBarGreen.png", "EnemyLifeBarGreen");
}

EnemyLifeBar::~EnemyLifeBar()
= default;

void EnemyLifeBar::draw()
{
	TextureManager::Instance()->draw("EnemyLifeBarRed", dstx, dsty, 0.0, 255, SDL_FLIP_NONE, 50, 2);
	TextureManager::Instance()->draw("EnemyLifeBarGreen", dstx, dsty, 0.0, 255, SDL_FLIP_NONE, greenx, 2);
}

void EnemyLifeBar::update(GameObject * enemy)
{
	dstx = enemy->getTransform()->position.x - 25;
	dsty = enemy->getTransform()->position.y - 20;

	greenx = enemy->getLife() * .50;

}

void EnemyLifeBar::clean()
{
}
