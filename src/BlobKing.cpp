#include "BlobKing.h"
#include "TextureManager.h"
#include "EnemyLifeBar.h"
#include "MathManager.h"
#include "Slimeattack.h"

BlobKing::BlobKing(glm::vec2 position)
{
	TextureManager::Instance()->loadSpriteSheet(
		"../Assets/sprites/blobking.txt",
		"../Assets/sprites/blobking.png",
		"blobking"
	);

	m_pSpriteSheet = TextureManager::Instance()->getSpriteSheet("blobking");

	m_pSpriteSheet->setWidthAndHeight(64, 64);

	setPosX(position.x);
	setPosY(position.y);

	getTransform()->position = glm::vec2(position);
	getRigidBody()->velocity = glm::vec2(2.0f, 2.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(BOSS);

	addAbility(new Slimeattack());
	m_EnemyName = "Blob King";
	m_pLife = 300;
	m_lifeRedCounter = m_pLife;
	UI.push_back(new EnemyLifeBar(this));
	m_buildAnimations();
	
}

BlobKing::~BlobKing()
{
	
}

void BlobKing::draw()
{
	Animate();
	animateBloodSplat();
	for (auto s : UI)
	{
		s->draw(this->m_lifeRedCounter);
	}
}

void BlobKing::update()
{
	setPosX(getTransform()->position.x);
	setPosY(getTransform()->position.y);

	//update the functionality
	static int tempCounter = 0;

	if (tempCounter > 90) {
		int randomNum = rand() % 2;
		if (randomNum == 0)
		{
			SoundManager::Instance().playSound("slimy", 0, 3);
			useCurrentAbility();
		}
		//m_currentAnimationState = static_cast<PlayerAnimationState>(rand() % 8); //num of animation states

		tempCounter = 0;
	}
	tempCounter++;

	for (auto ui : UI)
	{
		ui->update(this);
	}
	
	if(leftRightToggle)
	{
		
		if(getPosX() > minX && !waiting)
		{
			Move(getRigidBody()->velocity.x, 0);
			//std::cout << getPosX() << std::endl;
			waitTime = SDL_GetTicks() / 1000.0f;
			m_currentAnimationState = PLAYER_RUN_LEFT;
		}
		else if(getPosX() <= minX)
		{
			waiting = true;
			waitTime = SDL_GetTicks() / 1000.0f;
			leftRightToggle = !leftRightToggle;
		}
	}
	else
	{
		if (getPosX() < maxX && !waiting)
		{
			
			Move(getRigidBody()->velocity.x, 0);
			waitTime = SDL_GetTicks() / 1000.0f;
			m_currentAnimationState = PLAYER_RUN_RIGHT;
		}
		else if (getPosX() >= maxX)
		{
			waiting = true;
			leftRightToggle = !leftRightToggle;
		}
	}

	if(waiting)
	{
		m_currentAnimationState = PLAYER_RUN_DOWN;
		if(SDL_GetTicks() / 1000.0f - waitTime >= 4)
		{
			getRigidBody()->velocity.x *= -1;
			waitTime = 0;
			waiting = false;
		}
	}
}

void BlobKing::clean()
{
	
}

void BlobKing::useCurrentAbility()
{
	m_angle = MAMA::AngleBetweenPoints(this->getTransform()->position, PlayScene::listPlayers[0]->getTransform()->position);
	m_pListAbilities.front()->execute(getTransform()->position, m_angle, true); // to the left
}

void BlobKing::m_buildAnimations()
{
	Animation left = Animation();
	left.name = "blobking_left";
	left.frames.push_back(m_pSpriteSheet->getFrame("left-1"));
	left.frames.push_back(m_pSpriteSheet->getFrame("left-2"));
	left.frames.push_back(m_pSpriteSheet->getFrame("left-3"));
	m_pAnimations["blobking_left"] = left;

	Animation right = Animation();
	right.name = "blobking_right";
	right.frames.push_back(m_pSpriteSheet->getFrame("right-1"));
	right.frames.push_back(m_pSpriteSheet->getFrame("right-2"));
	right.frames.push_back(m_pSpriteSheet->getFrame("right-3"));
	m_pAnimations["blobking_right"] = right;

	Animation down = Animation();
	down.name = "blobking_down";
	down.frames.push_back(m_pSpriteSheet->getFrame("down-1"));
	down.frames.push_back(m_pSpriteSheet->getFrame("down-2"));
	down.frames.push_back(m_pSpriteSheet->getFrame("down-3"));
	m_pAnimations["blobking_down"] = down;
	
	Animation up = Animation();
	up.name = "blobking_up";
	up.frames.push_back(m_pSpriteSheet->getFrame("up-1"));
	up.frames.push_back(m_pSpriteSheet->getFrame("up-2"));
	up.frames.push_back(m_pSpriteSheet->getFrame("up-3"));
	m_pAnimations["blobking_up"] = up;
}

void BlobKing::Animate()
{
	//placeholder animations... 
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;
	float animationVelocity = 0.10f;

	switch (m_currentAnimationState)
	{
	case PLAYER_RUN_RIGHT:
		TheTextureManager::Instance()->playAnimation("blobking", m_pAnimations["blobking_right"],
			x, y, animationVelocity, 0, 255, true);
		break;

	case PLAYER_RUN_LEFT:
		TheTextureManager::Instance()->playAnimation("blobking", m_pAnimations["blobking_left"],
			x, y, animationVelocity, 0, 255, true);
		break;
	case PLAYER_RUN_DOWN:
		TheTextureManager::Instance()->playAnimation("blobking", m_pAnimations["blobking_down"],
			x, y, animationVelocity, 0, 255, true);
		break;
	default:
		TheTextureManager::Instance()->playAnimation("blobking", m_pAnimations["blobking_down"],
			x, y, animationVelocity, 0, 255, true);
		break;
	}
}
