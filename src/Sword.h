#pragma once
#ifndef __SWORD__
#define __SWORD__

#include "Ability.h"
#include "Game.h"

class Sword : public Ability {
public:
	Sword();
	Sword(glm::vec2 position, bool running, int angle, bool pickeable, bool enemyAbility);
	~Sword();
	virtual void update() override;
	virtual void draw() override;
	virtual void clean() override;

	void start();
	void execute(glm::vec2 position, int angle, bool enemyAbility);
	void stop();
	void sound();
	void animation();
	void pickable(glm::vec2 position);

	Sword* getAbility() override { return new Sword(); }

private:

	int abilityTimer = 0;
};
#endif