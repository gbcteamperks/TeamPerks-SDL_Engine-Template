#pragma once
#include "Enemy.h"
#include "Animation.h"
#include "PlayerAnimationState.h"
#include "SpriteSheet.h"
#include "Ability.h"
#include"UIElement.h"
#include <map>

class MotherSpider : public Enemy {
public:
	MotherSpider(glm::vec2 position);
	~MotherSpider();

	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	void useCurrentAbility();
	int& getLife() override { return *m_pLife; }

private:
	//animation variables
	void m_buildAnimations();
	void Animate();

	int m_randomAction = rand() % 2;
	SpriteSheet* m_pSpriteSheet;
	PlayerAnimationState m_currentAnimationState;
	std::unordered_map<std::string, Animation> m_pAnimations;
	//UI
	std::vector<UIElement*> UI;
	int m_lifeRedCounter;

};