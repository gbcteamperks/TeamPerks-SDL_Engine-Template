
#pragma once
#ifndef __BOSS_ONE__
#define __BOSS_ONE__

#include "DisplayObject.h"
#include "BossOneAnimationState.h"
#include "Animation.h"
#include "SpriteSheet.h"
#include <unordered_map>
#include "Target.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "CollisionManager.h"
#include "Ability.h"



class Enemy : public DisplayObject
{
public:
	Enemy();
	~Enemy();

	// Life Cycle Methods
	virtual void draw() =0 ;
	virtual void update() = 0;
	virtual void clean() = 0;


	//animation
	virtual void m_buildAnimations() = 0;

	//ability functions
	void addAbility(Ability*);
	void deleteAbility();
	virtual void useCurrentAbility();
	virtual std::string getName() { return m_EnemyName; }
	void dropAbility();
	void changeAbility();
	//getters

protected:

	void buildBloodAnimation();
	void animateBloodSplat();
	std::unordered_map<std::string, Animation> m_pAnimations;

	//ability list
	std::vector<Ability*> m_pListAbilities;
	bool m_abilityReady = true;
	std::string m_EnemyName;
	SpriteSheet* m_pSpriteSheetBlood;

	//Enemy Life
};

#endif /* defined (__BOSS_ONE__) */