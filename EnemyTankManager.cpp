#include "EnemyTankManager.h"
#include "EnemyTanks.h"
#include "PlayerTank.h"
#include "AmmoManager.h"

void EnemyTankManager::NewEnemyTank(EnemyTanks* enemyTank,TILE_INFO(*tileInfo)[TILE_COUNT], PlayerTank& playerTank, int posX, AmmoManager* mgr, bool item)
{
	vecEnemyTank.push_back(enemyTank);
	vecEnemyTank.back()->TankInit(posX, item);
	vecEnemyTank.back()->SetAmmoMgr(mgr);
	vecEnemyTank.back()->Init();
	vecEnemyTank.back()->SetTileInfo(tileInfo);
	vecEnemyTank.back()->SetPlyaerRect(playerTank);
}


void EnemyTankManager::SetVecEnemyTank()
{
	for (vector<EnemyTanks*>::iterator it = vecEnemyTank.begin();
		it != vecEnemyTank.end();
		it++)
	{
		(*it)->SetVecEnemyTank(vecEnemyTank);
	}
}

HRESULT EnemyTankManager::Init()
{
	return S_OK;
}

void EnemyTankManager::Update()
{
	for (vector<EnemyTanks*>::iterator it = vecEnemyTank.begin();
		it != vecEnemyTank.end();)
	{
		(*it)->Update();
		if ((*it)->GetisDestruction()) {
			SAFE_RELEASE((*it));
			it = vecEnemyTank.erase(it);
		}
		else {
			it++;
		}
	}
	totalEnemyNum = vecEnemyTank.size();
	cout << vecEnemyTank.size() << endl;
}

void EnemyTankManager::Render(HDC hdc)
{
	for (vector<EnemyTanks*>::iterator it = vecEnemyTank.begin();
		it != vecEnemyTank.end();
		it++)
	{
		(*it)->Render(hdc);
	}
}

void EnemyTankManager::Release()
{
}
