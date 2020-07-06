#include "EnemyWizard.h"
#include "Fireball.h"

EnemyWizard::EnemyWizard() : m_currentAnimationState(BOSSONE_WALK_RIGHT)
{
	TheTextureManager::Instance()->loadSpriteSheet(
		"../Assets/sprites/magicenemy.txt",
		"../Assets/sprites/magicenemy.png",
		"magicenemy");

	m_pSpriteSheet = TheTextureManager::Instance()->getSpriteSheet("magicenemy");

	// set frame width
	setWidth(40);

	// set frame height
	setHeight(60);

	getTransform()->position = glm::vec2(90.0f, 90.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	addAbility(new Fireball());
	setType(BOSS);

	m_buildAnimations();
}

EnemyWizard::~EnemyWizard()
= default;

void EnemyWizard::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	// draw the player according to animation state
	switch (m_currentAnimationState)
	{
	case BOSSONE_WALK_RIGHT:
		TheTextureManager::Instance()->playAnimation("magicenemy", m_pAnimations["walkright"],
			x, y, 0.12f, 0, 255, true);
		break;
	case BOSSONE_WALK_LEFT:
		TheTextureManager::Instance()->playAnimation("magicenemy", m_pAnimations["walkright"],
			x, y, 0.12f, 0, 255, true, SDL_FLIP_HORIZONTAL);
		break;
	case BOSSONE_WALK_UP:
		TheTextureManager::Instance()->playAnimation("magicenemy", m_pAnimations["walkup"],
			x, y, 0.25f, 0, 255, true);
		break;
	case BOSSONE_WALK_DOWN:
		TheTextureManager::Instance()->playAnimation("magicenemy", m_pAnimations["walkdown"],
			x, y, 0.25f, 0, 255, true);
		break;
	default:
		break;
	}

}

void EnemyWizard::update()
{
	runHereThere();
	bossAttack();


}

void EnemyWizard::clean()
{
}

void EnemyWizard::bossAttack()
{
	static int abilityTime = 0;

	if ((int)m_currentTime % 3 != 0)
	{
		abilityTime = 0;
	}

	if ((int)m_currentTime % 3 == 0 && abilityTime == 0)
	{
		abilityTime++;
		useCurrentAbility();
	}


}



void EnemyWizard::setAnimationState(const BossOneAnimationState new_state)
{
	m_currentAnimationState = new_state;
}

void EnemyWizard::setAnimation(const Animation & animation)
{
	m_pAnimations[animation.name] = animation;
}


void EnemyWizard::m_buildAnimations()
{
	Animation walkDown = Animation();

	walkDown.name = "walkdown";
	walkDown.frames.push_back(m_pSpriteSheet->getFrame("walkdown-1"));
	walkDown.frames.push_back(m_pSpriteSheet->getFrame("walkdown-1"));
	walkDown.frames.push_back(m_pSpriteSheet->getFrame("walkdown-1"));
	walkDown.frames.push_back(m_pSpriteSheet->getFrame("walkdown-1"));

	m_pAnimations["walkdown"] = walkDown;

	Animation walkRight = Animation();

	walkRight.name = "walkright";
	walkRight.frames.push_back(m_pSpriteSheet->getFrame("walkright-1"));
	walkRight.frames.push_back(m_pSpriteSheet->getFrame("walkright-2"));
	walkRight.frames.push_back(m_pSpriteSheet->getFrame("walkright-3"));
	walkRight.frames.push_back(m_pSpriteSheet->getFrame("walkright-4"));

	m_pAnimations["walkright"] = walkRight;

	Animation walkUp = Animation();

	walkUp.name = "walkup";
	walkUp.frames.push_back(m_pSpriteSheet->getFrame("walkup-1"));
	walkUp.frames.push_back(m_pSpriteSheet->getFrame("walkup-2"));
	walkUp.frames.push_back(m_pSpriteSheet->getFrame("walkup-3"));
	walkUp.frames.push_back(m_pSpriteSheet->getFrame("walkup-4"));

	m_pAnimations["walkup"] = walkUp;
}

void EnemyWizard::runHereThere()
{
	m_currentTime = (SDL_GetTicks() / 1000);
	if (m_bossFacingRight && !m_bossWaitToFire)
	{
		setAnimationState(BOSSONE_WALK_RIGHT);
		getTransform()->position.x += 2;
		if (getTransform()->position.x >= (Config::SCREEN_WIDTH) - getWidth())
		{
			m_bossFacingRight = false;
		}
		if (m_currentTime - m_prevTime > 5)
		{
			m_bossWaitToFire = true;
			setAnimationState(BOSSONE_WALK_RIGHT);
		}
	}
	else if (!m_bossFacingRight && !m_bossWaitToFire)
	{
		setAnimationState(BOSSONE_WALK_LEFT);
		getTransform()->position.x -= 2;
		if (getTransform()->position.x <= getWidth())
		{
			m_bossFacingRight = true;
		}
		if (m_currentTime - m_prevTime > 5)
		{
			m_bossWaitToFire = true;
			setAnimationState(BOSSONE_WALK_LEFT);
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
			m_bossWaitToFire = false;
		}
	}


}
