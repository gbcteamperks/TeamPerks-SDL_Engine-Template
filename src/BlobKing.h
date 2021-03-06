#pragma once
#include "Enemy.h"
#include "Animation.h"
#include "PlayerAnimationState.h"
#include "SpriteSheet.h"
#include"UIElement.h"

class BlobKing : public Enemy
{
public:
	
	BlobKing(glm::vec2 position);
	~BlobKing();

	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	void useCurrentAbility();
	
private:
	//animation variables
	void m_buildAnimations();
	void Animate();

	int moveTimer = 0;

	int minX = 355;
	int maxX = 675;
	bool leftRightToggle = false;
	int waitTime;
	bool waiting = false;
	
	glm::vec2 playerPos;
	std::vector<UIElement*> UI;
	int m_lifeRedCounter;


	SpriteSheet* m_pSpriteSheet;
	PlayerAnimationState m_currentAnimationState;
	std::unordered_map<std::string, Animation> m_pAnimations;
};