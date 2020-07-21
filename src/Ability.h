#pragma once
#ifndef __ABILITY__
#define __ABILITY__
#include "DisplayObject.h"
#include "StaticSprite.h"

class Ability : public DisplayObject {
public:
	Ability();
	virtual ~Ability();
	// Inherited via GameObject
	virtual void draw() override = 0;
	virtual void update() override = 0;
	virtual void clean() override = 0;

	virtual void execute(glm::vec2 position, int angle, bool enemyAbility) = 0;
	virtual void stop();
	virtual void sound();
	virtual void animation();
	virtual void pickable(glm::vec2 position) = 0;


	bool& getAbilityDone() { return m_abilityDone; }
	bool& IsRunning() { return m_running; }
	virtual Ability* getAbility() = 0;
	
protected:
	SpriteSheet* m_pSpriteSheetGem;
	std::unordered_map<std::string, Animation> m_pAnimations;
	bool m_abilityDone = false;
	int m_pickeableTimer;
	bool m_running = false;
	bool m_pickable = false;
	
	
};
#endif