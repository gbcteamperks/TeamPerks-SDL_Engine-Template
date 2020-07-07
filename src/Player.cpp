#include "Player.h"
#include "TextureManager.h"

Player::Player()
{
	// m_currentAnimationState=PLAYER_IDLE_RIGHT;
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

Player::~Player()
= default;

void Player::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	// draw the player according to animation state
	/*switch(m_currentAnimationState)
	{
	case PLAYER_IDLE_RIGHT:
		TheTextureManager::Instance()->playAnimation("spritesheet", m_pAnimations["idle"],
			x, y, 0.12f, 0, 255, true);
		break;
	case PLAYER_IDLE_LEFT:
		TheTextureManager::Instance()->playAnimation("spritesheet", m_pAnimations["idle"],
			x, y, 0.12f, 0, 255, true, SDL_FLIP_HORIZONTAL);
		break;
	case PLAYER_RUN_RIGHT:
		TheTextureManager::Instance()->playAnimation("spritesheet", m_pAnimations["run"],
			x, y, 0.25f, 0, 255, true);
		break;
	case PLAYER_RUN_LEFT:
		TheTextureManager::Instance()->playAnimation("spritesheet", m_pAnimations["run"],
			x, y, 0.25f, 0, 255, true, SDL_FLIP_HORIZONTAL);
		break;
	default:
		break;
	}*/
	
}

void Player::update()
{
	runHereThere();
}

void Player::clean()
{
}

void Player::setAnimationState(const PlayerAnimationState new_state)
{
	m_currentAnimationState = new_state;
}

void Player::setAnimation(const Animation& animation)
{
	m_pAnimations[animation.name] = animation;
}


void Player::m_buildAnimations()
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

void Player::runHereThere()
{
	if (m_playerFacingRight)
	{
		setAnimationState(PLAYER_RUN_RIGHT);
		getTransform()->position.x += 2;
		if (getTransform()->position.x >= (Config::SCREEN_WIDTH) - getWidth())
		{
			m_playerFacingRight = false;
		}
	}
	else if (!m_playerFacingRight)
	{
		setAnimationState(PLAYER_RUN_LEFT);
		getTransform()->position.x -= 2;
		if (getTransform()->position.x <= getWidth())
		{
			m_playerFacingRight = true;
		}
	}
	
	
}
