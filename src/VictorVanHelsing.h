#pragma once
#ifndef __VICTOR_VAN_HELSING__
#define __VICTOR_VAN_HELSING__

#include "DisplayObject.h"
#include "Animation.h"
#include "VictorAnimationState.h"
#include <unordered_map>
#include "SpriteSheet.h"
#include "Ability.h"
#include "UIElement.h"

class VictorVanHelsing : public DisplayObject
{
public:
	VictorVanHelsing(glm::vec2 position);
	~VictorVanHelsing();

	// Life Cycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	//bool isColliding(GameObject&) override;

	void setAnimationState(VictorAnimationState new_state);
	void setAnimation(const Animation& animation);

	//ability functions
	void addAbility(Ability *);
	void deleteAbility();
	void useCurrentAbility(int player);
	void changeAbility();
	//Test To Lfe Bar
	int& getLife() { return m_Life; }

	bool right, down = false;


private:
	void m_buildAnimations();
	SpriteSheet* m_pSpriteSheet;

	VictorAnimationState m_currentAnimationState;
	std::unordered_map<std::string, Animation> m_pAnimations;
	VictorVanHelsing* m_pObject;
	//ability list
	std::vector<Ability*> m_pListAbilities;
	bool m_abilityReady = true;

	int m_Life = 100;
	std::vector<UIElement*> UIList;

};

#endif /* defined (__VICTOR_VAN_HELSING__) */




