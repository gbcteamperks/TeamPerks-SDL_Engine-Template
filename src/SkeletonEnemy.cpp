#include "SkeletonEnemy.h"
#include "TextureManager.h"
#include "Game.h"
#include "LevelManager.h"
#include "MathManager.h"
#include "SpriteSheet.h"
#include "EnemyLifeBar.h"
#include "Util.h"

SkeletonEnemy::SkeletonEnemy(glm::vec2 position) : m_currentAnimationState(SKEL_WALK_RIGHT)
{
	TheTextureManager::Instance()->loadSpriteSheet(
		"../Assets/sprites/skeleton.txt",
		"../Assets/sprites/skeleton.png",
		"skeleton");

	m_pSpriteSheet = TheTextureManager::Instance()->getSpriteSheet("skeleton");
	// set frame width
	setWidth(64);

	// set frame height
	setHeight(64);
	setPosX(position.x);
	setPosY(position.y);

	getTransform()->position = position;
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(ENEMY);

	m_buildAnimations();
	// Life
	m_pLife = 200;
	m_lifeRedCounter = m_pLife;
	UI.push_back(new EnemyLifeBar(this));
}

SkeletonEnemy::~SkeletonEnemy()
= default;

void SkeletonEnemy::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	// draw the player according to animation state
	switch (m_currentAnimationState)
	{
	case SKEL_WALK_LEFT:
		TheTextureManager::Instance()->playAnimation("skeleton", m_pAnimations["run_left"],
			x, y, 0.12f, 0, 255, true);
		break;
	case SKEL_WALK_UP:
		TheTextureManager::Instance()->playAnimation("skeleton", m_pAnimations["run_up"],
			x, y, 0.25f, 0, 255, true);
		break;
	case SKEL_WALK_RIGHT:
		TheTextureManager::Instance()->playAnimation("skeleton", m_pAnimations["run_right"],
			x, y, 0.12f, 0, 255, true);
		break;
	case SKEL_WALK_DOWN:
		TheTextureManager::Instance()->playAnimation("skeleton", m_pAnimations["run_down"],
			x, y, 0.25f, 0, 255, true);
		break;
	default:
		break;
	}
	animateBloodSplat();
	for (auto s : UI)
	{
		s->draw(this->m_lifeRedCounter);
	}
}

void SkeletonEnemy::update()
{
	setPosX(getTransform()->position.x);
	setPosY(getTransform()->position.y);
	Patrol();
	skeltnAtk();
	for (auto s : UI)
	{
		s->update(this);
	}

}

void SkeletonEnemy::clean()
{
}

void SkeletonEnemy::setAnimationState(SkeltnAnimationState new_state)
{
	m_currentAnimationState = new_state;
}

void SkeletonEnemy::setAnimation(const Animation& animation)
{
	m_pAnimations[animation.name] = animation;
}

void SkeletonEnemy::m_buildAnimations()
{
	Animation runupAnimation = Animation();
	runupAnimation.name = "run_up";
	runupAnimation.frames.push_back(m_pSpriteSheet->getFrame("skel-up-1"));
	runupAnimation.frames.push_back(m_pSpriteSheet->getFrame("skel-up-3"));
	runupAnimation.frames.push_back(m_pSpriteSheet->getFrame("skel-up-4"));
	runupAnimation.frames.push_back(m_pSpriteSheet->getFrame("skel-up-6"));
	runupAnimation.frames.push_back(m_pSpriteSheet->getFrame("skel-up-7"));
	runupAnimation.frames.push_back(m_pSpriteSheet->getFrame("skel-up-8"));
	
	m_pAnimations["run_up"] = runupAnimation;

	Animation runleftAnimation = Animation();
	runleftAnimation.name = "run_left";
	runleftAnimation.frames.push_back(m_pSpriteSheet->getFrame("skel-left-1"));
	runleftAnimation.frames.push_back(m_pSpriteSheet->getFrame("skel-left-3"));
	runleftAnimation.frames.push_back(m_pSpriteSheet->getFrame("skel-left-4"));
	runleftAnimation.frames.push_back(m_pSpriteSheet->getFrame("skel-left-5"));
	m_pAnimations["run_left"] = runleftAnimation;

	Animation rundownAnimation = Animation();
	rundownAnimation.name = "run_down";
	rundownAnimation.frames.push_back(m_pSpriteSheet->getFrame("skel-down-1"));
	rundownAnimation.frames.push_back(m_pSpriteSheet->getFrame("skel-down-3"));
	rundownAnimation.frames.push_back(m_pSpriteSheet->getFrame("skel-down-4"));
	rundownAnimation.frames.push_back(m_pSpriteSheet->getFrame("skel-down-6"));
	rundownAnimation.frames.push_back(m_pSpriteSheet->getFrame("skel-down-7"));
	rundownAnimation.frames.push_back(m_pSpriteSheet->getFrame("skel-down-8"));
	m_pAnimations["run_down"] = rundownAnimation;

	Animation runrightAnimation = Animation();
	runrightAnimation.name = "run_right";
	runrightAnimation.frames.push_back(m_pSpriteSheet->getFrame("skel-right-2"));
	runrightAnimation.frames.push_back(m_pSpriteSheet->getFrame("skel-right-3"));
	runrightAnimation.frames.push_back(m_pSpriteSheet->getFrame("skel-right-4"));
	runrightAnimation.frames.push_back(m_pSpriteSheet->getFrame("skel-right-5"));
	m_pAnimations["run_right"] = runrightAnimation;

}


void SkeletonEnemy::skeltnAtk()
{
}

void SkeletonEnemy::Patrol()
{
	m_currentTime = (SDL_GetTicks() / 1000);
	if (m_enemyFacingRight && !m_enemyWaitToFire)
	{
		setAnimationState(SKEL_WALK_RIGHT);
		getTransform()->position.x += 2;
		if (getTransform()->position.x >= (Config::SCREEN_WIDTH) - getWidth())
		{
			m_enemyFacingRight = false;
		}
		if (m_currentTime - m_prevTime > 5)
		{
			m_enemyWaitToFire = true;
			setAnimationState(SKEL_WALK_RIGHT);
		}
	}
	else if (!m_enemyFacingRight && !m_enemyWaitToFire)
	{
		setAnimationState(SKEL_WALK_LEFT);
		getTransform()->position.x -= 2;
		if (getTransform()->position.x <= getWidth())
		{
			m_enemyFacingRight = true;
		}
		if (m_currentTime - m_prevTime > 5)
		{
			m_enemyWaitToFire = true;
			setAnimationState(SKEL_WALK_LEFT);
		}
	}
	else
	{
		//IDLE ANIMATION TRIGGER DELAY - in progress, but skipped due to time issues
		if (m_currentTime - m_prevTime > 5.00f)
		{
			m_prevTime = m_currentTime;
		}
		else
		{
			m_enemyWaitToFire = false;
		}
	}
}
