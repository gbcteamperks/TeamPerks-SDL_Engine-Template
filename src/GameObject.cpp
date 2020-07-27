#include "GameObject.h"
#include "Config.h"
#include <iostream>
#include "CollisionManager.h"
#include "MathManager.h"
#include "EventManager.h"

GameObject::GameObject():
	m_width(0), m_height(0), m_type(NONE)
{
	m_currentObject = this;
	m_pLife = 100;
	m_pDamage = 20;
	m_pNextDamageCounter = 0;
	m_timerColliding = 0;
}

GameObject::~GameObject()
= default;

Transform* GameObject::getTransform() 
{
	return &m_transform;
}

RigidBody* GameObject::getRigidBody() 
{
	return &m_rigidBody;
}

int GameObject::getWidth() const
{
	return m_width;
}

int GameObject::getHeight() const
{
	return m_height;
}

int GameObject::getPosX() const
{
	return m_posX;
}

int GameObject::getPosY() const
{
	return m_posY;
}

int GameObject::getAngle() const
{
	return m_angle;
}

GameObjectType GameObject::getType() const
{
	return m_type;
}

GameObjectType GameObject::getParentType() const
{
	return m_parent;
}

void GameObject::setWidth(const int new_width)
{
	m_width = new_width;
}

void GameObject::setHeight(const int new_height)
{
	m_height = new_height;
}

void GameObject::setPosX(int new_posX)
{
	m_posX = new_posX;
}

void GameObject::setPosY(int new_posY)
{
	m_posY = new_posY;
}

void GameObject::setAngle(int new_angle)
{
	m_angle = new_angle;
}

void GameObject::setType(const GameObjectType new_type)
{
	m_type = new_type;
}

void GameObject::setParentType(const GameObjectType new_type)
{
	m_parent = new_type;
}


//boundry restrict
void GameObject::m_BoundsRestrict()
{
	if (getTransform()->position.x + (getWidth() / 2) > Config::SCREEN_WIDTH)
	{
		getTransform()->position = glm::vec2(Config::SCREEN_WIDTH - getWidth() / 2, getTransform()->position.y);
		m_boundHit = RIGHTBOUNDARY;
	}

	if (getTransform()->position.x - (getWidth() / 2) < 0)
	{
		getTransform()->position = glm::vec2(0.0f + (getWidth() / 2), getTransform()->position.y);
		m_boundHit = LEFTBOUNDARY;
		//std::cout << "\n x axis below";
	}

	if (getTransform()->position.y + (getHeight() / 2) > Config::SCREEN_HEIGHT)
	{
		getTransform()->position = glm::vec2(getTransform()->position.x, Config::SCREEN_HEIGHT - getHeight() / 2);
		//std::cout << "\n y axis above";
		m_boundHit = BOTTOMBOUNDARY;
	}

	if (getTransform()->position.y - (getHeight() / 2) < 0)
	{
		getTransform()->position = glm::vec2(getTransform()->position.x, 0.00f + (getHeight() / 2));
		m_boundHit = TOPBOUNDARY;
		//std::cout << "\n y axis below";
	}
}

bool GameObject::m_CheckBounds()
{
	if (getTransform()->position.x  > Config::SCREEN_WIDTH + getWidth())
	{
		return true;
	}

	if (getTransform()->position.x  < -getWidth())
	{
		return true;
	}

	if (getTransform()->position.y  > Config::SCREEN_HEIGHT + getHeight())
	{
		return true;
	}

	if (getTransform()->position.y  < -getHeight())
	{
		return true;
	}
	return false;
}

bool GameObject::checkCollisionWithLevel(std::vector<GameObject*> listObstacles)
{
	m_pNextDamageCounter++;
	if (m_pNextDamageCounter > 60) 
	{
		m_pNextDamageCounter = 60;
	}
	bool collision = false;
	for (auto o : listObstacles)
	{
		if (o->getType() != SPIKES) {
			if (CollisionManager::AABBCheckUpdatingPosition(this, o))
			{
				collision = true;
			}
		}
		/*else if (o->getType() == SPIKES)
		{
			if (m_pNextDamageCounter == 60) 
			{
				if (CollisionManager::AABBCheck(this, o))
				{
					this->getLife() += -o->getDamage();
					m_pNextDamageCounter = 0;
				}
			}
			
		}*/
	}
	return collision;
}

bool GameObject::collidingWithLevel(std::vector<GameObject*> listObstacles)
{
	for (auto o : listObstacles)
	{
		if (CollisionManager::SImpleAABBCheck(this, o))
		{
			return true;
		}
	}
	return false;
}

void GameObject::fleeBehaviour(GameObject* obj)
{
	int distance = MAMA::Magnitude(MAMA::Distance(obj->getTransform()->position, this->getTransform()->position));
	if (distance < 300)
	{
		int angle = MAMA::AngleBetweenPoints(obj->getTransform()->position, this->getTransform()->position);
		m_angle = angle;
		angle = angle * 3.1416 / 180;
		this->getTransform()->position.x += this->getRigidBody()->velocity.x * cos(angle);
		this->getTransform()->position.y += this->getRigidBody()->velocity.y* sin(angle);
	}
}

void GameObject::Move(float velx, float vely)
{
	getTransform()->position.x += velx;
	getTransform()->position.y += vely;
	setPosX(getTransform()->position.x);
	setPosY(getTransform()->position.y);
}

void GameObject::cooldownColliding()
{
	if (getRigidBody()->isColliding)
	{
		m_timerColliding++;
		if (m_timerColliding >= 45) //0.75 seconds
		{
			getRigidBody()->isColliding = false;
			m_timerColliding = 0;
		}
	}
}


int& GameObject::getLife()
{
	return m_pLife;
}
int& GameObject::getDamage()
{
	return m_pDamage;
}