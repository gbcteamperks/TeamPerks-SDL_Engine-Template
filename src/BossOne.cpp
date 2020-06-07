#include "BossOne.h"
#include "TextureManager.h"

BossOne::BossOne() : m_currentAnimationState(BOSSONE_IDLE_RIGHT)
{
	TheTextureManager::Instance()->loadSpriteSheet(
		"../Assets/sprites/atlas.txt",
		"../Assets/sprites/atlas.png",
		"spritesheet");

	m_pSpriteSheet = TheTextureManager::Instance()->getSpriteSheet("spritesheet");

	// set frame width
	setWidth(53);

	// set frame height
	setHeight(58);

	getTransform()->position = glm::vec2(400.0f, 300.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(PLAYER);

	m_buildAnimations();
}

BossOne::~BossOne()
= default;

void BossOne::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	// draw the player according to animation state
	switch (m_currentAnimationState)
	{
	case BOSSONE_IDLE_RIGHT:
		TheTextureManager::Instance()->playAnimation("spritesheet", m_pAnimations["idle"],
			x, y, 0.12f, 0, 255, true);
		break;
	case BOSSONE_IDLE_LEFT:
		TheTextureManager::Instance()->playAnimation("spritesheet", m_pAnimations["idle"],
			x, y, 0.12f, 0, 255, true, SDL_FLIP_HORIZONTAL);
		break;
	case BOSSONE_RUN_RIGHT:
		TheTextureManager::Instance()->playAnimation("spritesheet", m_pAnimations["run"],
			x, y, 0.25f, 0, 255, true);
		break;
	case BOSSONE_RUN_LEFT:
		TheTextureManager::Instance()->playAnimation("spritesheet", m_pAnimations["run"],
			x, y, 0.25f, 0, 255, true, SDL_FLIP_HORIZONTAL);
		break;
	default:
		break;
	}

}

void BossOne::update()
{
	runHereThere();
}

void BossOne::clean()
{
}

void BossOne::setAnimationState(const BossOneAnimationState new_state)
{
	m_currentAnimationState = new_state;
}

void BossOne::setAnimation(const Animation & animation)
{
	m_pAnimations[animation.name] = animation;
}


void BossOne::m_buildAnimations()
{
	Animation idleAnimation = Animation();

	idleAnimation.name = "idle";
	idleAnimation.frames.push_back(m_pSpriteSheet->getFrame("megaman-idle-0"));
	idleAnimation.frames.push_back(m_pSpriteSheet->getFrame("megaman-idle-1"));
	idleAnimation.frames.push_back(m_pSpriteSheet->getFrame("megaman-idle-2"));
	idleAnimation.frames.push_back(m_pSpriteSheet->getFrame("megaman-idle-3"));

	m_pAnimations["idle"] = idleAnimation;

	Animation runAnimation = Animation();

	runAnimation.name = "run";
	runAnimation.frames.push_back(m_pSpriteSheet->getFrame("megaman-run-0"));
	runAnimation.frames.push_back(m_pSpriteSheet->getFrame("megaman-run-1"));
	runAnimation.frames.push_back(m_pSpriteSheet->getFrame("megaman-run-2"));
	runAnimation.frames.push_back(m_pSpriteSheet->getFrame("megaman-run-3"));

	m_pAnimations["run"] = runAnimation;
}

void BossOne::runHereThere()
{
	if (m_bossFacingRight)
	{
		setAnimationState(BOSSONE_RUN_RIGHT);
		getTransform()->position.x += 2;
		if (getTransform()->position.x >= (Config::SCREEN_WIDTH) - getWidth())
		{
			m_bossFacingRight = false;
		}
	}
	else if (!m_bossFacingRight)
	{
		setAnimationState(BOSSONE_RUN_LEFT);
		getTransform()->position.x -= 2;
		if (getTransform()->position.x <= getWidth())
		{
			m_bossFacingRight = true;
		}
	}


}