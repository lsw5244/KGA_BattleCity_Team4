#include "NormalEnemyTank.h"

HRESULT NormalEnemyTank::Init()
{
	img = ImageManager::GetSingleton()->FindImage("Image/Enemy/Enemy.bmp");
	pos.x = 16+8;
	pos.y = 16;
	return S_OK;
}

void NormalEnemyTank::Update()
{

}

void NormalEnemyTank::Render(HDC hdc)
{
	img->Render(hdc, pos.x, pos.y, 0, 0);
}

void NormalEnemyTank::Release()
{
}
