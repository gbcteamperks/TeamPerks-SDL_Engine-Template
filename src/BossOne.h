
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



class BossOne : public DisplayObject
{
public:
	BossOne();
	~BossOne();

	// Life Cycle Methods
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	void bossAttack();

	// setters
	void setAnimationState(BossOneAnimationState new_state);
	void setAnimation(const Animation& animation);
	void runHereThere();
	void getBullet(Target*);

	//ability functions
	void addAbility(Ability*);
	void deleteAbility();
	void useCurrentAbility();
	void dropAbility();

private:
	void m_buildAnimations();
	SpriteSheet* m_pSpriteSheet;

	BossOneAnimationState m_currentAnimationState;
	std::unordered_map<std::string, Animation> m_pAnimations;
	bool m_bossFacingRight = true;
	bool m_bossWaitToFire = false;
	bool m_bulletNotVisible = false;
	bool m_fire = false;
	float m_durationOfLife = 5;
	float m_prevTime = 0.00f;
	int m_bulletXPosition = 0;
	float m_currentTime = 0.00f;

	Target* m_pBossBullet;
	//Fireball* m_pFireball;

	std::vector<Target*> m_pListOfTargets;

	//ability list
	std::vector<Ability*> m_pListAbilities;
	bool m_abilityReady = true;
};

#endif /* defined (__BOSS_ONE__) */