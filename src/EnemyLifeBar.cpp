#include "EnemyLifeBar.h"


EnemyLifeBar::EnemyLifeBar(Enemy* enemy)
{
	TextureManager::Instance()->load("../Assets/textures/EnemyLifeBarRed.png", "EnemyLifeBarRed");
	TextureManager::Instance()->load("../Assets/textures/EnemyLifeBarGreen.png", "EnemyLifeBarGreen");
	greeny = 2;
	redx = 50;
	templife = enemy->getLife();
	m_pBossLabel = new Label(enemy->getName(), "Dock51", 20, { 255,255,255,255 }, glm::vec2(50.0f, 30.0f));
}

EnemyLifeBar::~EnemyLifeBar()
= default;

void EnemyLifeBar::draw(const int a)
{

	//(const std::string & id, SDL_Rect src, double angle, int alpha, SDL_RendererFlip flip, SDL_Rect dest)
	TextureManager::Instance()->draw("EnemyLifeBarRed", dstx, dsty, 0.0, 255, SDL_FLIP_NONE, redx, greeny);
	TextureManager::Instance()->draw("EnemyLifeBarGreen", dstx, dsty, 0.0, 255, SDL_FLIP_NONE, greenx, greeny);
	if (a > 300) {
		m_pBossLabel->draw();
	}
}


void EnemyLifeBar::update(Enemy* enemy)
{
	if (enemy->getType() == ENEMY) {
		dstx = enemy->getTransform()->position.x - enemy->getWidth()* 0.4;
		dsty = enemy->getTransform()->position.y - enemy->getHeight()* 0.6;

		greenx = redx * (enemy->getLife()/templife);
	}
	if (enemy->getType() == BOSS) {
		dstx = 10;
		dsty = 10;
		greeny = 10;
		redx = 500;
		greenx = redx * ((float)enemy->getLife() / templife);

	}
}

void EnemyLifeBar::clean()
{
}
