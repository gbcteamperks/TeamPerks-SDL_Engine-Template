#include "RatKing.h"
#include "RatBiter.h"
#include "TextureManager.h"
#include "Util.h"
#include "EnemyLifeBar.h"
#include "MathManager.h"

RatKing::RatKing(glm::vec2 position)
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
	setPosX(position.x - getWidth()*0.5);
	setPosY(position.y - getHeight()*0.5);
	
	getTransform()->position = glm::vec2(position);;
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(BOSS);
	addAbility(new RatBiter());
	m_EnemyName = "Rat King";
	m_pLife = 400;
	m_lifeRedCounter = m_pLife;
	UI.push_back(new EnemyLifeBar(this));
	getRigidBody()->velocity = { 4,4 };
	m_buildAnimations();
	m_pDamage = 7;

	setPosX(getTransform()->position.x - getWidth() * 0.5);
	setPosY(getTransform()->position.y - getHeight() * 0.5);
	
}


void RatKing::draw()
{
	Animate();
	animateBloodSplat();
	for (auto s : UI)
	{
		s->draw(this->m_lifeRedCounter);
	}
}

void RatKing::update()
{
	
	//update the functionality
	static int tempCounter = 0;
	if(Util::distance(PlayScene::listPlayers[0]->getTransform()->position, this->getTransform()->position) < 100)
	{
		playerPos = PlayScene::listPlayers[0]->getTransform()->position;
		m_angle = MathManager::AngleBetweenPoints(this->getTransform()->position, PlayScene::listPlayers[0]->getTransform()->position);
	}
	if(Util::distance(PlayScene::listPlayers[0]->getTransform()->position,this->getTransform()->position) < 60)
	{
		//m_currentAnimationState = PLAYER_RUN_LEFT;
		m_pushBack();
		
		SoundManager::Instance().playSound("whip");
		
	}
	else
	{
		m_currentAnimationState = PLAYER_RUN_DOWN;
	}

	if((PlayScene::listPlayers[0]->getTransform()->position.x + PlayScene::listPlayers[0]->getWidth() * 0.5) > (getTransform()->position.x + getWidth() * 0.5))
	{
		m_flip = true;
	}
	else
	{
		m_flip = false;
	}

	if(pushBackGo)
	{
		m_currentAnimationState = PLAYER_RUN_LEFT;
		PlayScene::listPlayers[0]->Move(getRigidBody()->velocity.x, getRigidBody()->velocity.y);
		if(currentTime == 0)
		{
			currentTime = SDL_GetTicks() / 1000.0f;
			PlayScene::listPlayers[0]->getLife() -= m_pDamage;
		}
		if((SDL_GetTicks() / 1000.0f) - currentTime > duration)
		{
			currentTime = 0;
			getRigidBody()->velocity = { 4,4 };
			
			pushBackGo = false;
		}
		
	}

	int randomNum = rand() % 100;
	if (randomNum == 4)
	{
		/*if(abilityUsed == false)
		{*/
			useCurrentAbility();
		/*	abilityUsed = true;
		}*/
		
	}
		//m_currentAnimationState = static_cast<PlayerAnimationState>(rand() % 8); //num of animation states

		
	

	for (auto ui : UI)
	{
		ui->update(this);
	}
}

void RatKing::useCurrentAbility()
{
	/*if (m_pListAbilities.size() > 0) {
		switch (m_currentAnimationState)
		{
		case PLAYER_RUN_RIGHT:*/
	if (abilityUsed == false)
	{
		/*m_pListAbilities.front()->execute({ getPosX() - 20 ,getColY() - 20 }, 0, true);
		m_pListAbilities.front()->execute({ getPosX() + getWidth(), getPosY()}, 0, true);
		m_pListAbilities.front()->execute({ getPosX() - 20 ,getColY() + getHeight() }, 0, true);
		m_pListAbilities.front()->execute({ getPosX() + getWidth(), getPosY() + getHeight()}, 0, true);*/

		m_pListAbilities.front()->execute({ 400,50 }, 0, true);
		m_pListAbilities.front()->execute({ 700,50  }, 0, true);
		m_pListAbilities.front()->execute({  300,300 }, 0, true);
		m_pListAbilities.front()->execute({ 580,300}, 0, true);
		abilityUsed = true;
	}
		
			/*changeAbility();
			break;
		default:
			break;
		}

	}*/
}

void RatKing::m_pushBack()
{
	directionToPush = { cos(MathManager::Deg2Rad(m_angle)) , sin(MathManager::Deg2Rad(m_angle)) };
	getRigidBody()->velocity *= directionToPush;
	//std::cout << "Velocity = " << getRigidBody()->velocity.x << "," << getRigidBody()->velocity.y << std::endl;
	pushBackGo = true;
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
			if(m_flip)
			{
				TheTextureManager::Instance()->playAnimation("ratking", m_pAnimations["ratK_bite"],
					x, y, animationVelocity, 0, 255, true,SDL_FLIP_HORIZONTAL);
			}
			else
			{
				TheTextureManager::Instance()->playAnimation("ratking", m_pAnimations["ratK_bite"],
					x, y, animationVelocity, 0, 255, true,SDL_FLIP_NONE);
			}
			break;

		case PLAYER_RUN_LEFT:
			if (m_flip)
			{
				TheTextureManager::Instance()->playAnimation("ratking", m_pAnimations["ratK_push"],
					x, y, animationVelocity, 0, 255, true, SDL_FLIP_HORIZONTAL);
			}
			else
			{
				TheTextureManager::Instance()->playAnimation("ratking", m_pAnimations["ratK_push"],
					x, y, animationVelocity, 0, 255, true, SDL_FLIP_NONE);
			}
			break;
		case PLAYER_RUN_DOWN:
			if (m_flip)
			{
				TheTextureManager::Instance()->playAnimation("ratking", m_pAnimations["ratK_idle"],
					x, y, animationVelocity, 0, 255, true, SDL_FLIP_HORIZONTAL);
			}
			else
			{
				TheTextureManager::Instance()->playAnimation("ratking", m_pAnimations["ratK_idle"],
					x, y, animationVelocity, 0, 255, true, SDL_FLIP_NONE);
			}
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


