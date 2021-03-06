#pragma once
#include "Ability.h"
#include "Game.h"

class RatBiter : public Ability
{
public:
	RatBiter();
	~RatBiter();

	RatBiter(glm::vec2 position, bool running, int angle, bool pickeable, bool enemyAbility);

	virtual void update() override;
	virtual void draw() override;
	virtual void clean() override;
	static int countOfBiterRats;

	void start();
	void execute(glm::vec2 position, int angle, bool enemyAbility);
	void stop();
	void sound();
	void animation();
	void pickable(glm::vec2 position);
	int ratDirection;
	int ratTag = 0;

	RatBiter* getAbility() override 
	{ 
		return new RatBiter(); 
	}

	
	
	void seekPlayer();
	void guardRatKing();

private:
	//animation variables
	
	void m_buildAnimations();
	void Animate();

	SpriteSheet* m_pSpriteSheet;
	SpriteSheet* m_pSpriteSheetExplosion;
	PlayerAnimationState m_currentAnimationState;

	int walkTimer = 0;

	int timerDie = 0;
	int timer = 0;
	bool die = false;

};

