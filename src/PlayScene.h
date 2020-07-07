#pragma once
#ifndef __LEVEL1_SCENE__
#define __LEVEL1_SCENE__

#include "Scene.h"

#include "PlaneSprite.h"
#include "Player.h"
#include "Target.h"
#include "Button.h"
#include "StaticSprite.h"
#include "VictorVanHelsing.h"
#include "GameObjectType.h"
#include "Game.h"
#include "EventManager.h"
#include "Enemy.h"
#include "Fireball.h"
#include "Sword.h"
#include "Tile.h"
#include <array>
#include <map>
class PlayScene : public Scene
{
public:
	PlayScene();
	~PlayScene();

	// Scene LifeCycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;

	void collisions();

	bool m_bgScrollX = false, m_bgScrollY = false;
	float playerSpeed = 2.0f;


	
private:
	glm::vec2 m_mousePosition;

	StaticSprite* m_pBkg{};
	std::vector<VictorVanHelsing*> listPlayers;
	int m_currentTime = 0;
	int m_prevTime = 0;

	

};

#endif /* defined (__LEVEL1_SCENE__) */