#pragma once
#ifndef __GAME_OBJECT__
#define __GAME_OBJECT__

#include "Transform.h"
#include "RigidBody.h"
//#include "CollisionManager.h"
#include <string>
#include <vector>

// enums
#include "GameObjectType.h"

//--
// enum for which boundary the object collided
enum BoundaryCollided{
	NOCOLLISION = 0,
	RIGHTBOUNDARY,
	LEFTBOUNDARY,
	TOPBOUNDARY,
	BOTTOMBOUNDARY
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
	int getPosX() const;
	int getPosY() const;
	int getAngle() const;

	void setWidth(int new_width);
	void setHeight(int new_height);
	void setPosX(int new_posX);
	void setPosY(int new_posY);
	void setAngle(int new_angle);
	GameObjectType getType() const;
	GameObjectType getParentType() const;
	void setType(GameObjectType new_type);
	void setParentType(GameObjectType new_type);
	void m_BoundsRestrict();
	bool m_CheckBounds();
	bool checkCollisionWithLevel(std::vector<GameObject*> listObstacles);
	void fleeBehaviour(GameObject* obj);

	//--GameObject* getCurrentObject();
	BoundaryCollided m_boundHit = NOCOLLISION;		//refer above enum
	virtual int& getLife();
	virtual int& getDamage();
protected:
	// transform component
	Transform m_transform;
	
	// rigid body component
	RigidBody m_rigidBody;

	// size variables for collision
	int m_width;
	int m_height;
	int m_posX;
	int m_posY;
	GameObjectType m_type;
	GameObjectType m_parent;
	
	//-- self reference

	int m_angle;
	GameObject* m_currentObject;
	int m_pLife;
	int m_pDamage;

	//debug

};

#endif /* defined (__GAME_OBJECT__) */