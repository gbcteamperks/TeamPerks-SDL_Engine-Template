#pragma once
#include "Ability.h"
#include "Game.h"

class RatBiter : public Ability
{
public:
	RatBiter();
	~RatBiter();

	RatBiter(glm::vec2 position, bool running, int angle, bool pickeable);

	virtual void update() override;
	virtual void draw() override;
	virtual void clean() override;

	void start();
	void execute(glm::vec2 position, int angle = 0);
	void stop();
	void sound();
	void animation();
	void pickable(glm::vec2 position);

	RatBiter* getAbility() override 
	{ 
		return new RatBiter(); 
	}

private:
	//animation variables
	void m_buildAnimations();
	void Animate();

	SpriteSheet* m_pSpriteSheet;
	SpriteSheet* m_pSpriteSheetExplosion;
	PlayerAnimationState m_currentAnimationState;
	std::unordered_map<std::string, Animation> m_pAnimations;

	bool m_running = false;
	bool m_pickable = false;

	int walkTimer = 0;
	int m_damage;
	int m_angle;

	int timerDie = 0;
	int timer = 0;
	bool die = false;

};

