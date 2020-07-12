#pragma once
#include "Ability.h"
#include "Game.h"

class ExplosiveSpider : public Ability {
public:
	ExplosiveSpider();
	ExplosiveSpider(glm::vec2 position, bool running, int angle, bool pickeable, bool enemyAbility);
	~ExplosiveSpider();
	virtual void update() override;
	virtual void draw() override;
	virtual void clean() override;

	void start();
	void execute(glm::vec2 position, int anglee, bool enemyAbility);
	void stop();
	void sound();
	void animation();
	void pickable(glm::vec2 position);

	ExplosiveSpider* getAbility() override { return new ExplosiveSpider();}

private:

	//animation variables
	void m_buildAnimations();
	void AnimateDeath();

	SpriteSheet* m_pSpriteSheet;
	SpriteSheet* m_pSpriteSheetExplosion;
	PlayerAnimationState m_currentAnimationState;
	std::unordered_map<std::string, Animation> m_pAnimations;

	bool m_running = false;
	bool m_pickable = false;

	int walkTimer = 0, explosionTimer = 0;
	int m_damage;

	StaticSprite* m_pPortrait;

};