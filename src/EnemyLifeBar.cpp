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
	TextureManager::Instance()->draw("EnemyLifeBarRed", dstx, dsty, 0.0, 255, SDL_FLIP_NONE, 50, 5);
	TextureManager::Instance()->draw("EnemyLifeBarGreen", dstx, dsty, 0.0, 255, SDL_FLIP_NONE, greenx, 5);
}

void EnemyLifeBar::update(GameObject * player)
{
	dstx = player->getTransform()->position.x - 25;
	dsty = player->getTransform()->position.y - 20;

	greenx = player->getLife() * .50; 

}

void EnemyLifeBar::clean()
{
}
