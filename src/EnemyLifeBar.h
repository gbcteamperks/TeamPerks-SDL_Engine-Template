#pragma once
#ifndef __LIFE_BAR__
#define __LIFE_BAR__

#include "UIElement.h"
#include "Enemy.h"
#include "Label.h"

class EnemyLifeBar : public UIElement
{
public:
	EnemyLifeBar(Enemy* enemy);
	~EnemyLifeBar();
	//virtual void draw();
	virtual void draw(const int a);
	virtual void update(Enemy* enemy);
	virtual void clean();
private:
	float greenx, greeny, redx, templife;
	int dstx;
	int dsty;
	Label* m_pBossLabel;
};

#endif