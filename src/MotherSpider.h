#pragma once
#include "Enemy.h"
#include "Animation.h"
#include "PlayerAnimationState.h"
#include "SpriteSheet.h"
#include "Ability.h"
#include <map>

class MotherSpider : public Enemy {
public:
	MotherSpider();
	~MotherSpider();

	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	void useCurrentAbility();

private:
	//animation variables
	void m_buildAnimations();
	void Animate();

	int m_randomAction = rand() % 2;
	SpriteSheet* m_pSpriteSheet;
	PlayerAnimationState m_currentAnimationState;
	std::unordered_map<std::string, Animation> m_pAnimations;

};