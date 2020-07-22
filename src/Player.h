#pragma once
#ifndef __PLAYER__
#define __PLAYER__

#include "DisplayObject.h"
#include "PlayerAnimationState.h"
#include "Animation.h"
#include "SpriteSheet.h"
#include <unordered_map>
#include "Ability.h"

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
	virtual std::vector<Ability*> getAbilitiesList() { return m_pListAbilities; }
	virtual int getAbilitieCounter() { return m_abilitieCounter; }
private:
	void m_buildAnimations();

	SpriteSheet* m_pSpriteSheet;
	//ability list
	std::vector<Ability*> m_pListAbilities;
	PlayerAnimationState m_currentAnimationState;
	std::unordered_map<std::string, Animation> m_pAnimations;
	bool m_playerFacingRight = true;
	int m_abilitieCounter;
};

#endif /* defined (__PLAYER__) */