#pragma once
#ifndef __GAME_OBJECT__
#define __GAME_OBJECT__

#include "Transform.h"
#include "RigidBody.h"
//#include "CollisionManager.h"
#include <string>
#include <vector>
#include "SDL.h"
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
enum State {
	IDLE,
	RUNNING,
	MELEEATK,
	RANGEATK,
	RANGEATK2,
	DIE,
	NUMOFSTATES
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
	void setState(State state);
	void setSpeed(float speed);
	float getSpeed();
	void setFlip(SDL_RendererFlip flip);
	void m_BoundsRestrict();
	bool m_CheckBounds();
	bool checkCollisionWithLevel(std::vector<GameObject*> listObstacles);
	bool collidingWithLevel(std::vector<GameObject*> listObstacles);
	void fleeBehaviour(GameObject* obj);
	void Move(float velx, float vely);

	void setColX(int colX);
	void setColY(int colY);
	int getColX() const;
	int getColY() const;
	

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

	float m_speed;
	int m_angle;
	GameObject* m_currentObject;
	int m_pLife;
	int m_pDamage;
	int m_pNextDamageCounter;
	int m_colX;
	int m_colY;
	//debug

	State m_currentState;
	SDL_RendererFlip m_Flip;
};

#endif /* defined (__GAME_OBJECT__) */