
#pragma once
#ifndef __BOSS_ONE__
#define __BOSS_ONE__

#include "DisplayObject.h"
#include "BossOneAnimationState.h"
#include "Animation.h"
#include "SpriteSheet.h"
#include <unordered_map>

class BossOne : public DisplayObject
{
public:
	BossOne();
	~BossOne();

	// Life Cycle Methods
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	// setters
	void setAnimationState(BossOneAnimationState new_state);
	void setAnimation(const Animation& animation);
	void runHereThere();

private:
	void m_buildAnimations();

	SpriteSheet* m_pSpriteSheet;

	BossOneAnimationState m_currentAnimationState;
	std::unordered_map<std::string, Animation> m_pAnimations;
	bool m_bossFacingRight = true;
};

#endif /* defined (__BOSS_ONE__) */