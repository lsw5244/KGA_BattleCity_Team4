#include "FastMoveEnemyTank.h"
#include "AmmoManager.h"
HRESULT FastMoveEnemyTank::Init()
{
	attackDelay = rand() % 3 + 1;

	if (itemTank) {
		img = ImageManager::GetSingleton()->FindImage("Image/Enemy/Enemy_Item.bmp");
		itemTime = 0.0f;
		itemfraemY = 2;
	} else {
		img = ImageManager::GetSingleton()->FindImage("Image/Enemy/Enemy.bmp");
	}
	moveSpeed = 50;
	hp = 1;
	return S_OK;
}

void FastMoveEnemyTank::Update()
{
	if (KeyManager::GetSingleton()->IsOnceKeyDown('Q')) isHit();
	if (!isDestructionEffect) {
		AutoFire();
		TankUpdate();
	}
	else {
		destructionEffectTime += TimerManager::GetSingleton()->GetDeltaTime();
		if (destructionEffectTime >= 0.1f) {
			destructionEffectNum++;
			if (destructionEffectNum >= 6)isDestruction = true;
			destructionEffectTime = 0;
		}
	}
}

void FastMoveEnemyTank::Render(HDC hdc)
{
	if (!isDestructionEffect) {
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
				img->Render(hdc, pos.x, pos.y, elapsedCount + elapsedWay, itemTankImg(2));
			}
			else {
				img->Render(hdc, pos.x, pos.y, elapsedCount + elapsedWay, 1);
			}
		}
	}
	else {
		destructionEffect1->Render(hdc, pos.x, pos.y, destructionEffectNum, 0);
	}
}

void FastMoveEnemyTank::Release()
{
}

void FastMoveEnemyTank::AutoFire()
{
	attackDelayTime += TimerManager::GetSingleton()->GetDeltaTime();

	if (attackDelayTime > attackDelay)
	{
		ammoMgr->EnemyFire(movedir, pos);

		attackDelay = rand() % 3 + 1;

		attackDelayTime = 0.0f;
	}
}
