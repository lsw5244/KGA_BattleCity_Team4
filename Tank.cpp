#include "Tank.h"
#include "EnemyTank.h"
#include "Image.h"

HRESULT Tank::Init()
{
	//spawnEffect->Init("Image/Effect/Spawn_Effect.BMP", 64, 16, 4, 1, true, RGB(255, 0, 255));

	enemyType = EnemyTankType::End;

	enemyMaxCount = 20;

	addEnemyCount = 0;

	destEnemyCount = 0;

	vecEnemyTanks.reserve(enemyMaxCount);

	bodySize = 16;

	onMapEnemyCount = 0;

	spawnTimer = 0.0f;

	spawnTank = true;

	return S_OK;
}

void Tank::Update()
{
	//	spawnTimer += 1.0f * TimerManager::GetSingleton()->GetDeltaTime();

	//if (onMapEnemyCount == 4)
	//{
	//	spawnTank = false;
	//	spawnTimer = 3.0f;
	//}

	//if (onMapEnemyCount < 4 && spawnTimer == 3.0f)
	//{
	//	for (int i = 0; i < 5; i++)
	//	{
	//		switch (spawnEffect->GetCurrFrameX())
	//		{
	//		case 0:
	//			for (int i = 0; i < 4; i++)
	//			{
	//				spawnEffect->SetCurrFrameX(i);
	//			}
	//			break;
	//		case 3:
	//			for (int i = 3; i >= 0; i--)
	//			{
	//				spawnEffect->SetCurrFrameX(i);
	//			}
	//			break;
	//		}
	//	}
	//	spawnTimer = 0.0f;
	//	onMapEnemyCount++;
	//}


	for (itEnemyTanks = vecEnemyTanks.begin(); itEnemyTanks != vecEnemyTanks.end(); itEnemyTanks++)
	{
		(*itEnemyTanks)->Update();
	}
}

void Tank::Render(HDC hdc)
{

	for (itEnemyTanks = vecEnemyTanks.begin(); itEnemyTanks != vecEnemyTanks.end(); itEnemyTanks++)
	{
		(*itEnemyTanks)->Render(hdc);
	}
}

void Tank::Release()
{
	for (itEnemyTanks = vecEnemyTanks.begin(); itEnemyTanks != vecEnemyTanks.end(); itEnemyTanks++)
	{
		SAFE_RELEASE((*itEnemyTanks));
	}
	vecEnemyTanks.clear();
}

void Tank::AddEnemy(EnemyTankType enemyType, int addEnemyNum)
{
	destEnemyCount += addEnemyNum;

	for (addEnemyCount; addEnemyCount < destEnemyCount; addEnemyCount++)
	{
		vecEnemyTanks.push_back(new EnemyTank);
		vecEnemyTanks[addEnemyCount]->SetEnemyTankType(enemyType);
		vecEnemyTanks[addEnemyCount]->Init();

		POINTFLOAT enemyPos = { ENEMY_SPAWN_POSX + ((bodySize * 6) * (addEnemyCount % 3)), ENEMY_SPAWN_POSY };//ENEMY_SPAWN_POSX
		vecEnemyTanks[addEnemyCount]->SetPos(enemyPos);
	}

}
