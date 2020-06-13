#include "BossOne.h"


BossOne::BossOne() : m_currentAnimationState(BOSSONE_WALK_RIGHT)
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

	getTransform()->position = glm::vec2(400.0f, 300.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(BOSS);

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

void BossOne::update()
{
	runHereThere();
	bossAttack();


}

void BossOne::clean()
{
}

void BossOne::bossAttack()
{	
	static int abilityTime = 0;
	
	if ((int)m_currentTime % 3 != 0)
	{
		abilityTime = 0;
	}
	
	/*m_fire = true;
	if (m_bulletNotVisible)
	{
		m_pBossBullet->getTransform()->position = glm::vec2(getTransform()->position.x, 90.0f);
		m_fire = false;
		m_bulletNotVisible = false;
		m_bulletXPosition = getTransform()->position.x;
		m_pBossBullet->getTransform()->position.y = getTransform()->position.y + 90;
	}
	m_fire = true;
	if (m_pBossBullet->getTransform()->position.y > 600)
	{
		m_pBossBullet->getTransform()->position = glm::vec2(-100.0f, -100.0f);
		m_bulletNotVisible = true;
	}
	*/
	if ((int)m_currentTime%3 == 0 && abilityTime == 0)
	{
		abilityTime++;
		useCurrentAbility();
		
		/*if (m_fire == true)
		{
			m_pBossBullet->setXY(m_pBossBullet->getTransform()->position.x, m_pBossBullet->getTransform()->position.y + 5);
		}*/
	}
	
	
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

void BossOne::runHereThere()
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

void BossOne::getBullet(Target* bullet)
{
	m_pBossBullet = bullet;
}

void BossOne::addAbility(Ability* ability)
{
	m_pListAbilities.push_back(ability);
}

void BossOne::deleteAbility()
{
	m_pListAbilities.erase(m_pListAbilities.begin()); //delete the first ability added.
}

void BossOne::useCurrentAbility()
{
	if (m_pListAbilities.size() > 0 && m_abilityReady) {
		m_pListAbilities.front()->execute(getTransform()->position, 90);
	}
}

void BossOne::dropAbility()
{
	if (m_pListAbilities.size() > 0) {
		m_pListAbilities.front()->pickable(getTransform()->position);//adding a pickeable item to DisplayList
	}
}
