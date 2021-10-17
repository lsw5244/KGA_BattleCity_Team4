#include "FastShootEnemyTank.h"

HRESULT FastShootEnemyTank::Init()
{
	img = ImageManager::GetSingleton()->FindImage("Image/Enemy/Enemy.bmp");
	pos.x = 48+8;
	pos.y = 16;
    return S_OK;
}

void FastShootEnemyTank::Update()
{

}

void FastShootEnemyTank::Render(HDC hdc)
{
	img->Render(hdc, pos.x, pos.y, 0, 2);

}

void FastShootEnemyTank::Release()
{
}
