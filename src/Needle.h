#pragma once

#pragma once
#ifndef __NEEDLE__
#define __NEEDLE__

#include "UIElement.h"

class Needle : public UIElement
{
public:
	Needle();
	~Needle();

	virtual void draw();
	virtual void update(GameObject* player);
	virtual void clean();
private:
	int x;
	int y;
	double angle;

};

#endif