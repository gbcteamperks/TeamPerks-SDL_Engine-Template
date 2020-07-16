#include "PlayScene.h"
#include "MotherSpider.h"
#include "EnemyWizard.h"
#include "VictorVanHelsing.h"
#include "Config.h"
#include "LevelManager.h"
#include <fstream>
#include <string>
#include "RatKing.h"
#include "SpawnEnemiesManager.h"
#include "SkeletonEnemy.h"

std::vector<VictorVanHelsing*> PlayScene::listPlayers;

PlayScene::PlayScene()
{
	PlayScene::start();
}

PlayScene::PlayScene(int level)
{
	this->levelNumber = level;
	PlayScene::start();
}

PlayScene::~PlayScene()
= default;

void PlayScene::draw()
{
	LVLMAN::Instance()->render();
	drawDisplayList();
}
void PlayScene::update()
{
	if (enemyKillCount > 5)
	{
		successful = true;
	}

	if(!successful)
	{
		updateDisplayList();
		SpawnEnemiesManager::level1();
		//delete projectiles
		if (getDisplayList().size() > 0) {
			for (auto it = getDisplayList().begin(); it != getDisplayList().end(); it++) {
				if (((*it)->getType() == ENEMYABILITY || (*it)->getType() == PLAYERABILITY) && (*it)->m_CheckBounds())
				{
					(*it)->clean();
					delete (*it);
					(*it) = nullptr;
				}
				else if ((*it)->getParentType() == ABILITY)
				{
					if (dynamic_cast<Ability*>(*it)->getAbilityDone())
					{
						(*it)->clean();
						delete (*it);
						(*it) = nullptr;
					}
				}

			}
		}
		getDisplayList().erase(std::remove(getDisplayList().begin(), getDisplayList().end(), nullptr), getDisplayList().end());

	}
	else
	{
		//update to the transition scene
		std::cout << "Update transiton" << std::endl;
		invokeTransition();
	}
		
	
}

void PlayScene::clean()
{
	VictorVanHelsing::numberOfPlayers = 0;
	LVLMAN::Instance()->clean();
	SoundManager::Instance().stopMusic();

	removeAllChildren();
}

void PlayScene::handleEvents()
{
	if(!successful)
	{
		EventManager::Instance().update();

		// handle player movement with GameController
		if (SDL_NumJoysticks() > 0)
		{
			if (EventManager::Instance().getGameController(0) != nullptr)
			{
				if (EventManager::Instance().getGameController(0)->START_BUTTON)
				{
					if (listPlayers.size() < 2)
					{
						listPlayers.push_back(new VictorVanHelsing(glm::vec2(500.0f, 400.0f)));
						addChild(listPlayers[1]);
					}
				}
				if (listPlayers.size() > 1)
				{
					const auto deadZone = 10000;
					if (EventManager::Instance().getGameController(0)->LEFT_STICK_X[1] > deadZone)
					{
						listPlayers[1]->getTransform()->position.x += listPlayers[1]->getRigidBody()->velocity.x;
						listPlayers[1]->setAnimationState(VICTOR_WALK_RIGHT);
					}
					if (EventManager::Instance().getGameController(0)->LEFT_STICK_X[1] < -deadZone)
					{
						listPlayers[1]->getTransform()->position.x -= listPlayers[1]->getRigidBody()->velocity.x;
						listPlayers[1]->setAnimationState(VICTOR_WALK_LEFT);
					}
					if (EventManager::Instance().getGameController(0)->LEFT_STICK_Y[1] < -deadZone)
					{
						listPlayers[1]->getTransform()->position.y -= listPlayers[1]->getRigidBody()->velocity.y;
						listPlayers[1]->setAnimationState(VICTOR_WALK_UP);

					}
					if (EventManager::Instance().getGameController(0)->LEFT_STICK_Y[1] > deadZone)
					{
						listPlayers[1]->getTransform()->position.y += listPlayers[1]->getRigidBody()->velocity.y;
						listPlayers[1]->setAnimationState(VICTOR_WALK_DOWN);
					}
					//Change Ability
					if (EventManager::Instance().getGameController(0)->Arealeased())
					{
						listPlayers[1]->changeAbility();
					}
					//Use Current Ability
					if (EventManager::Instance().getGameController(0)->Brealeased())
					{
						listPlayers[1]->useCurrentAbility(2);
					}
				}
			}
		}

		//KeyBoard


		if (EventManager::Instance().isKeyDown(SDL_SCANCODE_A)/* && LVLMAN::Instance()->checkCollision(listPlayers[0], -playerSpeed, 0)*/)
		{
			listPlayers[0]->setAnimationState(VICTOR_WALK_LEFT);
			listPlayers[0]->getTransform()->position.x -= listPlayers[0]->getRigidBody()->velocity.x;
		}
		else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_D) /*&& LVLMAN::Instance()->checkCollision(listPlayers[0], playerSpeed, 0)*/)
		{
			listPlayers[0]->setAnimationState(VICTOR_WALK_RIGHT);
			listPlayers[0]->getTransform()->position.x += listPlayers[0]->getRigidBody()->velocity.x;
		}
		if (EventManager::Instance().isKeyDown(SDL_SCANCODE_W) /*&& LVLMAN::Instance()->checkCollision(listPlayers[0], 0, -playerSpeed)*/)
		{
			listPlayers[0]->setAnimationState(VICTOR_WALK_UP);
			listPlayers[0]->getTransform()->position.y -= listPlayers[0]->getRigidBody()->velocity.y;
		}
		else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_S) /*&& LVLMAN::Instance()->checkCollision(listPlayers[0], 0, playerSpeed)*/)
		{
			listPlayers[0]->setAnimationState(VICTOR_WALK_DOWN);
			listPlayers[0]->getTransform()->position.y += listPlayers[0]->getRigidBody()->velocity.y;
		}



		if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
		{
			TheGame::Instance()->quit();
		}

		if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
		{
			TheGame::Instance()->changeSceneState(START_SCENE);
		}
		//Change Ability
		if (EventManager::Instance().KeyReleased(SDL_SCANCODE_E))
		{
			listPlayers[0]->changeAbility();
		}
		//Use Current Ability
		if (EventManager::Instance().KeyReleased(SDL_SCANCODE_Q))
		{
			listPlayers[0]->useCurrentAbility(1);

		}
		if (EventManager::Instance().isKeyDown(SDL_SCANCODE_2))
		{
			TheGame::Instance()->changeSceneState(END_SCENE);
		}

		if (EventManager::Instance().isKeyDown(SDL_SCANCODE_T))
		{

			LVLMAN::Instance()->printNodes();

			/*std::cout << "x: " << LevelManager::Instance()->getLevel()[5][10]->m_node->x << " y:" << LevelManager::Instance()->getLevel()[5][10]->m_node->y << "\n";
			listPlayers[0]->getTransform()->position.x = LVLMAN::Instance()->getLevel()[5][10]->m_node->x;
			listPlayers[0]->getTransform()->position.y = LVLMAN::Instance()->getLevel()[5][10]->m_node->y;*/
		}



		collisions();
	}
	else
	{
		//invoking transition.
	}
	
}

void PlayScene::start()
{
	LVLMAN::Instance()->loadTiles("../Assets/sprites/Level1_Tiles.png", "tiles", "../Assets/sprites/TileData.txt");
	
	
	
	switch(levelNumber)
	{
	case 1:
		levelNumberConcatenate = "../Assets/data/Level" + std::to_string((levelNumber)) + ".txt";
		break;

	case 2:
		levelNumberConcatenate = "../Assets/data/Level" + std::to_string((levelNumber)) + ".txt";
		break;

	case 3:
		levelNumberConcatenate = "../Assets/data/Level" + std::to_string((levelNumber)) + ".txt";
		break;

	default:
		break;
	}
	LVLMAN::Instance()->loadLevel(levelNumberConcatenate);
	std::cout << "start";

	//Boss
	//addChild(new EnemyWizard());

	//Victor
	listPlayers.push_back(new VictorVanHelsing(glm::vec2(390.0f, 400.0f)));
	addChild(listPlayers[0]);

	//BigSpider
	//addChild(new MotherSpider());


	//KingRat
	//addChild(new RatKing());

	//Music
	SoundManager::Instance().load("../Assets/audio/PlaySceneMusic.mp3", "PlaySceneMusic", SOUND_MUSIC);
	SoundManager::Instance().playMusic("PlaySceneMusic");
	//Sound fx
	SoundManager::Instance().load("../Assets/audio/sword-1b.wav", "Sword", SOUND_SFX);
	SoundManager::Instance().load("../Assets/audio/Rat.mp3", "Rat", SOUND_SFX);
	SoundManager::Instance().load("../Assets/audio/Fireball.wav", "FireBall", SOUND_SFX);
	SoundManager::Instance().load("../Assets/audio/electricshock.wav", "Orb", SOUND_SFX);
	SoundManager::Instance().load("../Assets/audio/Grunting-sound.mp3", "Grunt", SOUND_SFX);
}

void PlayScene::collisions()
{

	bool changeState = false;
	
	for (int i = 0; i < getDisplayList().size(); i++) {
		for (int k = 0; k < getDisplayList().size();k++) 
		{
			if (getDisplayList()[i] != nullptr && getDisplayList()[k] != nullptr) {
				//PLAYER ABILITIES AND ENEMIES
				if (getDisplayList()[i]->getType() == PLAYERABILITY && getDisplayList()[k]->getType() == ENEMY)
				{
					// **** Its the same code as the ability and boss check ****
					if (CollisionManager::AABBCheckBoss(getDisplayList()[i], getDisplayList()[k])) {
						if ((getDisplayList()[k])->getLife() > 0) {

							getDisplayList()[k]->getLife() -= getDisplayList()[i]->getDamage();
						}
					}
					if ((getDisplayList()[k])->getLife() <= 0){
						getDisplayList()[k]->clean();
						delete getDisplayList()[k];
						getDisplayList()[k] = nullptr;
						enemyKillCount++;
					}
				
				}
				//PlAYER ABILITY AND BOSS
				else if (getDisplayList()[i]->getType() == PLAYERABILITY && getDisplayList()[k]->getType() == BOSS)
				{
					if (CollisionManager::AABBCheckBoss(getDisplayList()[i], getDisplayList()[k])) {
						if ((getDisplayList()[k])->getLife() > 0) {

							getDisplayList()[k]->getLife() -= getDisplayList()[i]->getDamage();
						}
						if ((getDisplayList()[k])->getLife() <= 0) {
							getDisplayList()[k]->clean();
							delete getDisplayList()[k];
							getDisplayList()[k] = nullptr;
							enemyKillCount++;
						}
					}

				}

				//VICTOR AND PICKEABLE OBJECTS
				else if (getDisplayList()[i]->getType() == VICTOR && getDisplayList()[k]->getType() == PICKABLE)
				{
					if (CollisionManager::AABBCheck(getDisplayList()[i], getDisplayList()[k])) {
						dynamic_cast<VictorVanHelsing*>(getDisplayList()[i])->addAbility(dynamic_cast<Ability*>(getDisplayList()[k])->getAbility());
						getDisplayList()[k]->clean();
						delete getDisplayList()[k];
						getDisplayList()[k] = nullptr;
					}
				}
				//VICTOR AND ENEMYABILITIES
				else if (getDisplayList()[i]->getType() == VICTOR && getDisplayList()[k]->getType() == ENEMYABILITY)
				{
					if (CollisionManager::AABBCheck(getDisplayList()[i], getDisplayList()[k])) {
						
						getDisplayList()[i]->getLife() -= 5;
						SoundManager::Instance().playSound("Grunt");
						if (getDisplayList()[i]->getLife() == 0)
						{
							changeState = true;
						}
					}
				}
				//VICTOR WITH DOOR
				else if (getDisplayList()[i]->getType() == VICTOR && getDisplayList()[k]->getType() == DOOR)
				{
					if (CollisionManager::AABBCheck(getDisplayList()[i], getDisplayList()[k])) {
						
						std::cout << " x: " << getDisplayList()[k]->getTransform()->position.x << " y: " << getDisplayList()[k]->getTransform()->position.y << "\n";
						std::cout << "Hit Door\n";
					}
				}
				
			}
			
		}
	}

	getDisplayList().erase(std::remove(getDisplayList().begin(), getDisplayList().end(), nullptr),getDisplayList().end());
	if (changeState) {
		TheGame::Instance()->changeSceneState(END_SCENE);
	}

}

bool PlayScene::tileCollision(GameObject* obj)
{
	return false;
}

int PlayScene::getLevelNumber()
{
	return levelNumber;
}

void PlayScene::invokeTransition()
{
	levelNumber++;
	//std::cout << "in invoke transition.." << std::endl;
	TheGame::Instance()->changeSceneState(TRANSITION_SCENE);
}


