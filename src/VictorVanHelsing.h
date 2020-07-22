#pragma once
#ifndef __VICTOR_VAN_HELSING__
#define __VICTOR_VAN_HELSING__

#include "Player.h"
#include "Animation.h"
#include "VictorAnimationState.h"
#include <unordered_map>
#include "SpriteSheet.h"
#include "UIElement.h"

class VictorVanHelsing : public Player
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
	void countAbilitie();
	int getPlayerNumner() { return m_playerNumber; }
	bool right, down = false;
	static int numberOfPlayers;
	int getAbilitieCounter() { return m_abilitieCounter; }
	std::vector<Ability*> getAbilitiesList() { return m_pListAbilities; }

private:
	void m_buildAnimations();
	SpriteSheet* m_pSpriteSheet;

	VictorAnimationState m_currentAnimationState;
	std::unordered_map<std::string, Animation> m_pAnimations;
	VictorVanHelsing* m_pObject;
	//ability list
	std::vector<Ability*> m_pListAbilities;
	int m_currentAbility;//to swap Abilities
	bool m_abilityReady = true;
	int m_playerNumber;
	std::vector<UIElement*> UIList;
	int m_abilitieCounter;//For the UI lights
};

#endif /* defined (__VICTOR_VAN_HELSING__) */




