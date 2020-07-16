#include "MotherSpider.h"
#include "TextureManager.h"
#include "ExplosiveSpider.h"
#include "Orb.h"
#include "Game.h"
#include "LevelManager.h"
#include "MathManager.h"
#include "EnemyLifeBar.h"


MotherSpider::MotherSpider(glm::vec2 position)
{
	TheTextureManager::Instance()->loadSpriteSheet(
		"../Assets/sprites/spider.txt",
		"../Assets/sprites/spiderBig.png",
		"spiderBig");

	m_pSpriteSheet = TheTextureManager::Instance()->getSpriteSheet("spiderBig");
	m_pSpriteSheet->setWidthAndHeight(128, 128);
	
	// set frame width for the collision
	setWidth(64);

	// set frame height for the collision
	setHeight(64);
	setPosX(position.x);
	setPosY(position.y);

	getTransform()->position = position;
	getRigidBody()->velocity = glm::vec2(2.0f, 2.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(ENEMY);
	addAbility(new ExplosiveSpider());
	addAbility(new Orb());

	m_buildAnimations();
	m_Life = 150;
	m_lifeRedCounter = m_Life;
	UI.push_back(new EnemyLifeBar);
}

MotherSpider::~MotherSpider()
{
}

void MotherSpider::draw()
{
	Animate();

	for (auto s : UI)
	{
		s->draw(this->m_lifeRedCounter);
	}

}

void MotherSpider::update()
{
	setPosX(getTransform()->position.x);
	setPosY(getTransform()->position.y);

	checkCollisionWithLevel(LevelManager::Instance()->getObstacles());

	static int tempCounter = 0;
	if (tempCounter > 60) { //change state every # seconds
		
		if (m_randomAction == 0)
		{
			if (m_angle >= -45 && m_angle < 45)
			{
				m_currentAnimationState = PLAYER_RUN_RIGHT;
			}
			else if (m_angle >= 45 && m_angle < 135)
			{
				m_currentAnimationState = PLAYER_RUN_DOWN;
			}
			else if (m_angle >= 135 || m_angle < -135)
			{
				m_currentAnimationState = PLAYER_RUN_LEFT;
			}
			else if (m_angle >= -135 && m_angle < -45)
			{
				m_currentAnimationState = PLAYER_RUN_UP;
			}
			fleeBehaviour(PlayScene::listPlayers[0]);
			if (PlayScene::listPlayers.size() > 1)
			{
				fleeBehaviour(PlayScene::listPlayers[1]);
			}
			if (tempCounter > 120) {
				tempCounter = 0;
				m_randomAction = rand() % 2;
			}
		}
		else if (m_randomAction == 1)
		{
			useCurrentAbility();
			tempCounter = 0;
			m_randomAction = rand() % 2;
		}
	}
	tempCounter++;
	for (auto s : UI)
	{
		s->update(this);
	}

}

void MotherSpider::clean()
{
}


void MotherSpider::useCurrentAbility()
{
	int angle = MAMA::AngleBetweenPoints(this->getTransform()->position, PlayScene::listPlayers[0]->getTransform()->position);
	if (angle >= -45 && angle < 45)
	{
		m_currentAnimationState = ABILITY_RIGHT;
	}
	else if (angle >= 45 && angle < 135)
	{
		m_currentAnimationState = ABILITY_DOWN;
	}
	else if (angle >= 135 || angle < -135)
	{
		m_currentAnimationState = ABILITY_LEFT;
	}
	else if (angle >= -135 && angle < -45)
	{
		m_currentAnimationState = ABILITY_UP;
	}
	if (m_pListAbilities.size() > 0) {

		m_pListAbilities.front()->execute(getTransform()->position, angle, true); // to the left
		changeAbility();
	}
}

void MotherSpider::m_buildAnimations()
{
	

	Animation runupAnimation = Animation();

	runupAnimation.name = "run_up";

	runupAnimation.frames.push_back(m_pSpriteSheet->getFrame("spider_up5"));
	runupAnimation.frames.push_back(m_pSpriteSheet->getFrame("spider_up6"));
	runupAnimation.frames.push_back(m_pSpriteSheet->getFrame("spider_up7"));
	runupAnimation.frames.push_back(m_pSpriteSheet->getFrame("spider_up8"));
	runupAnimation.frames.push_back(m_pSpriteSheet->getFrame("spider_up9"));
	runupAnimation.frames.push_back(m_pSpriteSheet->getFrame("spider_up10"));

	m_pAnimations["run_up"] = runupAnimation;

	Animation runleftAnimation = Animation();

	runleftAnimation.name = "run_left";

	runleftAnimation.frames.push_back(m_pSpriteSheet->getFrame("spider_left5"));
	runleftAnimation.frames.push_back(m_pSpriteSheet->getFrame("spider_left6"));
	runleftAnimation.frames.push_back(m_pSpriteSheet->getFrame("spider_left7"));
	runleftAnimation.frames.push_back(m_pSpriteSheet->getFrame("spider_left8"));
	runleftAnimation.frames.push_back(m_pSpriteSheet->getFrame("spider_left9"));
	runleftAnimation.frames.push_back(m_pSpriteSheet->getFrame("spider_left10"));

	m_pAnimations["run_left"] = runleftAnimation;

	Animation rundownAnimation = Animation();

	rundownAnimation.name = "run_down";

	rundownAnimation.frames.push_back(m_pSpriteSheet->getFrame("spider_down5"));
	rundownAnimation.frames.push_back(m_pSpriteSheet->getFrame("spider_down6"));
	rundownAnimation.frames.push_back(m_pSpriteSheet->getFrame("spider_down7"));
	rundownAnimation.frames.push_back(m_pSpriteSheet->getFrame("spider_down8"));
	rundownAnimation.frames.push_back(m_pSpriteSheet->getFrame("spider_down9"));
	rundownAnimation.frames.push_back(m_pSpriteSheet->getFrame("spider_down10"));

	m_pAnimations["run_down"] = rundownAnimation;

	Animation runrightAnimation = Animation();

	runrightAnimation.name = "run_right";
	
	runrightAnimation.frames.push_back(m_pSpriteSheet->getFrame("spider_right5"));
	runrightAnimation.frames.push_back(m_pSpriteSheet->getFrame("spider_right6"));
	runrightAnimation.frames.push_back(m_pSpriteSheet->getFrame("spider_right7"));
	runrightAnimation.frames.push_back(m_pSpriteSheet->getFrame("spider_right8"));
	runrightAnimation.frames.push_back(m_pSpriteSheet->getFrame("spider_right9"));
	runrightAnimation.frames.push_back(m_pSpriteSheet->getFrame("spider_right10"));
	//runrightAnimation.setWidthAndHeight(64, 64);

	m_pAnimations["run_right"] = runrightAnimation;

	Animation biteupAnimation = Animation();

	biteupAnimation.name = "bite_up";
	biteupAnimation.frames.push_back(m_pSpriteSheet->getFrame("spider_up1"));
	biteupAnimation.frames.push_back(m_pSpriteSheet->getFrame("spider_up2"));
	biteupAnimation.frames.push_back(m_pSpriteSheet->getFrame("spider_up3"));
	biteupAnimation.frames.push_back(m_pSpriteSheet->getFrame("spider_up4"));
	

	m_pAnimations["bite_up"] = biteupAnimation;

	Animation biteleftAnimation = Animation();

	biteleftAnimation.name = "bite_left";
	biteleftAnimation.frames.push_back(m_pSpriteSheet->getFrame("spider_left1"));
	biteleftAnimation.frames.push_back(m_pSpriteSheet->getFrame("spider_left2"));
	biteleftAnimation.frames.push_back(m_pSpriteSheet->getFrame("spider_left3"));
	biteleftAnimation.frames.push_back(m_pSpriteSheet->getFrame("spider_left4"));


	m_pAnimations["bite_left"] = biteleftAnimation;

	Animation biterightAnimation = Animation();

	biterightAnimation.name = "bite_right";
	biterightAnimation.frames.push_back(m_pSpriteSheet->getFrame("spider_right1"));
	biterightAnimation.frames.push_back(m_pSpriteSheet->getFrame("spider_right2"));
	biterightAnimation.frames.push_back(m_pSpriteSheet->getFrame("spider_right3"));
	biterightAnimation.frames.push_back(m_pSpriteSheet->getFrame("spider_right4"));


	m_pAnimations["bite_right"] = biterightAnimation;

	Animation bitedownAnimation = Animation();

	bitedownAnimation.name = "bite_down";
	bitedownAnimation.frames.push_back(m_pSpriteSheet->getFrame("spider_down1"));
	bitedownAnimation.frames.push_back(m_pSpriteSheet->getFrame("spider_down2"));
	bitedownAnimation.frames.push_back(m_pSpriteSheet->getFrame("spider_down3"));
	bitedownAnimation.frames.push_back(m_pSpriteSheet->getFrame("spider_down4"));


	m_pAnimations["bite_down"] = bitedownAnimation;
}

void MotherSpider::Animate()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;
	float animationVelocity = 0.50f;
	// draw the player according to animation state
	switch (m_currentAnimationState)
	{
	case PLAYER_RUN_LEFT:
		TheTextureManager::Instance()->playAnimation("spiderBig", m_pAnimations["run_left"],
			x, y, animationVelocity, 0, 255, true);
		break;
	case PLAYER_RUN_UP:
		TheTextureManager::Instance()->playAnimation("spiderBig", m_pAnimations["run_up"],
			x, y, animationVelocity, 0, 255, true);
		break;
	case PLAYER_RUN_RIGHT:
		TheTextureManager::Instance()->playAnimation("spiderBig", m_pAnimations["run_right"],
			x, y, animationVelocity, 0, 255, true);
		break;
	case PLAYER_RUN_DOWN:
		TheTextureManager::Instance()->playAnimation("spiderBig", m_pAnimations["run_down"],
			x, y, animationVelocity, 0, 255, true);
		break;
	case ABILITY_LEFT:
		TheTextureManager::Instance()->playAnimation("spiderBig", m_pAnimations["bite_left"],
			x, y, animationVelocity, 0, 255, true);
		break;
	case ABILITY_UP:
		TheTextureManager::Instance()->playAnimation("spiderBig", m_pAnimations["bite_up"],
			x, y, animationVelocity, 0, 255, true);
		break;
	case ABILITY_RIGHT:
		TheTextureManager::Instance()->playAnimation("spiderBig", m_pAnimations["bite_right"],
			x, y, animationVelocity, 0, 255, true);
		break;
	case ABILITY_DOWN:
		TheTextureManager::Instance()->playAnimation("spiderBig", m_pAnimations["bite_down"],
			x, y, animationVelocity, 0, 255, true);
		break;
	default:
		break;
	}
}
