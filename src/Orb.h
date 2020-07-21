#pragma once
#include "Ability.h"
#include "Game.h"

class Orb : public Ability {
public:
	Orb();
	Orb(glm::vec2 position, bool running, int angle, bool pickeable, bool enemyAbility);
	~Orb();
	virtual void update() override;
	virtual void draw() override;
	virtual void clean() override;

	void start();
	void execute(glm::vec2 position, int angle, bool enemyAbility);
	void stop();
	void sound();
	void animation();
	void pickable(glm::vec2 position);
	int& getDamage() { return m_damage; }

	Orb* getAbility() override { return new Orb(); }

private:

	//animation variables
	void m_buildAnimations();
	void AnimateDeath();

	SpriteSheet* m_pSpriteSheet;
	
	PlayerAnimationState m_currentAnimationState;
	

	bool m_running = false;
	bool m_pickable = false;

	int m_damage;
	int m_angle;

	StaticSprite* m_pPortrait;

};