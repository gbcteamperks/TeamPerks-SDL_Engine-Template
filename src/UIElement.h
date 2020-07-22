#pragma once
#ifndef __UI_ELEMENT__
#define __UI_ELEMENT__


#include <vector>
#include "GameObject.h"
#include "Player.h"


class UIElement
{
public:
	explicit UIElement();
	~UIElement();

	// Inherited via GameObject
	virtual void draw();
	virtual void draw(const int a);
	virtual void update(GameObject* player);
	virtual void update(Player* player) {}
	virtual void clean();


private:
	 
};
#endif
