#include "SpawnEnemiesManager.h"

#include "BlobKing.h"
#include "LevelManager.h"
#include "MathManager.h"
#include "CollisionManager.h"
#include "MotherSpider.h"
#include "EnemyWizard.h"
#include "RatKing.h"
#include "SkeletonEnemy.h"
#include "CrazyBat.h"
#include "Config.h"
#include "Game.h"
#include "King.h"

int SpawnEnemiesManager::randomNum = rand() % 120 + 300;
bool SpawnEnemiesManager::bossSummoned = false;

void SpawnEnemiesManager::level1()
{
	bossSummoned = false;
	static int timer = 0;
	int countEnemies = Game::Instance()->getCurrentScene()->getEnemies().size();
	auto level = LVLMAN::Instance()->getLevel();
	if (timer > randomNum && countEnemies < 4)
	{
		int randomCol = rand() % (Config::COL_NUM - 2) + 2;
		int randomRow = rand() % (Config::ROW_NUM- 2) + 2;
		for (int col = randomCol; col < Config::COL_NUM - 2; col++)
		{
			for (int row = randomRow; row < Config::ROW_NUM - 2; row++)
			{
				if (level[row][col] != nullptr)
				{
					if (!level[row][col]->isObstacle()) 
					{
						int randomEnemy = rand() % 100;
						if (randomEnemy <= 30)
						{
							MotherSpider* spider = new MotherSpider(level[row][col]->getTransform()->position);
							if (!spider->checkCollisionWithLevel(LVLMAN::Instance()->getObstacles()))
							{
								Game::Instance()->getCurrentScene()->addChild(spider);
							}
							else
							{
								delete spider;
								spider = nullptr;
								continue;
							}
						}
						else if(randomEnemy >= 31 && randomEnemy <= 100)
						{
							CrazyBat* bat = new CrazyBat(level[row][col]->getTransform()->position);
							if (!bat->checkCollisionWithLevel(LVLMAN::Instance()->getObstacles()))
							{
								Game::Instance()->getCurrentScene()->addChild(bat);
							}
							else
							{
								delete bat;
								bat = nullptr;
								continue;
							}
						}
					
						timer = 0;
						randomNum = rand() % 120 + 300;
						col = Config::COL_NUM;
						row = Config::ROW_NUM;
					}
				}
			}
		}
	}
	timer++;
}

void SpawnEnemiesManager::level2()
{
	bossSummoned = false;
	static int timer = 0;
	int countEnemies = Game::Instance()->getCurrentScene()->getEnemies().size();
	auto level = LVLMAN::Instance()->getLevel();
	if (timer > randomNum && countEnemies < 4)
	{
		int randomCol = rand() % (Config::COL_NUM - 2) + 2;
		int randomRow = rand() % (Config::ROW_NUM - 2) + 2;
		for (int col = randomCol; col < Config::COL_NUM - 2; col++)
		{
			for (int row = randomRow; row < Config::ROW_NUM - 2; row++)
			{
				if (level[row][col] != nullptr)
				{
					if (!level[row][col]->isObstacle())
					{
						
						
						Game::Instance()->getCurrentScene()->addChild(new EnemyWizard(level[row][col]->getTransform()->position));
						
						//else if (randomEnemy > 60 && randomEnemy <= 100)
						//{
						//	//possible bug!!!!
						//	//Game::Instance()->getCurrentScene()->addChild(new SkeletonEnemy(level[row][col]->getTransform()->position));
						//	CrazyBat* bat = new CrazyBat(level[row][col]->getTransform()->position);
						//	if (!bat->checkCollisionWithLevel(LVLMAN::Instance()->getObstacles()))
						//	{
						//		Game::Instance()->getCurrentScene()->addChild(bat);
						//	}
						//	else
						//	{
						//		delete bat;
						//		bat = nullptr;
						//		continue;
						//	}
						//}
						timer = 0;
						randomNum = rand() % 120 + 300;
						col = Config::COL_NUM;
						row = Config::ROW_NUM;
					}
				}
			}
		}
	}
	timer++;
}

void SpawnEnemiesManager::level1Boss()
{
	if(bossSummoned == false)
	{
		auto level = LVLMAN::Instance()->getLevel();
		Game::Instance()->getCurrentScene()->removeChildByType(ENEMY);
		Game::Instance()->getCurrentScene()->removeChildByType(ENEMYABILITY);
		Game::Instance()->getCurrentScene()->addChild(new RatKing(level[5][Config::COL_NUM / 2]->getTransform()->position));
		bossSummoned = true;
	}
	else
	{
		
	}
	
	
}

void SpawnEnemiesManager::level2Boss()
{
	if (bossSummoned == false)
	{
		auto level = LVLMAN::Instance()->getLevel();
		Game::Instance()->getCurrentScene()->removeChildByType(ENEMY);
		Game::Instance()->getCurrentScene()->removeChildByType(ENEMYABILITY);
		Game::Instance()->getCurrentScene()->addChild(new BlobKing(level[5][Config::COL_NUM / 2]->getTransform()->position));
		bossSummoned = true;
	}
	else
	{
		
	}
}

void SpawnEnemiesManager::level3Boss()
{
	if (bossSummoned == false)
	{
		auto level = LVLMAN::Instance()->getLevel();
		Game::Instance()->getCurrentScene()->removeChildByType(ENEMY);
		Game::Instance()->getCurrentScene()->removeChildByType(ENEMYABILITY);
		Game::Instance()->getCurrentScene()->addChild(new King(level[5][Config::COL_NUM / 2]->getTransform()->position));
		bossSummoned = true;
	}
	else
	{
		
	}
}



