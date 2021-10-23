#include "EnemyTankManager.h"
#include "EnemyTanks.h"
#include "PlayerTank.h"
#include "AmmoManager.h"
#include "TimerManager.h"

void EnemyTankManager::NewEnemyTank(EnemyTanks* enemyTank, int posX, bool item)
{
	vecEnemyTank.push_back(enemyTank);
	vecEnemyTank.back()->TankInit(posX, item);
	vecEnemyTank.back()->SetAmmoMgr(mgr);
	vecEnemyTank.back()->Init();
	vecEnemyTank.back()->SetTileInfo(tileInfo);
	vecEnemyTank.back()->SetPlyaerRect(*playerTank);
	vecEnemyTank.back()->SetItemManager(itemManager);
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

void EnemyTankManager::SetData(TILE_INFO(*tileInfo)[TILE_COUNT], PlayerTank& playerTank, AmmoManager* mgr,ItemManager* itemManager)
{
	this->tileInfo = tileInfo;
	this->playerTank = &playerTank;
	this->mgr = mgr;
	this->itemManager = itemManager;

}

void EnemyTankManager::BoomItemUse()
{
	for (vector<EnemyTanks*>::iterator it = vecEnemyTank.begin();
		it != vecEnemyTank.end();
		it++)
	{
		for (int i = 0; i < 4; i++)(*it)->isHit();
		(*it)->SetItemDes(true);
	}
}

HRESULT EnemyTankManager::Init()
{


	stopTimeCheck = false;
	stopTime = 0.0f;
	return S_OK;
}

void EnemyTankManager::Update()
{
	if (stopTimeCheck) 
	{
		stopTime += TimerManager::GetSingleton()->GetDeltaTime();
		for (vector<EnemyTanks*>::iterator it = vecEnemyTank.begin();
			it != vecEnemyTank.end(); it++)
		{
			if (stopTimeCheck) {
				(*it)->SetTimeStop(true);
				if (stopTime > 5) {
					stopTime = 0;
					stopTimeCheck = false;
					for (vector<EnemyTanks*>::iterator iT = vecEnemyTank.begin();
						iT != vecEnemyTank.end(); iT++)(*iT)->SetTimeStop(false);
				}
			}
		}
	}

	for (vector<EnemyTanks*>::iterator it = vecEnemyTank.begin();
		it != vecEnemyTank.end();)
	{
		(*it)->Update();
		if ((*it)->GetisDestruction()) {
			if (!(*it)->GetItemDes())
			{
				switch ((*it)->GetTankInfo())
				{
				case TankInfo::Normal:
					totalNormal++;
					break;
				case TankInfo::FastMove:
					totalFastMove++;
					break;
				case TankInfo::FastShoot:
					totalFastShoot++;
					break;
				case TankInfo::BigTank:
					totalBigTank++;
					break;
				}
			}
			else if ((*it)->GetItemDes())
			{
				itemBonusPoint++;
			}
			SAFE_RELEASE((*it));
			it = vecEnemyTank.erase(it);
		}
		else {
			it++;
		}
	}
	totalEnemyNum = vecEnemyTank.size();
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
