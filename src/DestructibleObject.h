#pragma once
#ifndef __DESTRUCTIBLE_OBJECT__
#define __DESTRUCTIBLE_OBJECT__

#include "DisplayObject.h"
#include "Animation.h"
#include "SpriteSheet.h"
#include "DestructibleObjectState.h"
#include <unordered_map>
class DestructibleObject : public DisplayObject 
{
public:

	DestructibleObject(glm::vec2 position, int numOfHits, std::string data, std::string spritepath, std::string name, int width, int height, int drawX, int drawY);
	~DestructibleObject();

	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	void setAnimationState(DestructibleObejectState new_state);
	void setAnimation(const Animation& animation);


private:
	void m_buildAnimation();
	void updateCollision();
	SpriteSheet* m_pSpriteSheet;
	DestructibleObejectState m_currentAnimation;
	int m_numOfHits;
	int tempTimer;

	std::unordered_map<std::string, Animation> m_pAnimations;

};

#endif /* defined (__DESTRUCTIBLE_OBJECT__) */