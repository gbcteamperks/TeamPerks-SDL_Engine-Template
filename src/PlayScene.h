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
#include "DestructibleObject.h"
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
	bool tileCollision(GameObject* obj);
	bool m_bgScrollX = false, m_bgScrollY = false;
	std::vector<DisplayObject*>& getObstacles() { return obstacle_List; }

	static std::vector<VictorVanHelsing*> listPlayers;
	int getLevelNumber();
	void invokeTransition();
	//bool getDebug() { return m_debugView };
private:
	glm::vec2 m_mousePosition;
	std::vector<DisplayObject*> obstacle_List;
	StaticSprite* m_pBkg{};
	int m_currentTime = 0;
	int m_prevTime = 0;
	bool m_debugView = false;

	int enemyKillCount = 0;
	//transition to next scene
	bool successful = false;
	bool summonBoss = false;
	bool presuccessful = false;
	static int levelNumber;
	std::string levelNumberConcatenate;
	std::string tileNumberConcatenate;

	

	//pause
	bool gamePaused;



	

};

#endif /* defined (__LEVEL1_SCENE__) */