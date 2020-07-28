#pragma once
#include "Enemy.h"
#include "Animation.h"
#include "PlayerAnimationState.h"
#include "UIElement.h"
#include <map>
#include "SkeletonAnimationState.h"

class SkeletonEnemy : public Enemy
{
public:
	SkeletonEnemy(glm::vec2 position);
	/*SkeletonEnemy();*/
	~SkeletonEnemy();

	//Life cycle methods
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	void skeltnAtk();
	//animation variables
	void setAnimationState(SkeltnAnimationState new_state);
	void setAnimation(const Animation& animation);
	void m_buildAnimations();
	void Patrol();

private:
	
	SpriteSheet* m_pSpriteSheet;
	SkeltnAnimationState m_currentAnimationState;
	std::unordered_map<std::string, Animation> m_pAnimations;
	bool m_enemyFacingRight = true;
	bool m_enemyWaitToFire = false;
	float m_prevTime = 0.00f;
	float m_currentTime = 0.00f;
	//UI
	int m_randomAction = rand() % 2;
	int m_lifeRedCounter;
	std::vector<UIElement*> UI;

};