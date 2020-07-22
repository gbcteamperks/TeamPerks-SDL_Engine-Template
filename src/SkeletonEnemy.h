#pragma once
#include "Enemy.h"
#include "Animation.h"
#include "PlayerAnimationState.h"
#include "UIElement.h"
#include <map>

class SkeletonEnemy : public Enemy
{
public:
	SkeletonEnemy(glm::vec2 position);
	SkeletonEnemy();
	~SkeletonEnemy();

	//Life cycle methods
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

private:
	//animation variables
	void m_buildAnimations();
	void Animate();

	int m_randomAction = rand() % 2;
	SpriteSheet* m_pSpriteSheet;
	PlayerAnimationState m_currentAnimationState;
	std::unordered_map<std::string, Animation> m_pAnimations;
	//UI

	int m_lifeRedCounter;
	std::vector<UIElement*> UI;

};