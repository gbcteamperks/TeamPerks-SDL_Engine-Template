#include "EnemyWizard.h"
#include "EnemyLifeBar.h"
#include "Fireball.h"
#include "MathManager.h"

EnemyWizard::EnemyWizard(glm::vec2 position) 
{
	TheTextureManager::Instance()->loadSpriteSheet(
		"../Assets/sprites/wizardSpriteSheet.txt",
		"../Assets/sprites/wizardSpriteSheet.png",
		"wizardSpriteSheet");

	m_pSpriteSheet = TheTextureManager::Instance()->getSpriteSheet("wizardSpriteSheet");

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
	addAbility(new Fireball());
	setType(ENEMY);
	setState(State::IDLE);
	RightCicle = rand() % 2;
	m_buildAnimations();
	m_Flip = SDL_FLIP_NONE;
	// Life
	m_pLife = 100;
	m_lifeRedCounter = m_pLife;
	UI.push_back(new EnemyLifeBar(this));

	m_patrolNodes = new CircleList();
	setNodes();
}

EnemyWizard::~EnemyWizard()
= default;

void EnemyWizard::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	
	// draw the player according to animation state
	switch (m_currentState)
	{
	case IDLE:
		if (TheTextureManager::Instance()->playAnimation("wizardSpriteSheet", m_pAnimations["idle"],
			x, y, 0.25f, 0, 255, true, m_Flip))
		{
			setState(RUNNING);
		}
		break;
	case RUNNING:
		if (getRigidBody()->velocity.x > 0)
			m_Flip = SDL_FLIP_HORIZONTAL;
		else
			m_Flip = SDL_FLIP_NONE;
		TheTextureManager::Instance()->playAnimation("wizardSpriteSheet", m_pAnimations["move"],
			x, y, 0.25f, 0, 255, true, m_Flip);
		break;
	case RANGEATK:
		if (TheTextureManager::Instance()->playAnimation("wizardSpriteSheet", m_pAnimations["attack"],
			x, y, 0.25f, 0, 255, true, m_Flip))
		{
			setState(RANGEATK2);
			bossAttack();
		}
		break;
	case RANGEATK2:
		if (TheTextureManager::Instance()->playAnimation("wizardSpriteSheet", m_pAnimations["attackback"],
			x, y, 0.25f, 0, 255, true, m_Flip))
		{
			setState(State::IDLE);
		}
		break;
	default:
		break;
	}
	animateBloodSplat();
	for (auto s : UI)
	{
		s->draw(this->m_lifeRedCounter);
	}

}

void EnemyWizard::update()
{
	

	switch (m_currentState)
	{
	case IDLE:
		break;
	case RUNNING:
		PatrolWtNodes();
		Move(getRigidBody()->velocity.x, getRigidBody()->velocity.y);
		break;
	case RANGEATK:
		break;
	default:
		break;
	}
	for (auto s : UI)
	{
		s->update(this);
	}

}

void EnemyWizard::clean()
{
}

void EnemyWizard::bossAttack()
{
	m_angle = MAMA::AngleBetweenPoints(this->getTransform()->position, PlayScene::listPlayers[0]->getTransform()->position);
	m_pListAbilities.front()->execute(getTransform()->position, m_angle, true); // to the left
}

void EnemyWizard::setNodes()
{
	float iValue = 0.1f;
	float fValue = 0.9f;
	m_patrolNodes->add(new Node(Config::SCREEN_WIDTH* iValue, Config::SCREEN_HEIGHT* iValue));
	m_patrolNodes->add(new Node(Config::SCREEN_WIDTH * iValue, Config::SCREEN_HEIGHT * fValue));
	m_patrolNodes->add(new Node(Config::SCREEN_WIDTH * fValue, Config::SCREEN_HEIGHT * fValue));
	m_patrolNodes->add(new Node(Config::SCREEN_WIDTH * fValue, Config::SCREEN_HEIGHT * iValue));
	initialPosPatrol = rand() % 4;
	for (int i = 0; i < initialPosPatrol; i++)
		m_patrolNodes->Next();
}

void EnemyWizard::PatrolWtNodes()
{
	if (SeekingNode(m_patrolNodes->Current()->data[0], m_patrolNodes->Current()->data[1]))
	{
		if (PlayScene::listPlayers[0]->getTransform()->position.x - getTransform()->position.x > 0)
			m_Flip = SDL_FLIP_HORIZONTAL;
		else
			m_Flip = SDL_FLIP_NONE;
			

		setState(RANGEATK);
		if (RightCicle)
			m_patrolNodes->Next();
		else
			m_patrolNodes->Prev();
	}
}

bool EnemyWizard::SeekingNode(int x, int y)
{
	float speed = 2.0f;
	float angle = MAMA::AngleBetweenPoints(getTransform()->position, glm::vec2(x,y))*M_PI/180;
	glm::vec2 desired = glm::vec2(cos(angle), sin(angle)) * speed;
	float seekingForce = 1.0f;
	getRigidBody()->velocity.y = MAMA::LerpD(getRigidBody()->velocity.y, desired.y, seekingForce);
	getRigidBody()->velocity.x = MAMA::LerpD(getRigidBody()->velocity.x, desired.x, seekingForce);

	glm::vec2 distance = MAMA::Distance(getTransform()->position, glm::vec2(x, y));
	if (abs(distance.x) < 20 && abs(distance.y) < 20)
	{
		return true;
	}
	return false;
}

void EnemyWizard::m_buildAnimations()
{
	Animation idle = Animation();

	idle.name = "idle";
	idle.frames.push_back(m_pSpriteSheet->getFrame("idle1"));
	idle.frames.push_back(m_pSpriteSheet->getFrame("idle2"));
	idle.frames.push_back(m_pSpriteSheet->getFrame("idle3"));
	idle.frames.push_back(m_pSpriteSheet->getFrame("idle4"));
	idle.frames.push_back(m_pSpriteSheet->getFrame("idle5"));
	idle.frames.push_back(m_pSpriteSheet->getFrame("idle6"));

	m_pAnimations["idle"] = idle;

	Animation attack = Animation();

	attack.name = "attack";
	attack.frames.push_back(m_pSpriteSheet->getFrame("attack1"));
	attack.frames.push_back(m_pSpriteSheet->getFrame("attack2"));
	attack.frames.push_back(m_pSpriteSheet->getFrame("attack3"));
	attack.frames.push_back(m_pSpriteSheet->getFrame("attack4"));
	attack.frames.push_back(m_pSpriteSheet->getFrame("attack5"));
	attack.frames.push_back(m_pSpriteSheet->getFrame("attack6"));


	m_pAnimations["attack"] = attack;

	Animation attackback = Animation();

	attackback.name = "attackback";
	attackback.frames.push_back(m_pSpriteSheet->getFrame("attackback1"));
	attackback.frames.push_back(m_pSpriteSheet->getFrame("attackback2"));
	attackback.frames.push_back(m_pSpriteSheet->getFrame("attackback3"));
	attackback.frames.push_back(m_pSpriteSheet->getFrame("attackback4"));
	attackback.frames.push_back(m_pSpriteSheet->getFrame("attackback5"));

	m_pAnimations["attackback"] = attackback;

	Animation move = Animation();

	move.name = "move";
	move.frames.push_back(m_pSpriteSheet->getFrame("move1"));
	move.frames.push_back(m_pSpriteSheet->getFrame("move2"));
	move.frames.push_back(m_pSpriteSheet->getFrame("move3"));
	move.frames.push_back(m_pSpriteSheet->getFrame("move4"));

	m_pAnimations["move"] = move;
}

