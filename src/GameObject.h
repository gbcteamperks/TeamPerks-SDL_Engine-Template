#pragma once
#ifndef __GAME_OBJECT__
#define __GAME_OBJECT__

#include "Transform.h"
#include "RigidBody.h"
//#include "CollisionManager.h"
#include <string>

// enums
#include "GameObjectType.h"

//--
// enum for which boundary the object collided
enum {
	NOCOLLISION = 0,
	RIGHTBOUNDARY,
	LEFTBOUNDARY,
	BELOWBOUNDARY,
	ABOVEBOUNDARY
};

class GameObject {
public:
	GameObject();
	virtual ~GameObject();

	// Draw the object
	virtual void draw() = 0;

	// Update the object
	virtual void update() = 0;

	// remove anything that needs to be deleted
	virtual void clean() = 0;

	// getters for common variables
	Transform* getTransform();

	// getters and setters for physics properties
	RigidBody* getRigidBody();
	
	// getters and setters for game object properties
	int getWidth() const;
	int getHeight() const;
	int getAngle() const;

	void setWidth(int new_width);
	void setHeight(int new_height);
	void setAngle(int new_angle);
	GameObjectType getType() const;
	void setType(GameObjectType new_type);
	void m_BoundsRestrict();
	bool m_CheckBounds();

	//--GameObject* getCurrentObject();
	
private:
	// transform component
	Transform m_transform;
	
	// rigid body component
	RigidBody m_rigidBody;

	// size variables
	int m_width;
	int m_height;
	GameObjectType m_type;
	int m_boundHit = 0;		//refer above enum
	//-- self reference

	int m_angle;
	GameObject* m_currentObject;
		 
};

#endif /* defined (__GAME_OBJECT__) */