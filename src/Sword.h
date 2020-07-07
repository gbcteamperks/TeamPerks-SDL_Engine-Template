#pragma once
#ifndef __SWORD__
#define __SWORD__

#include "Ability.h"
#include "Game.h"

class Sword : public Ability {
public:
	Sword();
	Sword(glm::vec2 position, bool running, int angle, bool pickeable);
	~Sword();
	virtual void update() override;
	virtual void draw() override;
	virtual void clean() override;

	void start();
	void execute(glm::vec2 position, int angle = 0);
	void stop();
	void sound();
	void animation();
	void pickable(glm::vec2 position);

	Sword* getAbility() override { return new Sword(); }

private:

	bool m_running = false;
	bool m_pickable = false;
	int m_damage;
	int m_angle;
	int abilityTimer = 0;
};
#endif