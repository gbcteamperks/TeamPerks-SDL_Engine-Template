#include "ExplosiveSpider.h"

ExplosiveSpider::ExplosiveSpider()
{
	//m_velocity = 6;
	m_running = false;
	m_damage = 0;

	//getTransform()->position = glm::vec2(0.0f,0.0f);
	TheTextureManager::Instance()->load("../Assets/Sprites/spiderExplode.png", "spiderExplode");

	getRigidBody()->isColliding = false;
	//getTransform()->position = glm::vec2(100.0f, 100.0f);

	setType(PROJECTILE);
}
ExplosiveSpider::ExplosiveSpider(glm::vec2 position, bool running, int angle, bool pickeable)
{
	TheTextureManager::Instance()->loadSpriteSheet(
		"../Assets/sprites/spider.txt",
		"../Assets/sprites/spiderExplode.png",
		"spiderExplode");
	//load explosion
	TheTextureManager::Instance()->loadSpriteSheet(
		"../Assets/sprites/ExplosionSpider.txt",
		"../Assets/sprites/explosionSpider.png",
		"explosionSpider");

	m_pSpriteSheet = TheTextureManager::Instance()->getSpriteSheet("spiderExplode");

	m_pSpriteSheetExplosion = TheTextureManager::Instance()->getSpriteSheet("explosionSpider");
	m_pSpriteSheetExplosion->setWidthAndHeight(64, 64);
	m_angle = angle;
	m_running = running;
	m_pickable = pickeable;
	m_damage = 0;

	//animation
	m_currentAnimationState = PLAYER_RUN_LEFT;
	m_buildAnimations();

	getTransform()->position = position;
	getRigidBody()->velocity += 2.0;
	glm::vec2 direction = { cos(m_angle * M_PI / 180.0) , sin(m_angle * M_PI / 180.0) };
	getRigidBody()->velocity *= direction;
	getTransform()->position += (70.0f * direction); 

	setWidth(30);//for collision
	setHeight(30);
	getRigidBody()->isColliding = false;
	if (m_pickable) {
		setType(PICKABLE);
	}
	else {
		setType(PROJECTILE);
	}
	start();
}

ExplosiveSpider::~ExplosiveSpider()
{
}

void ExplosiveSpider::update()
{
	if (m_running && !m_pickable)
	{
		if (walkTimer < 120) {
			getTransform()->position += getRigidBody()->velocity;
		}
		walkTimer++;
	}
}

void ExplosiveSpider::draw()
{
	if (m_running && !m_pickable)
	{
		if (explosionTimer < 240) {
			animation();
		}
		else {
			AnimateDeath();
		}
		explosionTimer++;
	}
	else if (m_running && m_pickable)
	{
		animation();
	}
}

void ExplosiveSpider::clean()
{

}

void ExplosiveSpider::start()
{
	if (m_pickable)
	{
		sound();
		//animation();
	}

}

void ExplosiveSpider::execute(glm::vec2 position, int angle)
{
	//getTransform()->position = position;
	Game::Instance()->getCurrentScene()->addChild(new ExplosiveSpider(position, true, angle, false));

}

void ExplosiveSpider::stop()
{
	m_running = false;
}

void ExplosiveSpider::sound()
{
	if (m_running) {

	}
}

void ExplosiveSpider::animation()
{
	
		// alias for x and y
		const auto x = getTransform()->position.x;
		const auto y = getTransform()->position.y;
		float animationVelocity = 0.50f;
		// draw the player according to animation state
		switch (m_currentAnimationState)
		{
		case PLAYER_RUN_LEFT:
			TheTextureManager::Instance()->playAnimation("spiderExplode", m_pAnimations["run_left"],
				x, y, animationVelocity, 0, 255, true);
			break;
		case PLAYER_RUN_UP:
			TheTextureManager::Instance()->playAnimation("spiderExplode", m_pAnimations["run_up"],
				x, y, animationVelocity, 0, 255, true);
			break;
		case PLAYER_RUN_RIGHT:
			TheTextureManager::Instance()->playAnimation("spiderExplode", m_pAnimations["run_right"],
				x, y, animationVelocity, 0, 255, true);
			break;
		case PLAYER_RUN_DOWN:
			TheTextureManager::Instance()->playAnimation("spiderExplode", m_pAnimations["run_down"],
				x, y, animationVelocity, 0, 255, true);
			break;
		case ABILITY_LEFT:
			TheTextureManager::Instance()->playAnimation("spiderExplode", m_pAnimations["bite_left"],
				x, y, animationVelocity, 0, 255, true);
			break;
		case ABILITY_UP:
			TheTextureManager::Instance()->playAnimation("spiderExplode", m_pAnimations["bite_up"],
				x, y, animationVelocity, 0, 255, true);
			break;
		case ABILITY_RIGHT:
			TheTextureManager::Instance()->playAnimation("spiderExplode", m_pAnimations["bite_right"],
				x, y, animationVelocity, 0, 255, true);
			break;
		case ABILITY_DOWN:
			TheTextureManager::Instance()->playAnimation("spiderExplode", m_pAnimations["bite_down"],
				x, y, animationVelocity, 0, 255, true);
			break;
		default:
			break;
		}
	
}
void ExplosiveSpider::m_buildAnimations()
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

	//Explosion
	Animation Explosion = Animation();

	Explosion.name = "Explosion";
	Explosion.frames.push_back(m_pSpriteSheetExplosion->getFrame("explosion-1"));
	Explosion.frames.push_back(m_pSpriteSheetExplosion->getFrame("explosion-2"));
	Explosion.frames.push_back(m_pSpriteSheetExplosion->getFrame("explosion-3"));
	Explosion.frames.push_back(m_pSpriteSheetExplosion->getFrame("explosion-4"));


	m_pAnimations["Explosion"] = Explosion;
}

void ExplosiveSpider::AnimateDeath()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;
	float animationVelocity = 0.50f;
	if (TheTextureManager::Instance()->playAnimation("explosionSpider", m_pAnimations["Explosion"],
		x, y, animationVelocity, 0, 255, true))
	{
		m_abilityDone = true;
	}

}
void ExplosiveSpider::pickable(glm::vec2 position)
{
	Game::Instance()->getCurrentScene()->addChild(new ExplosiveSpider(position, true, 0, true));
}

