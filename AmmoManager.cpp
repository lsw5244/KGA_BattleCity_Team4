/*
	주의 ! : AmmoManager는 Init하기 전에 SetTileInfo를 먼저 해 주어야 함 !
*/

#include "AmmoManager.h"
#include "Ammo.h"

HRESULT AmmoManager::Init()
{
	vecEnemyAmmos.resize(enemyMaxAmmoCount);

	for (it = vecEnemyAmmos.begin(); it != vecEnemyAmmos.end(); it++)
	{
		(*it) = new Ammo;
		(*it)->Init();
		(*it)->SetTileInfo(tileInfo);
	}


	return S_OK;
}

void AmmoManager::Update()
{
}

void AmmoManager::Render(HDC hdc)
{
}

void AmmoManager::Release()
{
}
