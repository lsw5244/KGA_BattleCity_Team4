#include "FastShootEnemyTank.h"

HRESULT FastShootEnemyTank::Init()
{

	img = ImageManager::GetSingleton()->FindImage("Image/Enemy/Enemy.bmp");
	pos.x = 48+8;
	pos.y = 16;

	moveSpeed = 50;
    return S_OK;
}

void FastShootEnemyTank::Update()
{
	TankUpdate();
	
}

void FastShootEnemyTank::Render(HDC hdc)
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
		img->Render(hdc, pos.x, pos.y, elapsedCount + elapsedWay, 2);
	}
	else
	{
		spawnEffect->Render(hdc, pos.x, pos.y, spawnEffect->GetCurrFrameX(), 0);
	}

}

void FastShootEnemyTank::Release()
{
}
