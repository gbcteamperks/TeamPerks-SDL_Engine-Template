#pragma once
#ifndef __SLIMEATTACK__
#define __SLIMEATTACK__

#include "Ability.h"
#include "Game.h"

class Slimeattack : public Ability {
public:
	Slimeattack();
	Slimeattack(glm::vec2 position, bool running, int angle, bool pickeable, bool enemyAbility);
	~Slimeattack();
	virtual void update() override;
	virtual void draw() override;
	virtual void clean() override;

	void start();
	void execute(glm::vec2 position, int angle, bool enemyAbility);
	void stop();
	void sound();
	void animation();
	void pickable(glm::vec2 position);


	Slimeattack* getAbility() override { return new Slimeattack(); }
private:

	std::string m_key;
	StaticSprite* m_pPortrait;

};
#endif