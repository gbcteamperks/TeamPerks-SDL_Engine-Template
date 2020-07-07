#include "RatKing.h"
#include "RatBiter.h"
#include "TextureManager.h"

RatKing::RatKing()
{
	TextureManager::Instance()->loadSpriteSheet(
		"../Assets/sprites/rat_king.txt",
		"../Assets/sprites/rat_king.png",
		"ratking"
	);

	m_pSpriteSheet = TextureManager::Instance()->getSpriteSheet("ratking");
	
	m_pSpriteSheet->setWidthAndHeight(128, 128);
	
	//frame width and height
	setWidth(96);
	setHeight(96);
	
	getTransform()->position = glm::vec2(400.0f, 150.0f);;
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(BOSS);
	addAbility(new RatBiter());
	

	m_buildAnimations();
}


void RatKing::draw()
{
	Animate();
}

void RatKing::update()
{
	//update the functionality
	static int tempCounter = 0;
	
	if (tempCounter > 120) {
		int randomNum = rand() % 2;
		if (randomNum == 0)
		{
			m_currentAnimationState = PLAYER_RUN_LEFT;
		}
		else if (randomNum == 1)
		{
			m_currentAnimationState = PLAYER_RUN_RIGHT;
			useCurrentAbility();
		}
		m_currentAnimationState = static_cast<PlayerAnimationState>(rand() % 8); //num of animation states

		tempCounter = 0;
	}
	tempCounter++;
}

void RatKing::useCurrentAbility()
{
	if (m_pListAbilities.size() > 0) {
		switch (m_currentAnimationState)
		{
		case PLAYER_RUN_RIGHT:
			m_pListAbilities.front()->execute(getTransform()->position, 180); // to the left
			changeAbility();
			break;
		default:
			break;
		}

	}
}


void RatKing::m_buildAnimations()
{
	Animation idle = Animation();
	idle.name = "ratK_idle";
	idle.frames.push_back(m_pSpriteSheet->getFrame("idle-1"));
	idle.frames.push_back(m_pSpriteSheet->getFrame("idle-2"));
	idle.frames.push_back(m_pSpriteSheet->getFrame("idle-3"));
	idle.frames.push_back(m_pSpriteSheet->getFrame("idle-4"));
	idle.frames.push_back(m_pSpriteSheet->getFrame("idle-5"));
	idle.frames.push_back(m_pSpriteSheet->getFrame("idle-6"));
	m_pAnimations["ratK_idle"] = idle;
	

	Animation push = Animation();
	push.name = "ratK_push";
	push.frames.push_back(m_pSpriteSheet->getFrame("push-1"));
	push.frames.push_back(m_pSpriteSheet->getFrame("push-2"));
	push.frames.push_back(m_pSpriteSheet->getFrame("push-3"));
	push.frames.push_back(m_pSpriteSheet->getFrame("push-4"));
	push.frames.push_back(m_pSpriteSheet->getFrame("push-5"));
	push.frames.push_back(m_pSpriteSheet->getFrame("push-6"));
	push.frames.push_back(m_pSpriteSheet->getFrame("push-7"));
	push.frames.push_back(m_pSpriteSheet->getFrame("push-8"));
	m_pAnimations["ratK_push"] = push;


	Animation bite = Animation();
	bite.name = "ratK_bite";
	bite.frames.push_back(m_pSpriteSheet->getFrame("bite-1"));
	bite.frames.push_back(m_pSpriteSheet->getFrame("bite-2"));
	bite.frames.push_back(m_pSpriteSheet->getFrame("bite-3"));
	bite.frames.push_back(m_pSpriteSheet->getFrame("bite-4"));
	bite.frames.push_back(m_pSpriteSheet->getFrame("bite-5"));
	bite.frames.push_back(m_pSpriteSheet->getFrame("bite-6"));
	m_pAnimations["ratK_bite"] = bite;

	Animation dead = Animation();
	dead.name = "ratK_dead";
	dead.frames.push_back(m_pSpriteSheet->getFrame("dead-1"));
	dead.frames.push_back(m_pSpriteSheet->getFrame("dead-2"));
	dead.frames.push_back(m_pSpriteSheet->getFrame("dead-3"));
	dead.frames.push_back(m_pSpriteSheet->getFrame("dead-4"));
	dead.frames.push_back(m_pSpriteSheet->getFrame("dead-5"));
	dead.frames.push_back(m_pSpriteSheet->getFrame("dead-6"));
	dead.frames.push_back(m_pSpriteSheet->getFrame("dead-7"));
	dead.frames.push_back(m_pSpriteSheet->getFrame("dead-8"));
	dead.frames.push_back(m_pSpriteSheet->getFrame("dead-9"));
	m_pAnimations["ratK_dead"] = dead;

}

void RatKing::Animate()
{

	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;
	float animationVelocity = 0.40f;

	switch (m_currentAnimationState)
	{
		case PLAYER_RUN_RIGHT:
			TheTextureManager::Instance()->playAnimation("ratking", m_pAnimations["ratK_bite"],
				x, y, animationVelocity, 0, 255, true);
			break;

		case PLAYER_RUN_LEFT:
			TheTextureManager::Instance()->playAnimation("ratking", m_pAnimations["ratK_push"],
				x, y, animationVelocity, 0, 255, true);
			break;
		default:
			TheTextureManager::Instance()->playAnimation("ratking", m_pAnimations["ratK_idle"],
				x, y, animationVelocity, 0, 255, true);
			break;
	}

}

RatKing::~RatKing()
{
	//destructor
}

void RatKing::clean()
{
}


