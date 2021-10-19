#include "BigEnemyTank.h"
void BigEnemyTank::SetVecEnemyTank(vector<EnemyTanks*> vecEnemyTank, int num)
{
	this->vecEnemyTanks[num] = vecEnemyTank;
}
HRESULT BigEnemyTank::Init()
{

	img = ImageManager::GetSingleton()->FindImage("Image/Enemy/Enemy.bmp");
	moveSpeed = 50;

	return S_OK;
}

void BigEnemyTank::Update()
{
	TankUpdate();
}

void BigEnemyTank::Render(HDC hdc)
{
	if (KeyManager::GetSingleton()->IsStayKeyDown(TANK_COLLIDER_DEBUG)) {
		Rectangle(hdc,
			shape.left,
			shape.top,
			shape.right,
			shape.bottom);
	}
	if (SpawnEffect() == false)
	{
		img->Render(hdc, pos.x, pos.y, elapsedCount+ elapsedWay, 3);
	}
	else
	{
		spawnEffect->Render(hdc, pos.x, pos.y,spawnEffect->GetCurrFrameX(), 0);
	}

}

void BigEnemyTank::Release()
{
}
