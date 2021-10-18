#include "NormalEnemyTank.h"

HRESULT NormalEnemyTank::Init()
{
	ImageManager::GetSingleton()->AddImage("Image/Effect/Spawn_Effect.bmp", 64, 16, 4, 1, true, RGB(255, 0, 255));
	spawnEffect = ImageManager::GetSingleton()->FindImage("Image/Effect/Spawn_Effect.bmp");
	img = ImageManager::GetSingleton()->FindImage("Image/Enemy/Enemy.bmp");
	pos.x = 16+8;
	pos.y = 16;
	moveSpeed = 50;
	return S_OK;
}

void NormalEnemyTank::Update()
{
	SpawnEffect();
	if (SpawnEffect() == false)
	{
		TankUpdate();
	}
}

void NormalEnemyTank::Render(HDC hdc)
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
		img->Render(hdc, pos.x, pos.y, elapsedCount + elapsedWay, 0);
	}
	else
	{
		spawnEffect->Render(hdc, pos.x, pos.y, spawnEffect->GetCurrFrameX(), 0);
	}
}

void NormalEnemyTank::Release()
{
}
