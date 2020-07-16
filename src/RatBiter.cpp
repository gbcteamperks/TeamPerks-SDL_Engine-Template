#include "RatBiter.h"

RatBiter::RatBiter()
{
	//m_velocity = 6;
	m_running = false;
	m_damage = 40;

	TextureManager::Instance()->load("../Assets/sprites/rat_small.png", "ratsmall");

	getRigidBody()->isColliding = false;
	timerDie = (40 + rand() % 91);
	setType(ENEMYABILITY);
}


RatBiter::RatBiter(glm::vec2 position, bool running, int angle, bool pickeable, bool enemyAbility)
{
	//spawnable rats
	//TheTextureManager::Instance()->load("../Assets/Sprites/rat_small.png", "rat_small");
	TextureManager::Instance()->loadSpriteSheet(
		"../Assets/sprites/rat_small.txt",
		"../Assets/sprites/rat_small.png",
		"ratsmall"
	);

	m_pSpriteSheet = TextureManager::Instance()->getSpriteSheet("ratsmall");
	m_pSpriteSheet->setWidthAndHeight(64, 64);
	m_angle = angle;
	m_running = running;
	m_pickable = pickeable;
	m_damage = 0;

	m_currentAnimationState = PLAYER_RUN_UP;
	m_buildAnimations();

	getTransform()->position = position;
	getRigidBody()->velocity += 2.0;
	glm::vec2 direction = { cos(m_angle * M_PI / 180.0) , sin(m_angle * M_PI / 180.0) };
	getRigidBody()->velocity *= direction;
	

	setWidth(30);//for collision
	setHeight(30);
	getRigidBody()->isColliding = false;
	if (m_pickable) {
		setType(PICKABLE);
	}
	else {
		getTransform()->position += (70.0f * direction);
		if (enemyAbility) {
			setType(ENEMYABILITY);
		}
		else {
			setType(PLAYERABILITY);
		}
	}
	timerDie = (40 + rand() % 91);
	start();
}

void RatBiter::update()
{
	if (m_running && !m_pickable)
	{
		if (walkTimer < 120) {
			getTransform()->position += getRigidBody()->velocity;
		}
		walkTimer++;
	}
}

void RatBiter::draw()
{
	if (m_running && !m_pickable)
	{
		if (timer++ == timerDie)
		{
			m_currentAnimationState = PLAYER_RUN_UP;
			die = true;
			Animate();
			//timer = 0;
		}
		else
		{
			m_currentAnimationState = PLAYER_RUN_UP;
			Animate();
		}
	}
	else if (m_running && m_pickable)
	{
		Animate();
	}
}

void RatBiter::clean()
{
}

void RatBiter::start()
{
	if (m_pickable)
	{
		sound();
	}
}

void RatBiter::execute(glm::vec2 position, int angle, bool enemyAbility)
{
	Game::Instance()->getCurrentScene()->addChild(new RatBiter(position, true, angle, false,enemyAbility));
	SoundManager::Instance().playSound("Rat");
}

void RatBiter::stop()
{
	m_running = false;
}

void RatBiter::sound()
{
	//add sound
	if (m_running)
	{
		//play sound here.

	}
}


void RatBiter::pickable(glm::vec2 position)
{
	Game::Instance()->getCurrentScene()->addChild(new RatBiter(position, true, 0, true,false));
}


void RatBiter::animation()
{
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;
	float animationVelocity = 0.50f;

	TheTextureManager::Instance()->playAnimation("ratsmall", m_pAnimations["ratsmall_down"], x, y, animationVelocity, 0, 255, true);
}


void RatBiter::m_buildAnimations()
{
	Animation down = Animation();
	down.name = "ratsmall_down";
	down.frames.push_back(m_pSpriteSheet->getFrame("down-1"));
	down.frames.push_back(m_pSpriteSheet->getFrame("down-2"));
	down.frames.push_back(m_pSpriteSheet->getFrame("down-3"));
	down.frames.push_back(m_pSpriteSheet->getFrame("down-4"));
	m_pAnimations["ratsmall_down"] = down;

	Animation downAttack = Animation();
	downAttack.name = "ratsmall_downattack";
	downAttack.frames.push_back(m_pSpriteSheet->getFrame("downattack-1"));
	downAttack.frames.push_back(m_pSpriteSheet->getFrame("downattack-2"));
	downAttack.frames.push_back(m_pSpriteSheet->getFrame("downattack-3"));
	m_pAnimations["ratsmall_downattack"] = downAttack;


	Animation right = Animation();
	right.name = "ratsmall_right";
	right.frames.push_back(m_pSpriteSheet->getFrame("right-1"));
	right.frames.push_back(m_pSpriteSheet->getFrame("right-2"));
	right.frames.push_back(m_pSpriteSheet->getFrame("right-3"));
	right.frames.push_back(m_pSpriteSheet->getFrame("right-4"));
	m_pAnimations["ratsmall_right"] = right;

	Animation rightAttack = Animation();
	rightAttack.name = "ratsmall_rightattack";
	rightAttack.frames.push_back(m_pSpriteSheet->getFrame("rightattack-1"));
	rightAttack.frames.push_back(m_pSpriteSheet->getFrame("rightattack-2"));
	rightAttack.frames.push_back(m_pSpriteSheet->getFrame("rightattack-3"));
	m_pAnimations["ratsmall_rightattack"] = rightAttack;


	Animation up = Animation();
	up.name = "ratsmall_up";
	up.frames.push_back(m_pSpriteSheet->getFrame("up-1"));
	up.frames.push_back(m_pSpriteSheet->getFrame("up-2"));
	up.frames.push_back(m_pSpriteSheet->getFrame("up-3"));
	up.frames.push_back(m_pSpriteSheet->getFrame("up-4"));
	m_pAnimations["ratsmall_up"] = up;


	Animation upAttack = Animation();
	upAttack.name = "ratsmall_upattack";
	upAttack.frames.push_back(m_pSpriteSheet->getFrame("upattack-1"));
	upAttack.frames.push_back(m_pSpriteSheet->getFrame("upattack-2"));
	upAttack.frames.push_back(m_pSpriteSheet->getFrame("upattack-3"));
	m_pAnimations["ratsmall_upattack"] = upAttack;


	Animation left = Animation();
	left.name = "ratsmall_left";
	left.frames.push_back(m_pSpriteSheet->getFrame("left-1"));
	left.frames.push_back(m_pSpriteSheet->getFrame("left-2"));
	left.frames.push_back(m_pSpriteSheet->getFrame("left-3"));
	left.frames.push_back(m_pSpriteSheet->getFrame("left-4"));
	m_pAnimations["ratsmall_left"] = left;


	Animation leftAttack = Animation();
	leftAttack.name = "ratsmall_leftattack";
	leftAttack.frames.push_back(m_pSpriteSheet->getFrame("leftattack-1"));
	leftAttack.frames.push_back(m_pSpriteSheet->getFrame("leftattack-2"));
	leftAttack.frames.push_back(m_pSpriteSheet->getFrame("leftattack-3"));
	m_pAnimations["ratsmall_leftattack"] = leftAttack;


	//dead
	Animation deaddown = Animation();
	deaddown.name = "ratsmall_deaddown";
	deaddown.frames.push_back(m_pSpriteSheet->getFrame("deaddown-1"));
	m_pAnimations["ratsmall_deaddown"] = deaddown;

	Animation deadup = Animation();
	deadup.name = "ratsmall_deadup";
	deadup.frames.push_back(m_pSpriteSheet->getFrame("deadup-1"));
	m_pAnimations["ratsmall_deadup"] = deadup;

	Animation deadright = Animation();
	deadright.name = "ratsmall_deadright";
	deadright.frames.push_back(m_pSpriteSheet->getFrame("deadright-1"));
	m_pAnimations["ratsmall_deadright"] = deadright;

	Animation deadleft = Animation();
	deadleft.name = "ratsmall_deadleft";
	deadleft.frames.push_back(m_pSpriteSheet->getFrame("deadleft-1"));
	m_pAnimations["ratsmall_deadleft"] = deadleft;
}

void RatBiter::Animate()
{
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;
	float animationVelocity = 0.40f;


	switch (m_currentAnimationState)
	{
	case PLAYER_RUN_UP:
		TheTextureManager::Instance()->playAnimation("ratsmall", m_pAnimations["ratsmall_down"], x, y, animationVelocity, 0, 255, true);
		if (die == true)
		{
			m_abilityDone = true;
		}
		break;


	default:
		break;
	}
}



RatBiter::~RatBiter()
{
}