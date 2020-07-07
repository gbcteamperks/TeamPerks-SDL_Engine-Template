#pragma once
#include "Enemy.h"
#include "Animation.h"
#include "PlayerAnimationState.h"
#include "SpriteSheet.h"
#include "Ability.h"
#include <map>

class RatKing : public Enemy{
public:
	RatKing();
	~RatKing();

	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	void useCurrentAbility();

private:
	//animation variables
	void m_buildAnimations();
	void Animate();

	glm::vec2 playerPos;
	
	SpriteSheet* m_pSpriteSheet;
	PlayerAnimationState m_currentAnimationState;
	std::unordered_map<std::string, Animation> m_pAnimations;

};