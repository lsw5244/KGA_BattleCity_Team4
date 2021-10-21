#include "NormalEnemyTank.h"
#include "AmmoManager.h"
HRESULT NormalEnemyTank::Init()
{
	attackDelay = rand() % 3 + 1;

	if (itemTank) {
		img = ImageManager::GetSingleton()->FindImage("Image/Enemy/Enemy_Item.bmp");
		itemTime = 0.0f;
		itemfraemY = 0;
	}
	else {
		img = ImageManager::GetSingleton()->FindImage("Image/Enemy/Enemy.bmp");
	}
	moveSpeed = 50;
	return S_OK;
}

void NormalEnemyTank::Update()
{
	AutoFire();
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
	if (SpawnEffect() == false)
	{
		if (itemTank) {
			img->Render(hdc, pos.x, pos.y, elapsedCount + elapsedWay, itemTankImg(0));
		}
		else {
			img->Render(hdc, pos.x, pos.y, elapsedCount + elapsedWay, 2);
		}
	}
	else
	{
		spawnEffect->Render(hdc, pos.x, pos.y, spawnEffect->GetCurrFrameX(), 0);
	}
}

void NormalEnemyTank::Release()
{
}

void NormalEnemyTank::AutoFire()
{
	attackDelayTime += TimerManager::GetSingleton()->GetDeltaTime();

	if (attackDelayTime > attackDelay)
	{
		ammoMgr->EnemyFire(movedir, pos);

		attackDelay = rand() % 3 + 1;

		attackDelayTime = 0.0f;
	}
}
