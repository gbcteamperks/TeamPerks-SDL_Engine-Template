#include "SkeletonEnemy.h"
#include "TextureManager.h"
#include "Game.h"
#include "LevelManager.h"
#include "MathManager.h"
#include "SpriteSheet.h"
#include "EnemyLifeBar.h"
#include "Util.h"

SkeletonEnemy::SkeletonEnemy(glm::vec2 position)
{
	TheTextureManager::Instance()->loadSpriteSheet(
		"../Assets/sprites/skeleton.txt",
		"../Assets/sprites/skeleton.png",
		"skeleton");

	m_pSpriteSheet = TheTextureManager::Instance()->getSpriteSheet("skeleton");
	m_pSpriteSheet->setWidthAndHeight(128, 128);
	// set frame width
	setWidth(64);

	// set frame height
	setHeight(64);
	setPosX(position.x);
	setPosY(position.y);

	getTransform()->position = position;
	getRigidBody()->velocity = glm::vec2(2.0f, 2.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(ENEMY);

	m_buildAnimations();
	// Life
	m_pLife = 200;
	m_lifeRedCounter = m_pLife;
	UI.push_back(new EnemyLifeBar);
}

SkeletonEnemy::~SkeletonEnemy()
{
}


void SkeletonEnemy::draw()
{
	Animate();
	for (auto s : UI)
	{
		s->draw(this->m_lifeRedCounter);
	}

}

void SkeletonEnemy::update()
{
	checkCollisionWithLevel(LevelManager::Instance()->getObstacles());
	
	setPosX(getTransform()->position.x);
	setPosY(getTransform()->position.y);

	static int tempcounter = 0;
	if (tempcounter > 60) //change state every 60 seconds
	{
		if (m_randomAction == 0)
		{
			if (m_angle >= -45 && m_angle < 45)
			{
				m_currentAnimationState = PLAYER_RUN_RIGHT;
			}
			else if (m_angle >= 45 && m_angle < 135)
			{
				m_currentAnimationState = PLAYER_RUN_DOWN;
			}
			else if (m_angle >= 135 && m_angle < -135)
			{
				m_currentAnimationState = PLAYER_RUN_LEFT;
			}
			else if (m_angle >= -135 && m_angle < -45)
			{
				m_currentAnimationState = PLAYER_RUN_UP;
			}
			fleeBehaviour(PlayScene::listPlayers[0]);
			if (PlayScene::listPlayers.size() > 1)
			{
				fleeBehaviour(PlayScene::listPlayers[1]);
			}
			if (tempcounter > 120) {
				tempcounter = 0;
				m_randomAction = rand() % 2;
			}
		}
		else if (m_randomAction == 1)
		{
			tempcounter = 0;
			m_randomAction = rand() % 2;
		}

	}
	tempcounter++;
	for (auto s : UI)
	{
		s->update(this);
	}

}

void SkeletonEnemy::clean()
{
}

void SkeletonEnemy::m_buildAnimations()
{
	Animation runupAnimation = Animation();
	runupAnimation.name = "run_up";
	runupAnimation.frames.push_back(m_pSpriteSheet->getFrame("skel-up-1"));
	runupAnimation.frames.push_back(m_pSpriteSheet->getFrame("skel-up-2"));
	runupAnimation.frames.push_back(m_pSpriteSheet->getFrame("skel-up-3"));
	runupAnimation.frames.push_back(m_pSpriteSheet->getFrame("skel-up-4"));
	runupAnimation.frames.push_back(m_pSpriteSheet->getFrame("skel-up-5"));
	runupAnimation.frames.push_back(m_pSpriteSheet->getFrame("skel-up-6"));
	runupAnimation.frames.push_back(m_pSpriteSheet->getFrame("skel-up-7"));
	runupAnimation.frames.push_back(m_pSpriteSheet->getFrame("skel-up-8"));
	runupAnimation.frames.push_back(m_pSpriteSheet->getFrame("skel-up-9"));
	m_pAnimations["run_up"] = runupAnimation;

	Animation runleftAnimation = Animation();
	runleftAnimation.name = "run_left";
	runleftAnimation.frames.push_back(m_pSpriteSheet->getFrame("skel-left-1"));
	runleftAnimation.frames.push_back(m_pSpriteSheet->getFrame("skel-left-2"));
	runleftAnimation.frames.push_back(m_pSpriteSheet->getFrame("skel-left-3"));
	runleftAnimation.frames.push_back(m_pSpriteSheet->getFrame("skel-left-4"));
	runleftAnimation.frames.push_back(m_pSpriteSheet->getFrame("skel-left-5"));
	runleftAnimation.frames.push_back(m_pSpriteSheet->getFrame("skel-left-6"));
	runleftAnimation.frames.push_back(m_pSpriteSheet->getFrame("skel-left-7"));
	runleftAnimation.frames.push_back(m_pSpriteSheet->getFrame("skel-left-8"));
	runleftAnimation.frames.push_back(m_pSpriteSheet->getFrame("skel-left-9"));
	m_pAnimations["run_left"] = runleftAnimation;

	Animation rundownAnimation = Animation();
	rundownAnimation.name = "run_down";
	rundownAnimation.frames.push_back(m_pSpriteSheet->getFrame("skel-down-1"));
	rundownAnimation.frames.push_back(m_pSpriteSheet->getFrame("skel-down-2"));
	rundownAnimation.frames.push_back(m_pSpriteSheet->getFrame("skel-down-3"));
	rundownAnimation.frames.push_back(m_pSpriteSheet->getFrame("skel-down-4"));
	rundownAnimation.frames.push_back(m_pSpriteSheet->getFrame("skel-down-5"));
	rundownAnimation.frames.push_back(m_pSpriteSheet->getFrame("skel-down-6"));
	rundownAnimation.frames.push_back(m_pSpriteSheet->getFrame("skel-down-7"));
	rundownAnimation.frames.push_back(m_pSpriteSheet->getFrame("skel-down-8"));
	rundownAnimation.frames.push_back(m_pSpriteSheet->getFrame("skel-down-9"));
	m_pAnimations["run_down"] = rundownAnimation;

	Animation runrightAnimation = Animation();
	runrightAnimation.name = "run_right";
	runrightAnimation.frames.push_back(m_pSpriteSheet->getFrame("skel-right-1"));
	runrightAnimation.frames.push_back(m_pSpriteSheet->getFrame("skel-right-2"));
	runrightAnimation.frames.push_back(m_pSpriteSheet->getFrame("skel-right-3"));
	runrightAnimation.frames.push_back(m_pSpriteSheet->getFrame("skel-right-4"));
	runrightAnimation.frames.push_back(m_pSpriteSheet->getFrame("skel-right-5"));
	runrightAnimation.frames.push_back(m_pSpriteSheet->getFrame("skel-right-6"));
	runrightAnimation.frames.push_back(m_pSpriteSheet->getFrame("skel-right-7"));
	runrightAnimation.frames.push_back(m_pSpriteSheet->getFrame("skel-right-8"));
	runrightAnimation.frames.push_back(m_pSpriteSheet->getFrame("skel-right-9"));
	m_pAnimations["run_right"] = runrightAnimation;

}

void SkeletonEnemy::Animate()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;
	float animationVelocity = 0.50f;
	// draw the player according to animation state
	switch (m_currentAnimationState)
	{
	case PLAYER_RUN_LEFT:
		TheTextureManager::Instance()->playAnimation("skeleton", m_pAnimations["run_left"],
			x, y, animationVelocity, 0, 245, true);
		break;
	case PLAYER_RUN_UP:
		TheTextureManager::Instance()->playAnimation("skeleton", m_pAnimations["run_up"],
			x, y, animationVelocity, 0, 245, true);
		break;
	case PLAYER_RUN_RIGHT:
		TheTextureManager::Instance()->playAnimation("skeleton", m_pAnimations["run_right"],
			x, y, animationVelocity, 0, 245, true);
		break;
	case PLAYER_RUN_DOWN:
		TheTextureManager::Instance()->playAnimation("skeleton", m_pAnimations["run_down"],
			x, y, animationVelocity, 0, 245, true);
		break;
	default:
		break;
	}
}
