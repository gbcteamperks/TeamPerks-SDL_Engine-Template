
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
	void dropAbility();
	void changeAbility();

protected:
	//ability list
	std::vector<Ability*> m_pListAbilities;
	bool m_abilityReady = true;
	
};

#endif /* defined (__BOSS_ONE__) */