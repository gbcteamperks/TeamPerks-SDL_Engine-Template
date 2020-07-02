#pragma once
#include "DisplayObject.h"
#include "Animation.h"
#include "PlayerAnimationState.h"
#include "SpriteSheet.h"
#include "Ability.h"
#include <map>

class MotherSpider : public DisplayObject {
public:
	MotherSpider();
	~MotherSpider();

	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	// setters
	void setAnimationState(PlayerAnimationState new_state);

	//ability functions
	void addAbility(Ability*);
	void deleteAbility();
	void useCurrentAbility();
	void dropAbility();
	void changeAbility();

private:
	//animation variables
	void m_buildAnimations();
	void Animate();

	SpriteSheet* m_pSpriteSheet;
	PlayerAnimationState m_currentAnimationState;
	std::unordered_map<std::string, Animation> m_pAnimations;

	std::vector<Ability*> m_pListAbilities;
};