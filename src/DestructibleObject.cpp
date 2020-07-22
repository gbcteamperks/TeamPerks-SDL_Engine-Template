#include "DestructibleObject.h"
#include "TextureManager.h"
#include "CollisionManager.h"
#include "EventManager.h"
DestructibleObject::DestructibleObject(glm::vec2 pos, int numOfHits)
{
	TheTextureManager::Instance()->loadSpriteSheet(
		"../Assets/sprites/barrel.txt",
		"../Assets/sprites/barrel.png",
		"barrel"
	);

	m_pSpriteSheet = TheTextureManager::Instance()->getSpriteSheet("barrel");
	setWidth(48);
	setHeight(58);
	m_numOfHits = 4;
	getTransform()->position = pos;
	getRigidBody()->isColliding = false;
	setType(DESTRUCTIBLE);
	m_buildAnimation();

}

DestructibleObject::~DestructibleObject() = default;

void DestructibleObject::draw()
{
	if (m_numOfHits = 4) 
	{
		TheTextureManager::Instance()->drawFrame("barrel", getTransform()->position.x, getTransform()->position.y,
			this->getWidth(), this->getHeight(), 0, 0,39,49, 0, 255, false, SDL_FLIP_NONE);
	}
}

void DestructibleObject::update()
{
	setPosX(getTransform()->position.x);
	setPosY(getTransform()->position.y);
}

void DestructibleObject::clean()
{
}

void DestructibleObject::setAnimationState(DestructibleObejectState new_state)
{
}

void DestructibleObject::setAnimation(const Animation& animation)
{
}

void DestructibleObject::m_buildAnimation()
{
	Animation destruction = Animation();

	destruction.name = "frame";
	destruction.frames.push_back(m_pSpriteSheet->getFrame("frame-0"));
	destruction.frames.push_back(m_pSpriteSheet->getFrame("frame-1"));
	destruction.frames.push_back(m_pSpriteSheet->getFrame("frame-2"));
	destruction.frames.push_back(m_pSpriteSheet->getFrame("frame-3"));

	m_pAnimations["frame"] = destruction;
}
