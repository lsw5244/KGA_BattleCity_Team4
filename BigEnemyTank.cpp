#include "BigEnemyTank.h"
HRESULT BigEnemyTank::Init()
{
	img = ImageManager::GetSingleton()->FindImage("Image/Enemy/Enemy.bmp");
	pos.x = 64+8;
	pos.y = 16;
	return S_OK;
}

void BigEnemyTank::Update()
{
}

void BigEnemyTank::Render(HDC hdc)
{
	img->Render(hdc, pos.x, pos.y, 0, 3);

}

void BigEnemyTank::Release()
{
}
