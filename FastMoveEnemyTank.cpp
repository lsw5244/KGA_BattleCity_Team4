#include "FastMoveEnemyTank.h"

HRESULT FastMoveEnemyTank::Init()
{
	img = ImageManager::GetSingleton()->FindImage("Image/Enemy/Enemy.bmp");
	pos.x = 32+8;
	pos.y = 16;
	return S_OK;
}

void FastMoveEnemyTank::Update()
{

}

void FastMoveEnemyTank::Render(HDC hdc)
{
	img->Render(hdc, pos.x, pos.y, 0, 1);

}

void FastMoveEnemyTank::Release()
{
}
