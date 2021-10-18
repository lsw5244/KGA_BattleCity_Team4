#include "FastMoveEnemyTank.h"

HRESULT FastMoveEnemyTank::Init()
{
	ImageManager::GetSingleton()->AddImage("Image/Effect/Spawn_Effect.bmp", 64, 16, 4, 1, true, RGB(255, 0, 255));
	spawnEffect = ImageManager::GetSingleton()->FindImage("Image/Effect/Spawn_Effect.bmp");
	img = ImageManager::GetSingleton()->FindImage("Image/Enemy/Enemy.bmp");
	pos.x = 32+8;
	pos.y = 16;
	moveSpeed = 50;

	return S_OK;
}

void FastMoveEnemyTank::Update()
{
	SpawnEffect();
	if (SpawnEffect() == false)
	{
		TankUpdate();
	}
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
