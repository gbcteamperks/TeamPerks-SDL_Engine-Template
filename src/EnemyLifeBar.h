#pragma once

#pragma once
#ifndef __LIFE_BAR__
#define __LIFE_BAR__

#include "UIElement.h"

class EnemyLifeBar : public UIElement
{
public:
	EnemyLifeBar();
	~EnemyLifeBar();

	virtual void draw();
	virtual void update(GameObject* player);
	virtual void clean();
private:
	int greenx;
	int dstx;
	int dsty;
};

#endif