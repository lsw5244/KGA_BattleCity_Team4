#pragma once
#include "Config.h"


class EnemyTankManager;
class EnemyTankFactory;
class AmmoManager;
class PlayerTank;
class Image;
class StageManager
{
private:
	AmmoManager* ammoManager;
	PlayerTank* playerTank;
	EnemyTankManager* enemyTankManager;
	EnemyTankFactory* enemyTankFactory[4];
	enum class EnemyTankSpawnInfo {
		NormalTankSpawm,
		FastTankSpawm,
		ShootTankSpawm,
		BigTankSpawm
	};

	TILE_INFO(*tileInfo)[TILE_COUNT];
	POINTFLOAT pos;
	EnemyTankSpawnInfo enemyTankSpawnInfo[10][20];
	int stageNum;
	int spawnNum;
	int spawnPos;
	float spawnDelay;
	bool spawnCheck;

	Image* enemySpawnEffect;
	bool spawnEffectCheck;
	bool spawnEffectUpDown;
	float spawnEffectTime;
	int spawnEffectFrame;
	int spawnEffectCount;

	Image* gameOver;
	bool gameOverCheck;
	float gameOverTime;
	float gameOverPos;

	bool winCheck;
	bool deadCheck;
public:
	void SetData(EnemyTankManager* enemyTankManager, PlayerTank* playerTank, AmmoManager* ammoManager, TILE_INFO(*tileInfo)[TILE_COUNT]);
	int GetSpawnNum() { return spawnNum; }
	void Init();
	void Update();
	void Render(HDC hdc);
	void Release();

	void SpawnEffect();
};

