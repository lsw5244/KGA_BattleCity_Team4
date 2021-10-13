#include "Tank.h"
#include "EnemyTank.h"

HRESULT Tank::Init(TankType type)
{
	enemyType = EnemyTankType::End;

	enemyMaxCount = 20;

	return S_OK;
}

void Tank::Update()
{
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

void Tank::AddEnemy(int nCount, int fMCount, int qFCount, int bigCount, int iNCount, int iFMCount, int iQFCount, int iBigCount)
{
	//nCount, fMCount, qFCount, bigCount, iNCount, iFMCount, iQFCount, iBigCount;

	vecEnemyTanks.reserve(enemyMaxCount);

	for (int i = 0; 
		i < nCount; 
		i++)
	{
		vecEnemyTanks.push_back(new EnemyTank);
		vecEnemyTanks[i]->SetEnemyTankType(EnemyTankType::Normal);
		vecEnemyTanks[i]->Init();
	}

	for (int i = nCount; 
		i < nCount + fMCount; 
		i++)
	{
		vecEnemyTanks.push_back(new EnemyTank);
		vecEnemyTanks[i]->SetEnemyTankType(EnemyTankType::FastMove);
		vecEnemyTanks[i]->Init();
	}

	for (int i = nCount + fMCount; 
		i < nCount + fMCount + qFCount;
		i++)
	{
		vecEnemyTanks.push_back(new EnemyTank);
		vecEnemyTanks[i]->SetEnemyTankType(EnemyTankType::QuickFire);
		vecEnemyTanks[i]->Init();
	}

	for (int i = nCount + fMCount + qFCount;
		i < nCount + fMCount + qFCount + bigCount; 
		i++)
	{
		vecEnemyTanks.push_back(new EnemyTank);
		vecEnemyTanks[i]->SetEnemyTankType(EnemyTankType::Big);
		vecEnemyTanks[i]->Init();
	}

	for (int i = nCount + fMCount + qFCount + bigCount;
		i < nCount + fMCount + qFCount + bigCount + iNCount; 
		i++)
	{
		vecEnemyTanks.push_back(new EnemyTank);
		vecEnemyTanks[i]->SetEnemyTankType(EnemyTankType::iNormal);
		vecEnemyTanks[i]->Init();
	}

	for (int i = nCount + fMCount + qFCount + bigCount + iNCount;
		i < nCount + fMCount + qFCount + bigCount + iNCount + iFMCount; 
		i++)
	{
		vecEnemyTanks.push_back(new EnemyTank);
		vecEnemyTanks[i]->SetEnemyTankType(EnemyTankType::iFastMove);
		vecEnemyTanks[i]->Init();
	}

	for (int i = nCount + fMCount + qFCount + bigCount + iNCount + iFMCount; 
		i < nCount + fMCount + qFCount + bigCount + iNCount + iFMCount + iQFCount;
		i++)
	{
		vecEnemyTanks.push_back(new EnemyTank);
		vecEnemyTanks[i]->SetEnemyTankType(EnemyTankType::iQuickFire);
		vecEnemyTanks[i]->Init();
	}

	for (int i = nCount + fMCount + qFCount + bigCount + iNCount + iFMCount + iQFCount;
		i < nCount + fMCount + qFCount + bigCount + iNCount + iFMCount + iQFCount + iBigCount;
		i++)
	{
		vecEnemyTanks.push_back(new EnemyTank);
		vecEnemyTanks[i]->SetEnemyTankType(EnemyTankType::iBig);
		vecEnemyTanks[i]->Init();
	}

	for (int i = 0; i < nCount + fMCount + qFCount + bigCount + iNCount + iFMCount + iQFCount + iBigCount; i++)
	{
		POINTFLOAT enemyPos = { 50 + (60 * (i % 3)), 50 + (60 * (i / 3)) };
		
		vecEnemyTanks[i]->SetPos(enemyPos);
	}

}
