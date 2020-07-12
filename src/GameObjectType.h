#pragma once
#ifndef __GAME_OBJECT_TYPE__
#define __GAME_OBJECT_TYPE__
enum GameObjectType {
	NONE = -1,
	PLAYERABILITY,
	ENEMYABILITY,
	PICKABLE,
	ABILITY,
	VICTOR,
	BOSS,
	CHARACTERS,
	PLAYER,
	ENEMY,
	BACKGROUND,
	STATICSPRITE,
	START_BUTTON,
	PLAY_BUTTON,
	RESTART_BUTTON,
	BACK_BUTTON,
	NEXT_BUTTON, 
	TILE,
	DOOR,
	NUM_OF_TYPES
	
};
#endif /* defined (__GAME_OBJECT_TYPE__) */