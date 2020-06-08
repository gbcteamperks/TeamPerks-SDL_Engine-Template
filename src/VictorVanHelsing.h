#pragma once
#ifndef __VICTOR_VAN_HELSING__
#define __VICTOR_VAN_HELSING__

#include "DisplayObject.h"
#include "Animation.h"
#include "VictorAnimationState.h"
#include <unordered_map>
#include "SpriteSheet.h"

class VictorVanHelsing : public DisplayObject
{
public:
	VictorVanHelsing();
	~VictorVanHelsing();

	// Life Cycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	//bool isColliding(GameObject&) override;

	void setAnimationState(VictorAnimationState new_state);
	void setAnimation(const Animation& animation);

private:
	void m_buildAnimations();
	SpriteSheet* m_pSpriteSheet;

	VictorAnimationState m_currentAnimationState;
	std::unordered_map<std::string, Animation> m_pAnimations;
	VictorVanHelsing* m_pObject;
};

#endif /* defined (__VICTOR_VAN_HELSING__) */




