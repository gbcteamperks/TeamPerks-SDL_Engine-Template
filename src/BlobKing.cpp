#include "BlobKing.h"
#include "TextureManager.h"
#include "EnemyLifeBar.h"

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
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(BOSS);

	m_Life = 300;
	m_lifeRedCounter = m_Life;
	UI.push_back(new EnemyLifeBar);
	m_buildAnimations();
	
}

BlobKing::~BlobKing()
{
	
}

void BlobKing::draw()
{
	Animate();
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

	for (auto ui : UI)
	{
		ui->update(this);
	}
}

void BlobKing::clean()
{
	
}

void BlobKing::useCurrentAbility()
{
	
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
		TheTextureManager::Instance()->playAnimation("blobking", m_pAnimations["blobking_down"],
			x, y, animationVelocity, 0, 255, true);
		break;

	case PLAYER_RUN_LEFT:
		TheTextureManager::Instance()->playAnimation("blobking", m_pAnimations["blobking_up"],
			x, y, animationVelocity, 0, 255, true);
		break;
	default:
		TheTextureManager::Instance()->playAnimation("blobking", m_pAnimations["blobking_right"],
			x, y, animationVelocity, 0, 255, true);
		break;
	}
}
