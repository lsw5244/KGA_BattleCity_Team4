#pragma once
class EnemyTankManager;
class EnemyTankFactory;
class AmmoManager;
class PlayerTank;
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

	EnemyTankSpawnInfo enemyTankSpawnInfo[5][20];
	int stageNum;
	int spawnNum;
	int spawnPos;
	
	float spawnDelay;
public:
	void SetData(EnemyTankManager* enemyTankManager, PlayerTank* playerTank, AmmoManager* ammoManager, int num);
	void init();
	void Update();
};

