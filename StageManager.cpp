#include "StageManager.h"
#include "EnemyTankManager.h"
#include "EnemyTankFactory.h"
#include "TimerManager.h"
#include "AmmoManager.h"
#include "PlayerTank.h"
#define NormalTank		enemyTankFactory[0]->CreateEnemyTank()
#define FastTank		enemyTankFactory[1]->CreateEnemyTank()
#define ShootTank		enemyTankFactory[2]->CreateEnemyTank()
#define BigTank			enemyTankFactory[3]->CreateEnemyTank()

void StageManager::SetData(EnemyTankManager* enemyTankManager, PlayerTank* playerTank, AmmoManager* ammoManager, int num)
{
	this->ammoManager = ammoManager;
	this->enemyTankManager = enemyTankManager;
	this->playerTank = playerTank;
	stageNum = num;
	spawnDelay = 5.0f;
	spawnNum = 0;
	spawnPos = 1;
	enemyTankFactory[0] = new NormalTankFactory;
	enemyTankFactory[1] = new FastMoveTankFactory;
	enemyTankFactory[2] = new FastShootTankFactory;
	enemyTankFactory[3] = new BigTankFactory;

}

void StageManager::init()
{
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

void StageManager::Update()
{
	spawnDelay += TimerManager::GetSingleton()->GetDeltaTime();
	if (spawnDelay >= 3.0f && enemyTankManager->GetEnemyTankVecSize() < 4) {

		switch (enemyTankSpawnInfo[stageNum][spawnNum]) {
		case EnemyTankSpawnInfo::NormalTankSpawm:
			if (spawnNum == 3 || spawnNum == 11 || spawnNum == 17) enemyTankManager->NewEnemyTank(NormalTank, spawnPos, true);
			else enemyTankManager->NewEnemyTank(NormalTank, spawnPos, false);
			break;
		case EnemyTankSpawnInfo::FastTankSpawm:
			if (spawnNum == 3 || spawnNum == 11 || spawnNum == 17) enemyTankManager->NewEnemyTank(FastTank, spawnPos, true);
			else enemyTankManager->NewEnemyTank(FastTank, spawnPos, false);
			break;
		case EnemyTankSpawnInfo::ShootTankSpawm:
			if (spawnNum == 3 || spawnNum == 11 || spawnNum == 17) enemyTankManager->NewEnemyTank(ShootTank, spawnPos, true);
			else enemyTankManager->NewEnemyTank(ShootTank, spawnPos, false);
			break;
		case EnemyTankSpawnInfo::BigTankSpawm:
			if (spawnNum == 3 || spawnNum == 11 || spawnNum == 17) enemyTankManager->NewEnemyTank(BigTank, spawnPos, true);
			else enemyTankManager->NewEnemyTank(BigTank, spawnPos, false);
			break;
		}

		ammoManager->SetVecEnemyTank(enemyTankManager->GetVecEnemyTanks());
		ammoManager->SetTileInfoAndEnemyVec();
		enemyTankManager->SetVecEnemyTank();
		playerTank->SetVecEnemyTank(enemyTankManager->GetVecEnemyTanks());


		spawnNum++;
		spawnDelay = 0;
		spawnPos++;
		if (spawnPos == 4) spawnPos = 1;
	}


}
