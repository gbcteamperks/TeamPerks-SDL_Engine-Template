#include "VictorVanHelsing.h"
#include "TextureManager.h"
#include "CollisionManager.h"
#include "EventManager.h"
#include "MathManager.h"
#include "Sword.h"
#include "LifeBar.h"
#include "Needle.h"
#include "LevelManager.h"
#include "ExplosiveSpider.h"
#include "Orb.h"
#include "Util.h"
int VictorVanHelsing::numberOfPlayers = 0;
VictorVanHelsing::VictorVanHelsing(glm::vec2 pos) : m_currentAnimationState(VICTOR_WALK_UP)
{
	TheTextureManager::Instance()->loadSpriteSheet(
		"../Assets/sprites/victorvanhelsing.txt",
		"../Assets/sprites/victorvanhelsing.png",
		"victorvanhelsing");

	TheTextureManager::Instance()->loadSpriteSheet(
		"../Assets/sprites/bloodsplat2.txt",
		"../Assets/sprites/bloodsplat2.png",
		"bloodsplat2");

	m_pSpriteSheet = TheTextureManager::Instance()->getSpriteSheet("victorvanhelsing");
	m_pSpriteSheetBlood = TheTextureManager::Instance()->getSpriteSheet("bloodsplat2");
	
	
	m_playerNumber = numberOfPlayers; // assign an id to this player
	numberOfPlayers++; //add a player every time a victor is created
	// set collision Box.
	setWidth(35);
	setHeight(48);
	setPosX(pos.x);
	setPosY(pos.y+ 8);

	m_pSpriteSheetBlood->setWidthAndHeight(64, 64);

	getTransform()->position = pos;
	getRigidBody()->velocity = glm::vec2(2.0f, 2.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;

	addAbility(new Sword());
	//addAbility(new ExplosiveSpider());
	//addAbility(new Fireball());
	//addAbility(new Orb());
	setType(VICTOR);

	m_buildAnimations();
	gettingDamage = false;
	m_pObject = this;
	m_currentAbility = 0;

	UIList.push_back(new LifeBar());
	UIList.push_back(new Needle());
	m_pLife = 100;
	//m_abilitieCounter = 0;
}

VictorVanHelsing::~VictorVanHelsing()
= default;

void VictorVanHelsing::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;
	

	switch (m_currentAnimationState)
	{
	case VICTOR_WALK_RIGHT:
		right = true;
		TheTextureManager::Instance()->playAnimation("victorvanhelsing", m_pAnimations["walkright"],
			x, y, 0.12f, 0, 255, true);
		break;
	case VICTOR_WALK_LEFT:
		right = false;
		TheTextureManager::Instance()->playAnimation("victorvanhelsing", m_pAnimations["walkright"],
			x, y, 0.12f, 0, 255, true, SDL_FLIP_HORIZONTAL);
		break;
	case VICTOR_WALK_UP:
		down = false;
		TheTextureManager::Instance()->playAnimation("victorvanhelsing", m_pAnimations["walkup"],
			x, y, 0.25f, 0, 255, true);
		break;
	case VICTOR_WALK_DOWN:
		down = true;
		TheTextureManager::Instance()->playAnimation("victorvanhelsing", m_pAnimations["walkdown"],
			x, y, 0.25f, 0, 255, true);
		break;
	default:
		break;
	}
	animateBloodSplat();
	for (auto s : UIList)
	{
		s->draw();
	}
}

void VictorVanHelsing::update()
{
	setPosX(getTransform()->position.x);
	setPosY(getTransform()->position.y + 8);
	m_BoundsRestrict();
	checkCollisionWithLevel(LVLMAN::Instance()->getObstacles());
	cooldownColliding();

	for (auto s : UIList)
	{
		s->update(this);
	}
}

void VictorVanHelsing::clean()
{
}


void VictorVanHelsing::setAnimationState(const VictorAnimationState new_state)
{
	m_currentAnimationState = new_state;
}

void VictorVanHelsing::setAnimation(const Animation& animation)
{
	m_pAnimations[animation.name] = animation;
}

void VictorVanHelsing::addAbility(Ability* ability)
{	
	if (m_pListAbilities.size() == 4) // 1 sword and 3 abilites
	{
		m_pListAbilities[1] = m_pListAbilities[2];
		m_pListAbilities[2] = m_pListAbilities[3];
		m_pListAbilities[3] = ability;

		//or
		//deleteAbility();
		//m_pListAbilities.push_back(ability);
	}
	else 
	{
		m_pListAbilities.push_back(ability);
	}
}

void VictorVanHelsing::deleteAbility()
{
	m_pListAbilities.erase(m_pListAbilities.begin() + 1); //delete the first ability added.
}

void VictorVanHelsing::useCurrentAbility(int player)
{
	if (player == 1) 
	{
		setAngle(MAMA::AngleBetweenPoints(getTransform()->position, EventManager::Instance().getMousePosition()));
		if (m_pListAbilities.size() > 0) 
		{
			m_pListAbilities[m_currentAbility]->execute(getTransform()->position, getAngle(), false);
		}
	}
	if (player == 2)
	{
		if (m_pListAbilities.size() > 0)
		{
			setAngle(MAMA::AngleBetweenPoints(getTransform()->position, EventManager::Instance().getGameController(0)->getLeftJoystickPosition()));
			m_pListAbilities[m_currentAbility]->execute(getTransform()->position, getAngle(), false);
		}
	}

}

void VictorVanHelsing::changeAbility()
{

	if (m_currentAbility + 1 < m_pListAbilities.size())
	{
		m_currentAbility++;
	}
	else
	{
		m_currentAbility = 0;
	}
}


void VictorVanHelsing::m_buildAnimations()
{
	Animation walkDown = Animation();

	walkDown.name = "walkdown";
	walkDown.frames.push_back(m_pSpriteSheet->getFrame("walkdown-1"));
	walkDown.frames.push_back(m_pSpriteSheet->getFrame("walkdown-2"));
	walkDown.frames.push_back(m_pSpriteSheet->getFrame("walkdown-3"));
	walkDown.frames.push_back(m_pSpriteSheet->getFrame("walkdown-4"));

	m_pAnimations["walkdown"] = walkDown;

	Animation walkLeft = Animation();

	walkLeft.name = "walkleft";
	walkLeft.frames.push_back(m_pSpriteSheet->getFrame("walkleft-1"));
	walkLeft.frames.push_back(m_pSpriteSheet->getFrame("walkleft-2"));
	walkLeft.frames.push_back(m_pSpriteSheet->getFrame("walkleft-3"));
	walkLeft.frames.push_back(m_pSpriteSheet->getFrame("walkleft-4"));

	m_pAnimations["walkleft"] = walkLeft;

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

	Animation bloodsplat = Animation();

	bloodsplat.name = "bloodsplat";
	bloodsplat.frames.push_back(m_pSpriteSheetBlood->getFrame("bloodsplat1"));
	bloodsplat.frames.push_back(m_pSpriteSheetBlood->getFrame("bloodsplat2"));
	bloodsplat.frames.push_back(m_pSpriteSheetBlood->getFrame("bloodsplat3"));
	bloodsplat.frames.push_back(m_pSpriteSheetBlood->getFrame("bloodsplat4"));
	bloodsplat.frames.push_back(m_pSpriteSheetBlood->getFrame("bloodsplat5"));
	bloodsplat.frames.push_back(m_pSpriteSheetBlood->getFrame("bloodsplat6"));
	bloodsplat.frames.push_back(m_pSpriteSheetBlood->getFrame("bloodsplat7"));
	bloodsplat.frames.push_back(m_pSpriteSheetBlood->getFrame("bloodsplat8"));
	bloodsplat.frames.push_back(m_pSpriteSheetBlood->getFrame("bloodsplat9"));
	bloodsplat.frames.push_back(m_pSpriteSheetBlood->getFrame("bloodsplat10"));
	bloodsplat.frames.push_back(m_pSpriteSheetBlood->getFrame("bloodsplat11"));
	bloodsplat.frames.push_back(m_pSpriteSheetBlood->getFrame("bloodsplat12"));
	bloodsplat.frames.push_back(m_pSpriteSheetBlood->getFrame("bloodsplat13"));
	bloodsplat.frames.push_back(m_pSpriteSheetBlood->getFrame("bloodsplat14"));
	bloodsplat.frames.push_back(m_pSpriteSheetBlood->getFrame("bloodsplat15"));
	//bloodsplat.frames.push_back(m_pSpriteSheetBlood->getFrame("bloodsplat16"));


	m_pAnimations["bloodsplat"] = bloodsplat;
}

void VictorVanHelsing::animateBloodSplat()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;
	const float velocityAnimation = 2.0f;
	if (gettingDamage)
	{
		if (TheTextureManager::Instance()->playAnimation("bloodsplat2", m_pAnimations["bloodsplat"],
			x, y, velocityAnimation, 0, 255, true))
		{
			gettingDamage = false;
			m_pAnimations["bloodsplat"].current_frame = 0;
		}
	}
}


