#include "SpawnEnemiesManager.h"
#include "LevelManager.h"
#include "MathManager.h"
#include "CollisionManager.h"
#include "MotherSpider.h"
#include "EnemyWizard.h"
#include "RatKing.h"
#include "SkeletonEnemy.h"
#include "Config.h"
#include "Game.h"
int SpawnEnemiesManager::randomNum = rand() % 120 + 300;
void SpawnEnemiesManager::level1()
{
	static int timer = 0;
	int countEnemies = Game::Instance()->getCurrentScene()->getEnemies().size();
	auto level = LVLMAN::Instance()->getLevel();
	if (timer > randomNum && countEnemies < 4)
	{
		int randomCol = rand() % Config::COL_NUM;
		int randomRow = rand() % Config::ROW_NUM;
		for (int col = randomCol; col < Config::COL_NUM; col++)
		{
			for (int row = randomRow; row < Config::ROW_NUM; row++)
			{
				if (!level[row][col]->isObstacle()) 
				{
					int randomEnemy = rand() % 100;
					if (randomEnemy <= 30)
					{
						Game::Instance()->getCurrentScene()->addChild(new EnemyWizard(level[row][col]->getTransform()->position));
					}
					else if(randomEnemy >= 31 && randomEnemy <= 64)
					{
						//possible bug!!!!
						Game::Instance()->getCurrentScene()->addChild(new SkeletonEnemy(level[row][col]->getTransform()->position));
					}
					else if(randomEnemy >= 65)
					{
						Game::Instance()->getCurrentScene()->addChild(new MotherSpider(level[row][col]->getTransform()->position));
					}
					
					timer = 0;
					randomNum = rand() % 120 + 300;
					col = Config::COL_NUM;
					row = Config::ROW_NUM;
				}
			}
		}
	}
	timer++;
}
