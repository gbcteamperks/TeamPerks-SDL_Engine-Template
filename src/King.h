#pragma once
#include "Enemy.h"
#include "UIElement.h"
#include "DecisionTree.h"
enum class KingState {
	IDLE,
	ATTACK1,
	ATTACK1SWING,
	ATTACK1END,
	ATTACK2,
	ATTACK2EXPLOSION,
	ATTACK2END,
	TELEPORT,
	TELEPORTBACK,
	WALK,
	NUMBERSTATES
	
};
class King : public Enemy {
public:
	King(glm::vec2 position);
	~King();

	// Life Cycle Methods
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	void bossAttack();
	void setKingState(KingState state);
	KingState getKingState() { return m_currentKingState; }

	void m_buildAnimations() override;

private:
	void Seeking();
	void updateCollisionBox(float w, float h, float offSetX, float offSetY);
	void BuildTree();
	DecisionTree* m_ActionTree;

	KingState m_currentKingState;
	SpriteSheet* m_pSpriteSheet;
	std::unordered_map<std::string, Animation> m_pAnimations;

	//UI
	int m_lifeRedCounter;
	std::vector<UIElement*> UI;

	float m_distanceToPlayer;
	float m_maxLife;
	float m_timeIDLE, m_timeWALKING, m_velocityIDLE, m_velocityAnimation;
};
