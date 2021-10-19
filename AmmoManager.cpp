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

	for (int i = 0; i < PLAYE_MAX_AMMO_COUNT; i++)
	{
		playerAmmos[i] = new Ammo;
		playerAmmos[i]->Init();
		playerAmmos[i]->SetTileInfo(tileInfo);
	}

	return S_OK;
}

void AmmoManager::Update()
{
	for (it = vecEnemyAmmos.begin(); it != vecEnemyAmmos.end(); it++)
	{
		(*it)->Update();
	}

	for (int i = 0; i < PLAYE_MAX_AMMO_COUNT; i++)
	{
		playerAmmos[i]->Update();
	}
}

void AmmoManager::Render(HDC hdc)
{
	for (it = vecEnemyAmmos.begin(); it != vecEnemyAmmos.end(); it++)
	{
		(*it)->Render(hdc);
	}

	for (int i = 0; i < PLAYE_MAX_AMMO_COUNT; i++)
	{
		playerAmmos[i]->Render(hdc);
	}
}

void AmmoManager::Release()
{
	for (it = vecEnemyAmmos.begin(); it != vecEnemyAmmos.end(); it++)
	{
		SAFE_RELEASE((*it));
	}
	vecEnemyAmmos.clear();

	for (int i = 0; i < PLAYE_MAX_AMMO_COUNT; i++)
	{
		SAFE_RELEASE(playerAmmos[i]);
	}
}

void AmmoManager::EnemyFire(MoveDir dir, POINTFLOAT pos)
{
}

void AmmoManager::PlayerFire(MoveDir dir, POINTFLOAT pos)
{
	for (int i = 0; i < PLAYE_MAX_AMMO_COUNT; i++)
	{
		if (playerAmmos[i]->GetIsAlive() == false && playerAmmos[i]->GetRenderBoomEffect() == false)
		{
			playerAmmos[i]->Fire(dir, pos);
			break;
		}
	}

}
