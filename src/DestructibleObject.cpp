#include "DestructibleObject.h"
#include "TextureManager.h"
#include "CollisionManager.h"
#include "EventManager.h"
DestructibleObject::DestructibleObject(glm::vec2 pos, int numOfHits, std::string data, std::string spritepath, std::string name,int width, int height, int drawX, int drawY)
{
	TheTextureManager::Instance()->loadSpriteSheet(
	data,spritepath,name);

	m_pSpriteSheet = TheTextureManager::Instance()->getSpriteSheet("barrel");
	setWidth(width);
	setHeight(height);
	m_numOfHits = numOfHits;
	m_pLife = m_numOfHits;
	getTransform()->position = pos;
	getRigidBody()->isColliding = false;
	setType(DESTRUCTIBLE);
	m_buildAnimation();
	setColX(drawX);
	setColY(drawY);
}

DestructibleObject::~DestructibleObject() = default;

void DestructibleObject::draw()
{
	if (getLife() == 3) 
	{
		TheTextureManager::Instance()->drawFrame("barrel", getTransform()->position.x, getTransform()->position.y,
			getWidth(), getHeight(), 0, 0, getColX(),getColY(), 0, 255, false, SDL_FLIP_NONE);
	}	
	else if (getLife() == 2)
	{
		TheTextureManager::Instance()->drawFrame("barrel", getTransform()->position.x, getTransform()->position.y,
			getWidth(),getHeight(), 0, 1, getColX(), getColY(), 0, 255, false, SDL_FLIP_NONE);
	}	
	else if (getLife() == 1)
	{
		TheTextureManager::Instance()->drawFrame("barrel", getTransform()->position.x, getTransform()->position.y,
			getWidth(), getHeight(), 0, 2, getColX(), getColY(), 0, 255, false, SDL_FLIP_NONE);
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
