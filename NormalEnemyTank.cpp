#include "NormalEnemyTank.h"

HRESULT NormalEnemyTank::Init()
{
	img = ImageManager::GetSingleton()->FindImage("Image/Enemy/Enemy.bmp");
	pos.x = 16+8;
	pos.y = 16;
	moveSpeed = 50;
	return S_OK;
}

void NormalEnemyTank::Update()
{
	TankUpdate();

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
	img->Render(hdc, pos.x, pos.y, elapsedCount+ elapsedWay, 0);
}

void NormalEnemyTank::Release()
{
}
