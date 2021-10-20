#include "FastMoveEnemyTank.h"

void FastMoveEnemyTank::SetVecEnemyTank(vector<EnemyTanks*> vecEnemyTank, int num)
{
	this->vecEnemyTanks[num] = vecEnemyTank;
}

HRESULT FastMoveEnemyTank::Init()
{

	if (itemTank) {
		img = ImageManager::GetSingleton()->FindImage("Image/Enemy/Enemy_Item.bmp");
		itemTime = 0.0f;
		itemfraemY = 2;
	} else {
		img = ImageManager::GetSingleton()->FindImage("Image/Enemy/Enemy.bmp");
	}
	moveSpeed = 50;

	return S_OK;
}

void FastMoveEnemyTank::Update()
{
	TankUpdate();
}

void FastMoveEnemyTank::Render(HDC hdc)
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
		if (itemTank) {
			img->Render(hdc, pos.x, pos.y, elapsedCount + elapsedWay, itemTankImg(2));
		}
		else {
			img->Render(hdc, pos.x, pos.y, elapsedCount + elapsedWay, 1);
		}
	}
	else
	{
		spawnEffect->Render(hdc, pos.x, pos.y, spawnEffect->GetCurrFrameX(), 0);
	}

}

void FastMoveEnemyTank::Release()
{
}
