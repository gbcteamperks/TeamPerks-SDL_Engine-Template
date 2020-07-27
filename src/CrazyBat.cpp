#include "CrazyBat.h"
#include "PlayScene.h"
#include "EnemyLifeBar.h"
#include "LevelManager.h"
CrazyBat::CrazyBat(glm::vec2 position)
{
	TheTextureManager::Instance()->loadSpriteSheet(
		"../Assets/sprites/crazybat.txt",
		"../Assets/sprites/bat-orig.png",
		"crazybat");

	m_pSpriteSheet = TheTextureManager::Instance()->getSpriteSheet("crazybat");
	m_pSpriteSheet->setWidthAndHeight(32, 32);

	// set frame width for the collision
	setWidth(32);

	// set frame height for the collision
	setHeight(32);
	setPosX(position.x);
	setPosY(position.y);

	getTransform()->position = position;
	getRigidBody()->velocity = glm::vec2(2.0f, 2.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(ENEMY);

	m_buildAnimations();
	m_pLife = 20;
	m_lifeRedCounter = m_pLife;
	UI.push_back(new EnemyLifeBar(this));
}

CrazyBat::~CrazyBat()
{
}

void CrazyBat::draw()
{
	Animate();

	for (auto s : UI)
	{
		s->draw(this->m_lifeRedCounter);
	}

}

void CrazyBat::update()
{
	setPosX(getTransform()->position.x);
	setPosY(getTransform()->position.y);

	Rebound();
	cooldownColliding();
	
	for (auto s : UI)
	{
		s->update(this);
	}

}

void CrazyBat::clean()
{
}



void CrazyBat::m_buildAnimations()
{


	Animation runupAnimation = Animation();

	runupAnimation.name = "run_up";

	runupAnimation.frames.push_back(m_pSpriteSheet->getFrame("bat_up1"));
	runupAnimation.frames.push_back(m_pSpriteSheet->getFrame("bat_up2"));
	runupAnimation.frames.push_back(m_pSpriteSheet->getFrame("bat_up3"));
	runupAnimation.frames.push_back(m_pSpriteSheet->getFrame("bat_up4"));


	m_pAnimations["run_up"] = runupAnimation;

	Animation runleftAnimation = Animation();

	runleftAnimation.name = "run_left";

	runleftAnimation.frames.push_back(m_pSpriteSheet->getFrame("bat_left1"));
	runleftAnimation.frames.push_back(m_pSpriteSheet->getFrame("bat_left2"));
	runleftAnimation.frames.push_back(m_pSpriteSheet->getFrame("bat_left3"));
	runleftAnimation.frames.push_back(m_pSpriteSheet->getFrame("bat_left4"));


	m_pAnimations["run_left"] = runleftAnimation;

	Animation rundownAnimation = Animation();

	rundownAnimation.name = "run_down";

	rundownAnimation.frames.push_back(m_pSpriteSheet->getFrame("bat_down1"));
	rundownAnimation.frames.push_back(m_pSpriteSheet->getFrame("bat_down2"));
	rundownAnimation.frames.push_back(m_pSpriteSheet->getFrame("bat_down3"));
	rundownAnimation.frames.push_back(m_pSpriteSheet->getFrame("bat_down4"));


	m_pAnimations["run_down"] = rundownAnimation;

	Animation runrightAnimation = Animation();

	runrightAnimation.name = "run_right";

	runrightAnimation.frames.push_back(m_pSpriteSheet->getFrame("bat_right1"));
	runrightAnimation.frames.push_back(m_pSpriteSheet->getFrame("bat_right2"));
	runrightAnimation.frames.push_back(m_pSpriteSheet->getFrame("bat_right3"));
	runrightAnimation.frames.push_back(m_pSpriteSheet->getFrame("bat_right4"));


	m_pAnimations["run_right"] = runrightAnimation;

}

void CrazyBat::Animate()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;
	float animationVelocity = 0.50f;
	// draw the player according to animation state
	switch (m_currentAnimationState)
	{
	case PLAYER_RUN_LEFT:
		TheTextureManager::Instance()->playAnimation("crazybat", m_pAnimations["run_left"],
			x, y, animationVelocity, 0, 255, true);
		break;
	case PLAYER_RUN_UP:
		TheTextureManager::Instance()->playAnimation("crazybat", m_pAnimations["run_up"],
			x, y, animationVelocity, 0, 255, true);
		break;
	case PLAYER_RUN_RIGHT:
		TheTextureManager::Instance()->playAnimation("crazybat", m_pAnimations["run_right"],
			x, y, animationVelocity, 0, 255, true);
		break;
	case PLAYER_RUN_DOWN:
		TheTextureManager::Instance()->playAnimation("crazybat", m_pAnimations["run_down"],
			x, y, animationVelocity, 0, 255, true);
		break;
	default:
		break;
	}
}

void CrazyBat::Rebound()
{
	Move(getRigidBody()->velocity.x, 0);
	if (collidingWithLevel(LevelManager::Instance()->getObstacles()))
	{
		getRigidBody()->velocity.x *= -1;
		Move(getRigidBody()->velocity.x, getRigidBody()->velocity.y*-1);
	}
	Move(0, getRigidBody()->velocity.y);
	if (collidingWithLevel(LevelManager::Instance()->getObstacles()))
	{
		getRigidBody()->velocity.y *= -1;
		Move(getRigidBody()->velocity.x * -1, getRigidBody()->velocity.y);
	}
}
