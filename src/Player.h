#pragma once
#ifndef __PLAYER__
#define __PLAYER__

#include "DisplayObject.h"
#include "PlayerAnimationState.h"
#include "Animation.h"
#include "SpriteSheet.h"
#include <unordered_map>

class Player : public DisplayObject
{
public:
	Player();
	~Player();

	// Life Cycle Methods
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	// setters
	void setAnimationState(PlayerAnimationState new_state);
	void setAnimation(const Animation& animation);
	void runHereThere();

private:
	void m_buildAnimations();

	SpriteSheet* m_pSpriteSheet;

	PlayerAnimationState m_currentAnimationState;
	std::unordered_map<std::string, Animation> m_pAnimations;
	bool m_playerFacingRight = true;
};

#endif /* defined (__PLAYER__) */