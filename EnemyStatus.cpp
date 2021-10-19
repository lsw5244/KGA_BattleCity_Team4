#include "EnemyStatus.h"
#include "Image.h"

HRESULT EnemyStatus::Init()
{
	ImageManager::GetSingleton()->AddImage("Image/Icon/Icon_Enemy.bmp", 8, 8, true, RGB(255, 0, 255));
	enemyNumIcon = ImageManager::GetSingleton()->FindImage("Image/Icon/Icon_Enemy.bmp");

	return S_OK;
}

void EnemyStatus::Update()
{
}

void EnemyStatus::Render(HDC hdc)
{
}

void EnemyStatus::Release()
{
}

void EnemyStatus::EnemyIconRender(HDC hdc, int enemyNum)
{
	for (int i = 0; i < enemyNum; i++)
	{
		enemyNumIcon->Render(hdc, 240 + (8 * (i % 2)), 16 + (8 * (i / 2)));
	}
}
