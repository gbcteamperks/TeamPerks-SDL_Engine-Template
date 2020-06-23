#include "GameObject.h"
#include "Config.h"
#include <iostream>
#include "CollisionManager.h"

GameObject::GameObject():
	m_width(0), m_height(0), m_type(NONE)
{
	m_currentObject = this;
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

int GameObject::getAngle() const
{
	return m_angle;
}

GameObjectType GameObject::getType() const
{
	return m_type;
}

void GameObject::setWidth(const int new_width)
{
	m_width = new_width;
}

void GameObject::setHeight(const int new_height)
{
	m_height = new_height;
}

void GameObject::setAngle(int new_angle)
{
	m_angle = new_angle;
}

void GameObject::setType(const GameObjectType new_type)
{
	m_type = new_type;
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
		m_boundHit = BELOWBOUNDARY;
	}

	if (getTransform()->position.y - (getHeight() / 2) < 0)
	{
		getTransform()->position = glm::vec2(getTransform()->position.x, 0.00f + (getHeight() / 2));
		m_boundHit = ABOVEBOUNDARY;
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
