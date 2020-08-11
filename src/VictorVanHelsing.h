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
	int getPlayerNumner() { return m_playerNumber; }
	bool right, down = false;
	static int numberOfPlayers;
	void handleEventsKeyboard();
	void handleEventsController();
	void slowEffect();
	bool isVictorSlow();

private:
	void m_buildAnimations();
	void animateBloodSplat();

	bool isMoving();
	void moveKeyboard();
	bool checkMouseInput();
	bool isSlow = false;
	
	SpriteSheet* m_pSpriteSheet;
	SpriteSheet* m_pSpriteSheetBlood;

	
	VictorAnimationState m_currentAnimationState;
	std::unordered_map<std::string, Animation> m_pAnimations;
	VictorVanHelsing* m_pObject;
	//ability list
	bool m_abilityReady = true;
	int m_playerNumber;

	//click mouse
	bool click1MousePressed, click2MousePressed;

	std::vector<UIElement*> UIList;

};

#endif /* defined (__VICTOR_VAN_HELSING__) */




