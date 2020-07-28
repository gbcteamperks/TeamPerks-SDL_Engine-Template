#pragma once
#include "Enemy.h"
#include "Animation.h"
#include "PlayerAnimationState.h"
#include "SpriteSheet.h"
#include"UIElement.h"
class CrazyBat : public Enemy {
public:
	CrazyBat(glm::vec2 position);
	~CrazyBat();

	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;


private:
	//animation variables
	void m_buildAnimations();
	void Animate();
	void Rebound();

	SpriteSheet* m_pSpriteSheet;
	PlayerAnimationState m_currentAnimationState;
	std::unordered_map<std::string, Animation> m_pAnimations;
	//UI
	std::vector<UIElement*> UI;
	int m_lifeRedCounter;

};