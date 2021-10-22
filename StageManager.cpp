#include "StageManager.h"
#include "EnemyTankManager.h"
#include "EnemyTankFactory.h"
#include "TimerManager.h"
#define NormalTank		enemyTankFactory[0]->CreateEnemyTank()
#define FastTank		enemyTankFactory[1]->CreateEnemyTank()
#define ShootTank		enemyTankFactory[2]->CreateEnemyTank()
#define BigTank			enemyTankFactory[3]->CreateEnemyTank()

void StageManager::SetData(EnemyTankManager* enemyTankManager, int num)
{
	this->enemyTankManager = enemyTankManager;
	stageNum = num;
	spawnDelay = 0.0f;
	spawnNum = 0;
	spawnPos = 0;
	enemyTankFactory[0] = new NormalTankFactory;
	enemyTankFactory[1] = new FastShootTankFactory;
	enemyTankFactory[2] = new FastMoveTankFactory;
	enemyTankFactory[3] = new BigTankFactory;

	{
		enemyTankSpawnInfo[0][0] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[0][1] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[0][2] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[0][3] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[0][4] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[0][5] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[0][6] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[0][7] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[0][8] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[0][9] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[0][10] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[0][11] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[0][12] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[0][13] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[0][14] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[0][15] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[0][16] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[0][17] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[0][18] = EnemyTankSpawnInfo::FastTankSpawm;
		enemyTankSpawnInfo[0][19] = EnemyTankSpawnInfo::FastTankSpawm;
	}
	// 1스테이지 초기화

}

void StageManager::init()
{
}

void StageManager::Update()
{
	spawnDelay += TimerManager::GetSingleton()->GetDeltaTime();
	if (spawnDelay >= 5.0f) {

		switch (enemyTankSpawnInfo[stageNum][spawnNum]) {
		case EnemyTankSpawnInfo::NormalTankSpawm:
			enemyTankManager->NewEnemyTank(NormalTank, spawnPos, false);

			break;
		case EnemyTankSpawnInfo::FastTankSpawm:
			enemyTankManager->NewEnemyTank(FastTank, spawnPos, false);

			break;
		case EnemyTankSpawnInfo::ShootTankSpawm:
			enemyTankManager->NewEnemyTank(ShootTank, spawnPos, false);

			break;
		case EnemyTankSpawnInfo::BigTankSpawm:
			enemyTankManager->NewEnemyTank(BigTank, spawnPos, false);

			break;
		}
		spawnNum++;



		spawnDelay = 0;
		spawnPos++;
		if (spawnPos == 3) spawnPos = 2;
	}

}
