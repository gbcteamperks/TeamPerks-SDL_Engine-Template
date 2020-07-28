#pragma once

#pragma once
#ifndef __LIFE_BAR__
#define __LIFE_BAR__

#include "UIElement.h"

class LifeBar : public UIElement 
{
public:
	LifeBar();
	~LifeBar();

	virtual void draw();
	virtual void update(Player* player);
	virtual void clean();
private:
	
	SDL_Rect src;
};







#endif