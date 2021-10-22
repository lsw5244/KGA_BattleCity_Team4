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


	POINTFLOAT pos;
	EnemyTankSpawnInfo enemyTankSpawnInfo[5][20];
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

public:
	void SetData(EnemyTankManager* enemyTankManager, PlayerTank* playerTank, AmmoManager* ammoManager, int num);
	void Init();
	void Update();
	void Render(HDC hdc);

	void SpawnEffect();
};

