#include "EnemyLifeBar.h"
#include "TextureManager.h"

EnemyLifeBar::EnemyLifeBar()
{
	TextureManager::Instance()->load("../Assets/textures/EnemyLifeBarRed.png", "EnemyLifeBarRed");
	TextureManager::Instance()->load("../Assets/textures/EnemyLifeBarGreen.png", "EnemyLifeBarGreen");
}

EnemyLifeBar::~EnemyLifeBar()
= default;

void EnemyLifeBar::draw(const int a)
{
	TextureManager::Instance()->draw("EnemyLifeBarRed", dstx, dsty, 0.0, 255, SDL_FLIP_NONE, a * 0.5, 2);
	TextureManager::Instance()->draw("EnemyLifeBarGreen", dstx, dsty, 0.0, 255, SDL_FLIP_NONE, greenx, 2);
}
void EnemyLifeBar::draw() {

}

void EnemyLifeBar::update(GameObject * enemy)
{
	dstx = enemy->getTransform()->position.x - enemy->getHeight()*.5;
	dsty = enemy->getTransform()->position.y - enemy->getHeight() *.5;

	greenx = enemy->getLife() * .50;

}

void EnemyLifeBar::clean()
{
}
