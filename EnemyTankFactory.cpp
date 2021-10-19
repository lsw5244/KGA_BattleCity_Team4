#include "EnemyTankFactory.h"
#include "EnemyTanks.h"
#include "NormalEnemyTank.h"
#include "FastMoveEnemyTank.h"
#include "FastShootEnemyTank.h"
#include "BigEnemyTank.h"

void EnemyTankFactory::NewEnemyTank(TILE_INFO(*tileInfo)[TILE_COUNT], PlayerTank& playerTank, int posX)
{
	EnemyTanks* enemyTank = CreateEnemyTank();
	vecEnemyTank.push_back(enemyTank);
	vecEnemyTank.back()->TankInit(posX);
	vecEnemyTank.back()->Init();
	vecEnemyTank.back()->SetTileInfo(tileInfo);
	vecEnemyTank.back()->SetPlyaerRect(playerTank);
}

EnemyTankFactory::~EnemyTankFactory()
{
	for (vector<EnemyTanks*>::iterator it = vecEnemyTank.begin();
		it != vecEnemyTank.end();
		it++)
	{
		(*it)->Release();
		delete (*it);		// Missile
	}
	vecEnemyTank.clear();
}

EnemyTanks* NormalTankFactory::CreateEnemyTank()
{
	return new NormalEnemyTank;
}

HRESULT NormalTankFactory::Init()
{
	return S_OK;
}

void NormalTankFactory::Update()
{
	for (vector<EnemyTanks*>::iterator it = vecEnemyTank.begin();
		it != vecEnemyTank.end();
		it++)
	{
		(*it)->Update();
	}
}

void NormalTankFactory::Render(HDC hdc)
{
	for (vector<EnemyTanks*>::iterator it = vecEnemyTank.begin();
		it != vecEnemyTank.end();
		it++)
	{
		(*it)->Render(hdc);
	}
}

void NormalTankFactory::Release()
{

}

NormalTankFactory::~NormalTankFactory()
{
}

EnemyTanks* FastMoveTankFactory::CreateEnemyTank()
{
	return new FastMoveEnemyTank;
}

HRESULT FastMoveTankFactory::Init()
{
	return S_OK;
}

void FastMoveTankFactory::Update()
{
	for (vector<EnemyTanks*>::iterator it = vecEnemyTank.begin();
		it != vecEnemyTank.end();
		it++)
	{
		(*it)->Update();
	}
}

void FastMoveTankFactory::Render(HDC hdc)
{
	for (vector<EnemyTanks*>::iterator it = vecEnemyTank.begin();
		it != vecEnemyTank.end();
		it++)
	{
		(*it)->Render(hdc);
	}
}

void FastMoveTankFactory::Release()
{
}

FastMoveTankFactory::~FastMoveTankFactory()
{
}

EnemyTanks* FastShootTankFactory::CreateEnemyTank()
{
	return new FastShootEnemyTank;
}

HRESULT FastShootTankFactory::Init()
{
	return S_OK;
}

void FastShootTankFactory::Update()
{
	for (vector<EnemyTanks*>::iterator it = vecEnemyTank.begin();
		it != vecEnemyTank.end();
		it++)
	{
		(*it)->Update();
	}
}

void FastShootTankFactory::Render(HDC hdc)
{
	for (vector<EnemyTanks*>::iterator it = vecEnemyTank.begin();
		it != vecEnemyTank.end();
		it++)
	{
		(*it)->Render(hdc);
	}
}

void FastShootTankFactory::Release()
{
}

FastShootTankFactory::~FastShootTankFactory()
{
}

EnemyTanks* BigTankFactory::CreateEnemyTank()
{
	return new BigEnemyTank;
}

HRESULT BigTankFactory::Init()
{
	return S_OK;
}


void BigTankFactory::Update()
{
	for (vector<EnemyTanks*>::iterator it = vecEnemyTank.begin();
		it != vecEnemyTank.end();
		it++)
	{
		(*it)->Update();
	}
}

void BigTankFactory::Render(HDC hdc)
{
	for (vector<EnemyTanks*>::iterator it = vecEnemyTank.begin();
		it != vecEnemyTank.end();
		it++)
	{
		(*it)->Render(hdc);
	}
}

void BigTankFactory::Release()
{
}

BigTankFactory::~BigTankFactory()
{
}
