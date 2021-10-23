#include "StageManager.h"
#include "EnemyTankManager.h"
#include "EnemyTankFactory.h"
#include "TimerManager.h"
#include "AmmoManager.h"
#include "PlayerTank.h"
#include "Image.h"
#include "ImageManager.h"

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
}

void StageManager::Init()
{
	enemyTankFactory[0] = new NormalTankFactory;
	enemyTankFactory[1] = new FastMoveTankFactory;
	enemyTankFactory[2] = new FastShootTankFactory;
	enemyTankFactory[3] = new BigTankFactory;
	
	enemySpawnEffect = ImageManager::GetSingleton()->FindImage("Image/Effect/Spawn_Effect.bmp");
	spawnEffectCheck = false;
	spawnEffectUpDown = true;;
	spawnEffectTime = 0.0f;
	spawnEffectFrame = 0;
	spawnEffectCount = 0;
	spawnCheck = false;
	
	spawnDelay = 5.0f;
	spawnPos = 0;
	spawnNum = 0;
	pos.x = 16 + (8);
	pos.y = 16;
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

	{
		enemyTankSpawnInfo[1][0] = EnemyTankSpawnInfo::BigTankSpawm;
		enemyTankSpawnInfo[1][1] = EnemyTankSpawnInfo::BigTankSpawm;
		enemyTankSpawnInfo[1][2] = EnemyTankSpawnInfo::FastTankSpawm;
		enemyTankSpawnInfo[1][3] = EnemyTankSpawnInfo::FastTankSpawm;
		enemyTankSpawnInfo[1][4] = EnemyTankSpawnInfo::FastTankSpawm;
		enemyTankSpawnInfo[1][5] = EnemyTankSpawnInfo::FastTankSpawm;
		enemyTankSpawnInfo[1][6] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[1][7] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[1][8] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[1][9] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[1][10] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[1][11] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[1][12] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[1][13] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[1][14] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[1][15] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[1][16] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[1][17] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[1][18] = EnemyTankSpawnInfo::NormalTankSpawm;
		enemyTankSpawnInfo[1][19] = EnemyTankSpawnInfo::NormalTankSpawm;
	}
	// 2스테이지 초기화
}

void StageManager::Update()
{
	if(spawnNum < 20)spawnDelay += TimerManager::GetSingleton()->GetDeltaTime();
	if (spawnDelay >= 3.0f && enemyTankManager->GetEnemyTankVecSize() < 4 && !spawnEffectCheck) {
		spawnEffectCheck = true;
		spawnPos++;
		if (spawnPos == 4) spawnPos = 1;
		if (spawnPos == 1) {
			pos.x = 16 + (8);
		}
		else if (spawnPos == 2) {
			pos.x = 16 + (8 + 96);
		}
		else {
			pos.x = 16 + (8 + 192);
		}
	}

	if (spawnEffectCheck)
	{
		spawnEffectTime += TimerManager::GetSingleton()->GetDeltaTime();
		SpawnEffect();
	}

	if (spawnCheck) {
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
		spawnCheck = false;
	}
}

void StageManager::Render(HDC hdc)
{
	if (spawnEffectCheck)
	{
		enemySpawnEffect->Render(hdc, pos.x, pos.y, spawnEffectFrame, 0);
	}
}

void StageManager::SpawnEffect()
{
	if (spawnEffectTime >= 0.1) {
		if (spawnEffectUpDown)spawnEffectFrame++;
		else spawnEffectFrame--;
		if (spawnEffectFrame == 0) spawnEffectUpDown = true;
		if (spawnEffectFrame == 3) spawnEffectUpDown = false;
		spawnEffectTime = 0.0f;
		spawnEffectCount++;
		if (spawnEffectCount == 13) {
			spawnEffectUpDown = true;
			spawnEffectCheck = false;
			spawnEffectTime = 0.0f;
			spawnEffectCount = 0;
			spawnEffectFrame = 0;
			spawnCheck = true;
		}
	}
}
