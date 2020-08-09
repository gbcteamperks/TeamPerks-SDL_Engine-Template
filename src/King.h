#pragma once
#include "Enemy.h"
#include "UIElement.h"
class King : public Enemy {
public:
	King(glm::vec2 position);
	~King();

	// Life Cycle Methods
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	void bossAttack();

	bool SeekingNode(int x, int y);
	void m_buildAnimations() override;

private:

	SpriteSheet* m_pSpriteSheet;

	std::unordered_map<std::string, Animation> m_pAnimations;

	//UI
	int m_lifeRedCounter;
	std::vector<UIElement*> UI;
};
