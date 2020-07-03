#pragma once
#include "Enemy.h"

class EnemyWizard : public Enemy {
public:
	EnemyWizard();
	~EnemyWizard();

	// Life Cycle Methods
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	void bossAttack();

	// setters
	void setAnimationState(BossOneAnimationState new_state);

	//animation
	void setAnimation(const Animation& animation);
	void m_buildAnimations() override;
	void runHereThere();

private:

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
};
