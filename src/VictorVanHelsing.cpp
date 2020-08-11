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
		"../Assets/sprites/VictorspriteSheet2.txt",
		"../Assets/sprites/VictorspriteSheet2.png",
		"VictorspriteSheet2");

	TheTextureManager::Instance()->loadSpriteSheet(
		"../Assets/sprites/bloodsplat2.txt",
		"../Assets/sprites/bloodsplat2.png",
		"bloodsplat2");

	m_pSpriteSheet = TheTextureManager::Instance()->getSpriteSheet("VictorspriteSheet2");
	m_pSpriteSheetBlood = TheTextureManager::Instance()->getSpriteSheet("bloodsplat2");
	m_pSpriteSheet->setWidthAndHeight(150, 150);
	
	m_playerNumber = numberOfPlayers; // assign an id to this player
	numberOfPlayers++; //add a player every time a victor is created
	// set collision Box.
	setWidth(35);
	setHeight(48);
	setPosX(pos.x);
	setPosY(pos.y+ 8);
	setSpeed(3.0f);

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
	m_currentState = IDLE;
	m_Flip = SDL_FLIP_NONE;

	m_buildAnimations();
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
	const float velAnimation = 0.75f;

	switch (m_currentState)
	{
	case IDLE:
		TheTextureManager::Instance()->playAnimation("VictorspriteSheet2", m_pAnimations["idle"],
			x, y, velAnimation, 0, 255, true, m_Flip);
		break;
	case RUNNING:
		TheTextureManager::Instance()->playAnimation("VictorspriteSheet2", m_pAnimations["running"],
			x, y, velAnimation, 0, 255, true, m_Flip);
		break;
	case MELEEATK:
		TheTextureManager::Instance()->playAnimation("VictorspriteSheet2", m_pAnimations["meleeatk"],
			x, y, velAnimation, 0, 255, true, m_Flip);
		if (TheTextureManager::Instance()->playAnimation("VictorspriteSheet2", m_pAnimations["meleeatkA"],
			x, y, velAnimation, 0, 255, true, m_Flip))
		{
			setState(IDLE);
		}
		break;
	case RANGEATK:
		TheTextureManager::Instance()->playAnimation("VictorspriteSheet2", m_pAnimations["rangeAtk"],
			x, y, velAnimation, 0, 255, true, m_Flip);
		if (TheTextureManager::Instance()->playAnimation("VictorspriteSheet2", m_pAnimations["rangeAtk"],
			x, y, velAnimation, 0, 255, true, m_Flip))
		{
			setState(IDLE);
		}
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
	Move(getRigidBody()->velocity.x, getRigidBody()->velocity.y);
	setPosY(getPosY() + 8); //just and intended offset

	m_BoundsRestrict();
	if (checkCollisionWithLevel(LVLMAN::Instance()->getObstacles()))
	{
		Move(-getRigidBody()->velocity.x, -getRigidBody()->velocity.y);
	}

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
		if (getAngle() > -90 && getAngle() < 90)
		{
			m_Flip = SDL_FLIP_NONE;
		}
		else {
			m_Flip = SDL_FLIP_HORIZONTAL;
		}
		if (m_currentAbility == 0)
		{
			if (m_Flip == SDL_FLIP_NONE)
				setAngle(0);
			else if (m_Flip == SDL_FLIP_HORIZONTAL)
				setAngle(180);
		}
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


void VictorVanHelsing::handleEventsKeyboard()
{
	switch (m_currentState)
	{
	case IDLE:
				getRigidBody()->velocity = { 0.0f, 0.0f };
				if (isMoving())
				{
					setState(RUNNING);
				}
				checkMouseInput();
				break;
	case RUNNING:
				if (!isMoving())
				{
					setState(IDLE);
				}
				moveKeyboard();
				checkMouseInput();
				break;
	case MELEEATK:
		getRigidBody()->velocity = { 0.0f, 0.0f };
		break;
	case RANGEATK:
		getRigidBody()->velocity = { 0.0f, 0.0f };
		break;
	case DIE:
		break;
	case NUMOFSTATES:
		break;
	default:
		break;
	}

	
	
}

void VictorVanHelsing::handleEventsController()
{
	const auto deadZone = 10000;
	switch (m_currentState)
	{
	case IDLE:
		getRigidBody()->velocity = { 0.0f, 0.0f };
		if (EventManager::Instance().getGameController(0)->LEFT_STICK_X[1] > deadZone ||
			EventManager::Instance().getGameController(0)->LEFT_STICK_X[1] < -deadZone ||
			EventManager::Instance().getGameController(0)->LEFT_STICK_Y[1] < -deadZone ||
			EventManager::Instance().getGameController(0)->LEFT_STICK_Y[1] > deadZone)
		{
			setState(RUNNING);
		}
		break;
	case RUNNING:
		if (EventManager::Instance().getGameController(0)->LEFT_STICK_X[1] < deadZone &&
			EventManager::Instance().getGameController(0)->LEFT_STICK_X[1] > -deadZone &&
			EventManager::Instance().getGameController(0)->LEFT_STICK_Y[1] > -deadZone &&
			EventManager::Instance().getGameController(0)->LEFT_STICK_Y[1] < deadZone)
		{
			setState(IDLE);
		}
		if (EventManager::Instance().getGameController(0)->LEFT_STICK_X[1] > deadZone)
		{
			getRigidBody()->velocity.x = getSpeed();
		}
		if (EventManager::Instance().getGameController(0)->LEFT_STICK_X[1] < -deadZone)
		{
			getRigidBody()->velocity.x = -getSpeed();
		}
		if (EventManager::Instance().getGameController(0)->LEFT_STICK_Y[1] < -deadZone)
		{
			getRigidBody()->velocity.y = getSpeed();
		}
		if (EventManager::Instance().getGameController(0)->LEFT_STICK_Y[1] > deadZone)
		{
			getRigidBody()->velocity.y = -getSpeed();
		}
		break;
	case MELEEATK:
		break;
	case RANGEATK:
		break;
	case DIE:
		break;
	case NUMOFSTATES:
		break;
	default:
		break;
	}
	
		//
		////Change Ability
		//if (EventManager::Instance().getGameController(0)->Arealeased())
		//{
		//	listPlayers[1]->changeAbility();
		//}
		////Use Current Ability
		//if (EventManager::Instance().getGameController(0)->Brealeased())
		//{
		//	listPlayers[1]->useCurrentAbility(2);
		//}
}

void VictorVanHelsing::slowEffect()
{
	if(isSlow)
	{
		isSlow = !isSlow;
		setSpeed(3.0f);
	}
	else
	{
		isSlow = !isSlow;
		setSpeed(1.0f);
	}
}

bool VictorVanHelsing::isVictorSlow()
{
	return isSlow;
}

void VictorVanHelsing::m_buildAnimations()
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


	m_pAnimations["idle"] = idle;

	Animation running = Animation();

	running.name = "running";
	running.frames.push_back(m_pSpriteSheet->getFrame("running1"));
	running.frames.push_back(m_pSpriteSheet->getFrame("running2"));
	running.frames.push_back(m_pSpriteSheet->getFrame("running3"));
	running.frames.push_back(m_pSpriteSheet->getFrame("running4"));
	running.frames.push_back(m_pSpriteSheet->getFrame("running5"));
	running.frames.push_back(m_pSpriteSheet->getFrame("running6"));
	running.frames.push_back(m_pSpriteSheet->getFrame("running7"));
	running.frames.push_back(m_pSpriteSheet->getFrame("running8"));


	m_pAnimations["running"] = running;

	Animation meleeatk = Animation();

	meleeatk.name = "meleeatk";
	meleeatk.frames.push_back(m_pSpriteSheet->getFrame("meleeatck1"));
	meleeatk.frames.push_back(m_pSpriteSheet->getFrame("meleeatck2"));
	meleeatk.frames.push_back(m_pSpriteSheet->getFrame("meleeatck3"));
	meleeatk.frames.push_back(m_pSpriteSheet->getFrame("meleeatck4"));
	meleeatk.frames.push_back(m_pSpriteSheet->getFrame("meleeatck5"));
	meleeatk.frames.push_back(m_pSpriteSheet->getFrame("meleeatck6"));
	meleeatk.frames.push_back(m_pSpriteSheet->getFrame("meleeatck7"));
	meleeatk.frames.push_back(m_pSpriteSheet->getFrame("meleeatck8"));


	m_pAnimations["meleeatk"] = meleeatk;

	Animation meleeatkA= Animation();

	meleeatkA.name = "meleeatkA";
	meleeatkA.frames.push_back(m_pSpriteSheet->getFrame("meleeatckA1"));
	meleeatkA.frames.push_back(m_pSpriteSheet->getFrame("meleeatckA2"));
	meleeatkA.frames.push_back(m_pSpriteSheet->getFrame("meleeatckA3"));
	meleeatkA.frames.push_back(m_pSpriteSheet->getFrame("meleeatckA4"));
	meleeatkA.frames.push_back(m_pSpriteSheet->getFrame("meleeatckA5"));
	meleeatkA.frames.push_back(m_pSpriteSheet->getFrame("meleeatckA6"));
	meleeatkA.frames.push_back(m_pSpriteSheet->getFrame("meleeatckA7"));
	meleeatkA.frames.push_back(m_pSpriteSheet->getFrame("meleeatckA8"));
	meleeatkA.setWidthAndHeight(300, 300);

	m_pAnimations["meleeatkA"] = meleeatkA;

	Animation rangeAtk = Animation();

	rangeAtk.name = "rangeAtk";
	rangeAtk.frames.push_back(m_pSpriteSheet->getFrame("rangeatk1"));
	rangeAtk.frames.push_back(m_pSpriteSheet->getFrame("rangeatk2"));
	rangeAtk.frames.push_back(m_pSpriteSheet->getFrame("rangeatk3"));
	rangeAtk.frames.push_back(m_pSpriteSheet->getFrame("rangeatk4"));
	rangeAtk.frames.push_back(m_pSpriteSheet->getFrame("rangeatk5"));
	rangeAtk.frames.push_back(m_pSpriteSheet->getFrame("rangeatk6"));
	rangeAtk.frames.push_back(m_pSpriteSheet->getFrame("rangeatk7"));
	rangeAtk.frames.push_back(m_pSpriteSheet->getFrame("rangeatk8"));

	m_pAnimations["rangeAtk"] = rangeAtk;



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
	if (getRigidBody()->isColliding)
	{
		if (TheTextureManager::Instance()->playAnimation("bloodsplat2", m_pAnimations["bloodsplat"],
			x, y, velocityAnimation, 0, 255, true))
		{
			getRigidBody()->isColliding = false;
			m_pAnimations["bloodsplat"].current_frame = 0;
		}
	}
}

bool VictorVanHelsing::isMoving()
{
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_A) ||
		EventManager::Instance().isKeyDown(SDL_SCANCODE_D) ||
		EventManager::Instance().isKeyDown(SDL_SCANCODE_W) ||
		EventManager::Instance().isKeyDown(SDL_SCANCODE_S))
	{
		return true;
	}

	return false;
}

void VictorVanHelsing::moveKeyboard()
{
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_A)/* && LVLMAN::Instance()->checkCollision(listPlayers[0], -playerSpeed, 0)*/)
	{
		setFlip(SDL_FLIP_HORIZONTAL);
		getRigidBody()->velocity.x = -getSpeed();
	}
	else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_D) /*&& LVLMAN::Instance()->checkCollision(listPlayers[0], playerSpeed, 0)*/)
	{
		setFlip(SDL_FLIP_NONE);
		getRigidBody()->velocity.x = getSpeed();
	}
	else {
		getRigidBody()->velocity.x = 0.0f;
	}
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_W) /*&& LVLMAN::Instance()->checkCollision(listPlayers[0], 0, -playerSpeed)*/)
	{
		getRigidBody()->velocity.y = -getSpeed();
	}
	else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_S) /*&& LVLMAN::Instance()->checkCollision(listPlayers[0], 0, playerSpeed)*/)
	{
		getRigidBody()->velocity.y = getSpeed();
	}
	else {
		getRigidBody()->velocity.y = 0.0f;
	}
}

bool VictorVanHelsing::checkMouseInput()
{
	//Change Ability
	if (EventManager::Instance().getMouseButton(2))
	{
		if (!click2MousePressed)
		{
			click2MousePressed = true;
			changeAbility();
		}
		return true;
	}
	if (!EventManager::Instance().getMouseButton(2))
	{
		click2MousePressed = false;
	}

	//Use Current Ability
	if (EventManager::Instance().getMouseButton(0))
	{
		if (!click1MousePressed)
		{
			click1MousePressed = true;
			if (m_currentAbility == 0)
			{
				setState(MELEEATK);
			}
			else
			{
				setState(RANGEATK);
			}
			useCurrentAbility(1);
			
		}
		return true;

	}
	if (!EventManager::Instance().getMouseButton(0))
	{
		click1MousePressed = false;
	}

	return false;
}


