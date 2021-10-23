#include "EnemyStatus.h"
#include "Image.h"
#include "EnemyTankManager.h"

HRESULT EnemyStatus::Init(EnemyTankManager& enemyTank)
{
	enemyNumIcon = ImageManager::GetSingleton()->FindImage("Image/Icon/Icon_Enemy.bmp");

	SetEnemyTank(enemyTank);
	return S_OK;
}

void EnemyStatus::Update(EnemyTankManager& enemyTank)
{
	totalEnmey = enemyTank.GetTotalEnemyNum();
}

void EnemyStatus::Render(HDC hdc)
{
	for (int i = 0; i < totalEnmey; i++)
	{
		enemyNumIcon->Render(hdc, 240 + (8 * (i % 2)), 16 + (8 * (i / 2)));
	}
}

void EnemyStatus::Release()
{
}
