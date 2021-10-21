#include "FastShootEnemyTank.h"
#include "AmmoManager.h"


HRESULT FastShootEnemyTank::Init()
{
	attackDelay = rand() % 3 + 1;

	if (itemTank) {
		img = ImageManager::GetSingleton()->FindImage("Image/Enemy/Enemy_Item.bmp");
		itemTime = 0.0f;
		itemfraemY = 4;
	}
	else {
		img = ImageManager::GetSingleton()->FindImage("Image/Enemy/Enemy.bmp");
	}
	moveSpeed = 50;
	hp = 1;
	return S_OK;
}

void FastShootEnemyTank::Update()
{
	if (isDestruction) {
		AutoFire();
		TankUpdate();
	}
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
		if (itemTank) {
			img->Render(hdc, pos.x, pos.y, elapsedCount + elapsedWay, itemTankImg(4));
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

void FastShootEnemyTank::Release()
{
}

void FastShootEnemyTank::AutoFire()
{
	attackDelayTime += TimerManager::GetSingleton()->GetDeltaTime();

	if (attackDelayTime > attackDelay)
	{
		ammoMgr->EnemyFire(movedir, pos);

		attackDelay = rand() % 3 + 1;

		attackDelayTime = 0.0f;
	}
}
