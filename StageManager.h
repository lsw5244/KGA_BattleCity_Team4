#pragma once
class EnemyTankManager;
class EnemyTankFactory;
class StageManager
{
private:
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
	void SetData(EnemyTankManager* enemyTankManager, int num);
	void init();
	void Update();
};

