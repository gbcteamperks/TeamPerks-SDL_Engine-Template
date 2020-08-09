#include "King.h"
#include "EnemyLifeBar.h"
King::King(glm::vec2 position)
{
	TheTextureManager::Instance()->loadSpriteSheet(
		"../Assets/sprites/KingSpriteSheet.txt",
		"../Assets/sprites/KingSpriteSheet.png",
		"KingSpriteSheet");

	m_pSpriteSheet = TheTextureManager::Instance()->getSpriteSheet("KingSpriteSheet");
	m_pSpriteSheet->setWidthAndHeight(300, 300);

	// set frame width
	setWidth(40);
	// set frame height
	setHeight(60);

	setPosX(position.x - getWidth() * 0.5);
	setPosY(position.y - getHeight() * 0.5);

	getTransform()->position = position;
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;

	setType(ENEMY);
	setState(State::IDLE);

	m_buildAnimations();
	m_Flip = SDL_FLIP_NONE;

	// Life
	m_pLife = 100;
	m_lifeRedCounter = m_pLife;
	UI.push_back(new EnemyLifeBar(this));

}

King::~King()
{
}

void King::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	switch (m_currentState)
	{
	case IDLE:
		if (TheTextureManager::Instance()->playAnimation("KingSpriteSheet", m_pAnimations["idle"],
			x, y, 1.0f, 0, 255, true, m_Flip))
		{
			//setState(RUNNING);
		}
		break;
	}
}

void King::update()
{
}

void King::clean()
{
}

void King::bossAttack()
{
}

bool King::SeekingNode(int x, int y)
{
	return false;
}

void King::m_buildAnimations()
{

	Animation idle = Animation();

	idle.name = "idle";
	idle.frames.push_back(m_pSpriteSheet->getFrame("idle1"));
	idle.frames.push_back(m_pSpriteSheet->getFrame("idle2"));
	idle.frames.push_back(m_pSpriteSheet->getFrame("idle3"));
	idle.frames.push_back(m_pSpriteSheet->getFrame("idle4"));
	idle.frames.push_back(m_pSpriteSheet->getFrame("idle5"));
	idle.frames.push_back(m_pSpriteSheet->getFrame("idle6"));
	idle.frames.push_back(m_pSpriteSheet->getFrame("idle7"));
	idle.frames.push_back(m_pSpriteSheet->getFrame("idle8"));
	idle.frames.push_back(m_pSpriteSheet->getFrame("idle9"));
	idle.frames.push_back(m_pSpriteSheet->getFrame("idle10"));
	idle.frames.push_back(m_pSpriteSheet->getFrame("idle11"));
	idle.frames.push_back(m_pSpriteSheet->getFrame("idle12"));
	idle.frames.push_back(m_pSpriteSheet->getFrame("idle13"));
	idle.frames.push_back(m_pSpriteSheet->getFrame("idle14"));
	idle.frames.push_back(m_pSpriteSheet->getFrame("idle15"));
	idle.frames.push_back(m_pSpriteSheet->getFrame("idle16"));
	idle.frames.push_back(m_pSpriteSheet->getFrame("idle17"));
	idle.frames.push_back(m_pSpriteSheet->getFrame("idle18"));

	m_pAnimations["idle"] = idle;

}
