#pragma once
class SpawnEnemiesManager {
public:
	static void level1();
	static void level2();
	static void level1Boss();
	static void level2Boss();
	static void level3Boss();
	static int randomNum;
	SpawnEnemiesManager();
	static bool bossSummoned;
};