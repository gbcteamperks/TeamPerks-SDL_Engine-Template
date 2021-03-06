#pragma once
#ifndef __FIREBALL__
#define __FIREBALL__

#include "Ability.h"
#include "Game.h"

class Fireball : public Ability {
public:
	Fireball();
	Fireball(glm::vec2 position, bool running, int angle, bool pickeable, bool enemyAbility);
	~Fireball();
	virtual void update() override;
	virtual void draw() override;
	virtual void clean() override;

	void start();
	void execute(glm::vec2 position, int angle, bool enemyAbility) ;
	void stop();
	void sound();
	void animation();
	void pickable(glm::vec2 position) ;

	Fireball* getAbility() override { return new Fireball(); }
private:

	std::string m_key;
	StaticSprite* m_pPortrait;

};
#endif