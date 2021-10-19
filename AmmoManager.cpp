/*
	���� ! : AmmoManager�� Init�ϱ� ���� SetTileInfo�� ���� �� �־�� �� !
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
