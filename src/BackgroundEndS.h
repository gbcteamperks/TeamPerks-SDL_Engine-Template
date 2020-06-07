#pragma once
#include "DisplayObject.h"
#include "Animation.h"
#include <unordered_map>
#include "SpriteSheet.h"

class BackgroundEndS : public DisplayObject
{
public:
	BackgroundEndS();
	~BackgroundEndS();

	// Life Cycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	//bool isColliding(GameObject&) override;

	void setAnimation(const Animation& animation);

private:
	void m_buildAnimations();
	SpriteSheet* m_pSpriteSheet;

	std::unordered_map<std::string, Animation> m_pAnimations;
};
