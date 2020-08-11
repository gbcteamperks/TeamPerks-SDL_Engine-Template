#include "King.h"
#include "EnemyLifeBar.h"
#include "PlayScene.h"
#include "MathManager.h"
#include "EventManager.h"
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
	m_distanceToPlayer = 0.0f;
	m_timeIDLE = 0.0f;
	m_timeWALKING = 0.0f;
	m_velocityIDLE = 120.0f;
	m_velocityAnimation = 1.0f;

	m_EnemyName = "KING";
	setType(BOSS);
	setKingState(KingState::IDLE);

	m_buildAnimations();
	m_Flip = SDL_FLIP_NONE;

	// Life
	m_maxLife = 1000.0f;
	m_pLife = m_maxLife;
	m_lifeRedCounter = m_pLife;
	UI.push_back(new EnemyLifeBar(this));


	m_ActionTree = new DecisionTree();
	BuildTree();
}

King::~King()
{
}

void King::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	switch (m_currentKingState)
	{
	case KingState::IDLE:
		if (TheTextureManager::Instance()->playAnimation("KingSpriteSheet", m_pAnimations["idle"],
			x, y, 1.0f * m_velocityAnimation, 0, 255, true, m_Flip))
		{
			//setState(RUNNING);
		}
		break;
	case KingState::ATTACK1:
		if (TheTextureManager::Instance()->playAnimation("KingSpriteSheet", m_pAnimations["attack"],
			x, y, 2.0f * m_velocityAnimation, 0, 255, true, m_Flip))
		{
			setKingState(KingState::ATTACK1SWING);
		}
		break;
	case KingState::ATTACK1SWING:
		if (TheTextureManager::Instance()->playAnimation("KingSpriteSheet", m_pAnimations["attackswing"],
			x, y, 2.0f* m_velocityAnimation, 0, 255, true, m_Flip))
		{
			setKingState(KingState::ATTACK1END);
		}
		break;
	case KingState::ATTACK1END:
		if (TheTextureManager::Instance()->playAnimation("KingSpriteSheet", m_pAnimations["attackend"],
			x, y, 1.0f * m_velocityAnimation, 0, 255, true, m_Flip))
		{
			setKingState(KingState::IDLE);
		}
		break;
	case KingState::TELEPORT:
		if (TheTextureManager::Instance()->playAnimation("KingSpriteSheet", m_pAnimations["teleport"],
			x, y, 5.0f* m_velocityAnimation, 0, 255, true, m_Flip))
		{
			setKingState(KingState::TELEPORTBACK);
			getTransform()->position = MAMA::LerpV(getTransform()->position, PlayScene::listPlayers[0]->getTransform()->position, 0.8f);
		}
		break;
	case KingState::TELEPORTBACK:
		if (TheTextureManager::Instance()->playAnimation("KingSpriteSheet", m_pAnimations["teleportback"],
			x, y, 5.0f * m_velocityAnimation, 0, 255, true, m_Flip))
		{
			setKingState(KingState::IDLE);
		}
		break;
	case KingState::ATTACK2:
		if (TheTextureManager::Instance()->playAnimation("KingSpriteSheet", m_pAnimations["attacktwo"],
			x, y, 2.0f * m_velocityAnimation, 0, 255, true, m_Flip))
		{
			setKingState(KingState::ATTACK2EXPLOSION);
		}
		break;
	case KingState::ATTACK2EXPLOSION:
		if (TheTextureManager::Instance()->playAnimation("KingSpriteSheet", m_pAnimations["attacktwoexp"],
			x, y, 0.1f * m_velocityAnimation, 0, 255, true, m_Flip))
		{
			setKingState(KingState::ATTACK2END);
		}
		break;
	case KingState::ATTACK2END:
		if (TheTextureManager::Instance()->playAnimation("KingSpriteSheet", m_pAnimations["attacktwoend"],
			x, y, 0.5f * m_velocityAnimation, 0, 255, true, m_Flip))
		{
			setKingState(KingState::IDLE);
		}
		break;
	case KingState::WALK:
		if (TheTextureManager::Instance()->playAnimation("KingSpriteSheet", m_pAnimations["walk"],
			x, y, 0.5f * m_velocityAnimation, 0, 255, true, m_Flip))
		{
			//setKingState(KingState::IDLE);
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

void King::update()
{
	if (getTransform()->position.x < PlayScene::listPlayers[0]->getTransform()->position.x)
		m_Flip = SDL_FLIP_NONE;
	else m_Flip = SDL_FLIP_HORIZONTAL;

	m_distanceToPlayer = MAMA::DistanceDouble(PlayScene::listPlayers[0]->getTransform()->position, getTransform()->position);
	switch (m_currentKingState)
	{
	case KingState::IDLE:
		if (m_pLife <= m_maxLife*0.5 && m_pLife >= m_maxLife*0.2)
		{
			m_velocityIDLE = 60;
			m_velocityAnimation = 1.5f;
		}
		else if (m_pLife < m_maxLife * 0.2)
		{
			m_velocityIDLE = 30;
			m_velocityAnimation = 2.0f;
		}

		if (m_timeIDLE > m_velocityIDLE)
		{
			m_ActionTree->solveTree();
			m_timeIDLE = 0;
		}
		m_timeIDLE++;
		break;
	case KingState::WALK:
		if (m_timeWALKING < 120)
		{
			updateCollisionBox(40, 60, 0, 0);
			Seeking();
			m_timeWALKING++;
		}
		else
		{
			m_timeWALKING = 0;
			setKingState(KingState::IDLE);
		}
		break;
	default:
		break;
	}
	for (auto ui : UI)
	{
		ui->update(this);
	}
}

void King::clean()
{
}

void King::bossAttack()
{
}

void King::setKingState(KingState state)
{
	m_currentKingState = state;
	float offSetX = 0;
	float offSetY = 0;
	switch (m_currentKingState)
	{
	case KingState::IDLE:
		m_timeIDLE = 0.0f;
		updateCollisionBox(40, 60, 0, 0);
		break;
	case KingState::ATTACK1:
		break;
	case KingState::ATTACK1SWING:
		if (m_Flip == SDL_FLIP_NONE)
		{
			offSetX = 40;
		}
		else
		{
			offSetX = -40;
		}

		updateCollisionBox(80, 100, offSetX, 0);
		break;
	case KingState::ATTACK1END:
		updateCollisionBox(40, 60, 0, 0);
		break;
	case KingState::ATTACK2:
		break;
	case KingState::ATTACK2EXPLOSION:
		updateCollisionBox(150, 150, 0, 0);
		break;
	case KingState::ATTACK2END:
		break;
	case KingState::TELEPORT:
		updateCollisionBox(0, 0, 0, 0);
		break;
	case KingState::TELEPORTBACK:
		//updateCollisionBox(40, 60, 0, 0);
		break;
	case KingState::WALK:
		break;
	case KingState::NUMBERSTATES:
		break;
	default:
		break;
	}
	
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

	Animation attack = Animation();

	attack.name = "attack";
	attack.frames.push_back(m_pSpriteSheet->getFrame("attack1"));
	attack.frames.push_back(m_pSpriteSheet->getFrame("attack2"));
	attack.frames.push_back(m_pSpriteSheet->getFrame("attack3"));
	attack.frames.push_back(m_pSpriteSheet->getFrame("attack4"));
	attack.frames.push_back(m_pSpriteSheet->getFrame("attack5"));
	attack.frames.push_back(m_pSpriteSheet->getFrame("attack6"));
	attack.frames.push_back(m_pSpriteSheet->getFrame("attack7"));
	attack.frames.push_back(m_pSpriteSheet->getFrame("attack8"));
	attack.frames.push_back(m_pSpriteSheet->getFrame("attack9"));
	attack.frames.push_back(m_pSpriteSheet->getFrame("attack10"));
	attack.frames.push_back(m_pSpriteSheet->getFrame("attack11"));
	attack.frames.push_back(m_pSpriteSheet->getFrame("attack12"));
	attack.frames.push_back(m_pSpriteSheet->getFrame("attack13"));
	attack.frames.push_back(m_pSpriteSheet->getFrame("attack14"));
	attack.frames.push_back(m_pSpriteSheet->getFrame("attack15"));
	attack.frames.push_back(m_pSpriteSheet->getFrame("attack16"));
	attack.frames.push_back(m_pSpriteSheet->getFrame("attack17"));
	attack.frames.push_back(m_pSpriteSheet->getFrame("attack18"));
	attack.frames.push_back(m_pSpriteSheet->getFrame("attack19"));

	m_pAnimations["attack"] = attack;

	Animation attackswing = Animation();

	attackswing.name = "attackswing";
	attackswing.frames.push_back(m_pSpriteSheet->getFrame("attackswing1"));
	attackswing.frames.push_back(m_pSpriteSheet->getFrame("attackswing2"));
	attackswing.frames.push_back(m_pSpriteSheet->getFrame("attackswing3"));
	attackswing.frames.push_back(m_pSpriteSheet->getFrame("attackswing4"));
	attackswing.frames.push_back(m_pSpriteSheet->getFrame("attackswing5"));
	attackswing.frames.push_back(m_pSpriteSheet->getFrame("attackswing6"));
	attackswing.frames.push_back(m_pSpriteSheet->getFrame("attackswing7"));
	attackswing.frames.push_back(m_pSpriteSheet->getFrame("attackswing8"));
	attackswing.frames.push_back(m_pSpriteSheet->getFrame("attackswing9"));
	attackswing.frames.push_back(m_pSpriteSheet->getFrame("attackswing10"));
	attackswing.frames.push_back(m_pSpriteSheet->getFrame("attackswing11"));
	attackswing.frames.push_back(m_pSpriteSheet->getFrame("attackswing12"));
	attackswing.frames.push_back(m_pSpriteSheet->getFrame("attackswing13"));
	attackswing.frames.push_back(m_pSpriteSheet->getFrame("attackswing14"));
	attackswing.frames.push_back(m_pSpriteSheet->getFrame("attackswing15"));
	attackswing.frames.push_back(m_pSpriteSheet->getFrame("attackswing16"));
	attackswing.frames.push_back(m_pSpriteSheet->getFrame("attackswing17"));
	attackswing.frames.push_back(m_pSpriteSheet->getFrame("attackswing18"));
	attackswing.frames.push_back(m_pSpriteSheet->getFrame("attackswing19"));
	attackswing.frames.push_back(m_pSpriteSheet->getFrame("attackswing20"));
	attackswing.frames.push_back(m_pSpriteSheet->getFrame("attackswing21"));
	attackswing.frames.push_back(m_pSpriteSheet->getFrame("attackswing22"));
	attackswing.frames.push_back(m_pSpriteSheet->getFrame("attackswing23"));
	attackswing.frames.push_back(m_pSpriteSheet->getFrame("attackswing24"));
	attackswing.frames.push_back(m_pSpriteSheet->getFrame("attackswing25"));
	attackswing.frames.push_back(m_pSpriteSheet->getFrame("attackswing26"));
	
	m_pAnimations["attackswing"] = attackswing;

	Animation attackend = Animation();

	attackend.name = "attackend";
	attackend.frames.push_back(m_pSpriteSheet->getFrame("attackend1"));
	attackend.frames.push_back(m_pSpriteSheet->getFrame("attackend2"));
	attackend.frames.push_back(m_pSpriteSheet->getFrame("attackend3"));
	attackend.frames.push_back(m_pSpriteSheet->getFrame("attackend4"));
	attackend.frames.push_back(m_pSpriteSheet->getFrame("attackend5"));
	attackend.frames.push_back(m_pSpriteSheet->getFrame("attackend6"));
	attackend.frames.push_back(m_pSpriteSheet->getFrame("attackend7"));
	attackend.frames.push_back(m_pSpriteSheet->getFrame("attackend8"));
	attackend.frames.push_back(m_pSpriteSheet->getFrame("attackend9"));
	attackend.frames.push_back(m_pSpriteSheet->getFrame("attackend10"));
	attackend.frames.push_back(m_pSpriteSheet->getFrame("attackend11"));
	attackend.frames.push_back(m_pSpriteSheet->getFrame("attackend12"));
	attackend.frames.push_back(m_pSpriteSheet->getFrame("attackend13"));
	
	m_pAnimations["attackend"] = attackend;

	Animation teleport = Animation();

	teleport.name = "teleport";
	teleport.frames.push_back(m_pSpriteSheet->getFrame("teleport1"));
	teleport.frames.push_back(m_pSpriteSheet->getFrame("teleport2"));
	teleport.frames.push_back(m_pSpriteSheet->getFrame("teleport3"));
	teleport.frames.push_back(m_pSpriteSheet->getFrame("teleport4"));
	teleport.frames.push_back(m_pSpriteSheet->getFrame("teleport5"));
	teleport.frames.push_back(m_pSpriteSheet->getFrame("teleport6"));
	teleport.frames.push_back(m_pSpriteSheet->getFrame("teleport7"));
	teleport.frames.push_back(m_pSpriteSheet->getFrame("teleport8"));
	teleport.frames.push_back(m_pSpriteSheet->getFrame("teleport9"));
	teleport.frames.push_back(m_pSpriteSheet->getFrame("teleport10"));
	teleport.frames.push_back(m_pSpriteSheet->getFrame("teleport11"));
	teleport.frames.push_back(m_pSpriteSheet->getFrame("teleport12"));
	teleport.frames.push_back(m_pSpriteSheet->getFrame("teleport13"));
	teleport.frames.push_back(m_pSpriteSheet->getFrame("teleport14"));
	teleport.frames.push_back(m_pSpriteSheet->getFrame("teleport15"));
	teleport.frames.push_back(m_pSpriteSheet->getFrame("teleport16"));
	teleport.frames.push_back(m_pSpriteSheet->getFrame("teleport17"));
	teleport.frames.push_back(m_pSpriteSheet->getFrame("teleport18"));
	teleport.frames.push_back(m_pSpriteSheet->getFrame("teleport19"));
	teleport.frames.push_back(m_pSpriteSheet->getFrame("teleport20"));
	teleport.frames.push_back(m_pSpriteSheet->getFrame("teleport21"));
	teleport.frames.push_back(m_pSpriteSheet->getFrame("teleport22"));
	teleport.frames.push_back(m_pSpriteSheet->getFrame("teleport23"));
	teleport.frames.push_back(m_pSpriteSheet->getFrame("teleport24"));
	teleport.frames.push_back(m_pSpriteSheet->getFrame("teleport25"));
	teleport.frames.push_back(m_pSpriteSheet->getFrame("teleport26"));
	teleport.frames.push_back(m_pSpriteSheet->getFrame("teleport27"));
	teleport.frames.push_back(m_pSpriteSheet->getFrame("teleport28"));
	teleport.frames.push_back(m_pSpriteSheet->getFrame("teleport29"));
	teleport.frames.push_back(m_pSpriteSheet->getFrame("teleport30"));
	teleport.frames.push_back(m_pSpriteSheet->getFrame("teleport31"));
	teleport.frames.push_back(m_pSpriteSheet->getFrame("teleport32"));
	teleport.frames.push_back(m_pSpriteSheet->getFrame("teleport33"));
	teleport.frames.push_back(m_pSpriteSheet->getFrame("teleport34"));
	teleport.frames.push_back(m_pSpriteSheet->getFrame("teleport35"));
	teleport.frames.push_back(m_pSpriteSheet->getFrame("teleport36"));
	teleport.frames.push_back(m_pSpriteSheet->getFrame("teleport37"));
	

	m_pAnimations["teleport"] = teleport;

	Animation teleportback = Animation();

	teleportback.name = "teleportback";
	teleportback.frames.push_back(m_pSpriteSheet->getFrame("teleportback1"));
	teleportback.frames.push_back(m_pSpriteSheet->getFrame("teleportback2"));
	teleportback.frames.push_back(m_pSpriteSheet->getFrame("teleportback3"));
	teleportback.frames.push_back(m_pSpriteSheet->getFrame("teleportback4"));
	teleportback.frames.push_back(m_pSpriteSheet->getFrame("teleportback5"));
	teleportback.frames.push_back(m_pSpriteSheet->getFrame("teleportback6"));
	teleportback.frames.push_back(m_pSpriteSheet->getFrame("teleportback7"));
	teleportback.frames.push_back(m_pSpriteSheet->getFrame("teleportback8"));
	teleportback.frames.push_back(m_pSpriteSheet->getFrame("teleportback9"));
	teleportback.frames.push_back(m_pSpriteSheet->getFrame("teleportback10"));
	teleportback.frames.push_back(m_pSpriteSheet->getFrame("teleportback11"));
	teleportback.frames.push_back(m_pSpriteSheet->getFrame("teleportback12"));
	teleportback.frames.push_back(m_pSpriteSheet->getFrame("teleportback13"));
	teleportback.frames.push_back(m_pSpriteSheet->getFrame("teleportback14"));
	teleportback.frames.push_back(m_pSpriteSheet->getFrame("teleportback15"));
	teleportback.frames.push_back(m_pSpriteSheet->getFrame("teleportback16"));
	teleportback.frames.push_back(m_pSpriteSheet->getFrame("teleportback17"));
	teleportback.frames.push_back(m_pSpriteSheet->getFrame("teleportback18"));
	teleportback.frames.push_back(m_pSpriteSheet->getFrame("teleportback19"));
	teleportback.frames.push_back(m_pSpriteSheet->getFrame("teleportback20"));
	teleportback.frames.push_back(m_pSpriteSheet->getFrame("teleportback21"));
	teleportback.frames.push_back(m_pSpriteSheet->getFrame("teleportback22"));
	teleportback.frames.push_back(m_pSpriteSheet->getFrame("teleportback23"));
	teleportback.frames.push_back(m_pSpriteSheet->getFrame("teleportback24"));
	teleportback.frames.push_back(m_pSpriteSheet->getFrame("teleportback25"));
	teleportback.frames.push_back(m_pSpriteSheet->getFrame("teleportback26"));
	teleportback.frames.push_back(m_pSpriteSheet->getFrame("teleportback27"));
	teleportback.frames.push_back(m_pSpriteSheet->getFrame("teleportback28"));
	teleportback.frames.push_back(m_pSpriteSheet->getFrame("teleportback29"));
	teleportback.frames.push_back(m_pSpriteSheet->getFrame("teleportback30"));
	teleportback.frames.push_back(m_pSpriteSheet->getFrame("teleportback31"));
	teleportback.frames.push_back(m_pSpriteSheet->getFrame("teleportback32"));
	teleportback.frames.push_back(m_pSpriteSheet->getFrame("teleportback33"));
	teleportback.frames.push_back(m_pSpriteSheet->getFrame("teleportback34"));
	teleportback.frames.push_back(m_pSpriteSheet->getFrame("teleportback35"));
	teleportback.frames.push_back(m_pSpriteSheet->getFrame("teleportback36"));
	teleportback.frames.push_back(m_pSpriteSheet->getFrame("teleportback37"));

	m_pAnimations["teleportback"] = teleportback;

	Animation attacktwo = Animation();

	attacktwo.name = "attacktwo";
	attacktwo.frames.push_back(m_pSpriteSheet->getFrame("attacktwo1"));
	attacktwo.frames.push_back(m_pSpriteSheet->getFrame("attacktwo2"));
	attacktwo.frames.push_back(m_pSpriteSheet->getFrame("attacktwo3"));
	attacktwo.frames.push_back(m_pSpriteSheet->getFrame("attacktwo4"));
	attacktwo.frames.push_back(m_pSpriteSheet->getFrame("attacktwo5"));
	attacktwo.frames.push_back(m_pSpriteSheet->getFrame("attacktwo6"));
	attacktwo.frames.push_back(m_pSpriteSheet->getFrame("attacktwo7"));
	attacktwo.frames.push_back(m_pSpriteSheet->getFrame("attacktwo8"));
	attacktwo.frames.push_back(m_pSpriteSheet->getFrame("attacktwo9"));
	attacktwo.frames.push_back(m_pSpriteSheet->getFrame("attacktwo10"));
	attacktwo.frames.push_back(m_pSpriteSheet->getFrame("attacktwo11"));
	attacktwo.frames.push_back(m_pSpriteSheet->getFrame("attacktwo12"));
	attacktwo.frames.push_back(m_pSpriteSheet->getFrame("attacktwo13"));
	attacktwo.frames.push_back(m_pSpriteSheet->getFrame("attacktwo14"));
	attacktwo.frames.push_back(m_pSpriteSheet->getFrame("attacktwo15"));
	attacktwo.frames.push_back(m_pSpriteSheet->getFrame("attacktwo16"));
	attacktwo.frames.push_back(m_pSpriteSheet->getFrame("attacktwo17"));
	attacktwo.frames.push_back(m_pSpriteSheet->getFrame("attacktwo18"));

	m_pAnimations["attacktwo"] = attacktwo;

	Animation attacktwoexp = Animation();

	attacktwoexp.name = "attacktwoexp";
	attacktwoexp.frames.push_back(m_pSpriteSheet->getFrame("attacktwoexp1"));
	attacktwoexp.frames.push_back(m_pSpriteSheet->getFrame("attacktwoexp2"));
	attacktwoexp.frames.push_back(m_pSpriteSheet->getFrame("attacktwoexp3"));
	attacktwoexp.frames.push_back(m_pSpriteSheet->getFrame("attacktwoexp4"));
	attacktwoexp.setWidthAndHeight(600, 600);
	m_pAnimations["attacktwoexp"] = attacktwoexp;

	Animation attacktwoend = Animation();

	attacktwoend.name = "attacktwoend";
	attacktwoend.frames.push_back(m_pSpriteSheet->getFrame("attacktwoend1"));
	attacktwoend.frames.push_back(m_pSpriteSheet->getFrame("attacktwoend2"));
	attacktwoend.frames.push_back(m_pSpriteSheet->getFrame("attacktwoend3"));
	attacktwoend.frames.push_back(m_pSpriteSheet->getFrame("attacktwoend4"));
	attacktwoend.frames.push_back(m_pSpriteSheet->getFrame("attacktwoend5"));
	attacktwoend.frames.push_back(m_pSpriteSheet->getFrame("attacktwoend6"));
	attacktwoend.frames.push_back(m_pSpriteSheet->getFrame("attacktwoend7"));
	attacktwoend.frames.push_back(m_pSpriteSheet->getFrame("attacktwoend8"));

	m_pAnimations["attacktwoend"] = attacktwoend;

	Animation walk = Animation();

	walk.name = "walk";
	walk.frames.push_back(m_pSpriteSheet->getFrame("walk1"));
	walk.frames.push_back(m_pSpriteSheet->getFrame("walk2"));
	walk.frames.push_back(m_pSpriteSheet->getFrame("walk3"));
	walk.frames.push_back(m_pSpriteSheet->getFrame("walk4"));
	walk.frames.push_back(m_pSpriteSheet->getFrame("walk5"));
	walk.frames.push_back(m_pSpriteSheet->getFrame("walk6"));
	walk.frames.push_back(m_pSpriteSheet->getFrame("walk7"));
	walk.frames.push_back(m_pSpriteSheet->getFrame("walk8"));

	m_pAnimations["walk"] = walk;
}


void King::Seeking()
{
	double direction = MAMA::AngleBetweenPoints(getTransform()->position, PlayScene::listPlayers[0]->getTransform()->position)*M_PI/180;
	glm::vec2 unitDir = glm::vec2(cos(direction), sin(direction));
	float speed = 2.0f * m_velocityAnimation;
	glm::vec2 desired = unitDir * speed;
	float seekingFactor = 0.2f * m_velocityAnimation;
	getRigidBody()->velocity.x = MAMA::LerpD(getRigidBody()->velocity.x, desired.x, seekingFactor);
	getRigidBody()->velocity.y = MAMA::LerpD(getRigidBody()->velocity.y, desired.y, seekingFactor);
	getTransform()->position += getRigidBody()->velocity;
}

void King::updateCollisionBox(float w, float h, float offSetX, float offSetY)
{
	setPosX(getTransform()->position.x - w*0.5 + offSetX);
	setPosY(getTransform()->position.y - h*0.5 + offSetY);
	setWidth(w);
	setHeight(h);
}

void King::BuildTree()
{
	TreeNode* teleport = new TreeNode();
	teleport->Action = [this]() {
		//std::cout << "Teleporting" << std::endl; 
		setKingState(KingState::TELEPORT);
	};

	TreeNode* walk = new TreeNode();
	walk->Action = [this]() {
		//std::cout << "Walking" << std::endl; 
		setKingState(KingState::WALK);
	};

	TreeNode* attack1 = new TreeNode();
	attack1->Action = [this]() {
		//std::cout << "Attack Number 1" << std::endl;
		setKingState(KingState::ATTACK1);
	};

	TreeNode* attack2 = new TreeNode();
	attack2->Action = [this]() {
		//std::cout << "Attack Number 2" << std::endl;
		setKingState(KingState::ATTACK2);
	};

	TreeNode* tossAcoin1 = new TreeNode();
	tossAcoin1->Condition = []() { 
		if (rand() % 2 == 0)
			return true;
		return false;
	};
	tossAcoin1->Right = walk;
	tossAcoin1->Left = teleport;

	TreeNode* tossAcoin2 = new TreeNode();
	tossAcoin2->Condition = []() {
		if (rand() % 2 == 0) 
			return true; 
		return false;
	};
	tossAcoin2->Right = attack1;
	tossAcoin2->Left = attack2;

	TreeNode* root = new TreeNode();
	root->Condition = [this]() {
		if (m_distanceToPlayer < 150)
			return true; 
		return false;
};
	root->Action = [this]() {
		//std::cout << "Distance is "<< m_distanceToPlayer << std::endl; 
	};
	root->Right = tossAcoin2;
	root->Left = tossAcoin1;

	m_ActionTree->setRoot(root);
}
