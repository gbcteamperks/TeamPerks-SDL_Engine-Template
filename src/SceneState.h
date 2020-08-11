#pragma once
#ifndef __SCENE_STATE__
#define __SCENE_STATE__
enum SceneState
{
	NO_SCENE = -1,
	START_SCENE,
	PLAY_SCENE,
	END_SCENE,
	TRANSITION_SCENE,
	VICTORY_SCENE,
	NUM_OF_SCENES = 5
};
#endif /* defined (__SCENE_STATE__) */