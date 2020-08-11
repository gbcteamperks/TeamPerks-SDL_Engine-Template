#pragma once
#include "Enemy.h"
#include "Animation.h"
#include "PlayerAnimationState.h"
#include "SpriteSheet.h"
#include"UIElement.h"
#include "Ability.h"
#include <map>

class RatKing : public Enemy{
public:
	RatKing(glm::vec2 position);
	~RatKing();

	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	
	void useCurrentAbility();
	void m_pushBack();

private:
	//animation variables
	void m_buildAnimations();
	void Animate();

	glm::vec2 playerPos;
	glm::vec2 directionToPush;
	glm::vec2 ratBiterPosition;
	bool abilityUsed = false;
	bool pushBackGo = false;
	int currentTime;
	int duration = 1;
	std::vector<UIElement*> UI;
	int m_lifeRedCounter;
	bool m_flip;

	SpriteSheet* m_pSpriteSheet;
	PlayerAnimationState m_currentAnimationState;
	std::unordered_map<std::string, Animation> m_pAnimations;

};