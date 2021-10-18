#include "FastMoveEnemyTank.h"

HRESULT FastMoveEnemyTank::Init()
{

	img = ImageManager::GetSingleton()->FindImage("Image/Enemy/Enemy.bmp");
	pos.x = 32+8;
	pos.y = 16;
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
		img->Render(hdc, pos.x, pos.y, elapsedCount + elapsedWay, 1);
	}
	else
	{
		spawnEffect->Render(hdc, pos.x, pos.y, spawnEffect->GetCurrFrameX(), 0);
	}

}

void FastMoveEnemyTank::Release()
{
}
