#pragma once
#ifndef __ABILITY__
#define __ABILITY__
#include "DisplayObject.h"
#include "StaticSprite.h"

class Ability : public DisplayObject {
public:
	Ability();
	virtual ~Ability();
	// Inherited via GameObject
	virtual void draw() override = 0;
	virtual void update() override = 0;
	virtual void clean() override = 0;

	virtual void execute(glm::vec2 position, int angle) = 0;
	virtual void stop() = 0;
	virtual void sound() = 0;
	virtual void animation() = 0;
	virtual void pickable(glm::vec2 position) = 0;
	
protected:
	
	
};
#endif