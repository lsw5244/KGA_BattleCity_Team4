#include "BigEnemyTank.h"
#include "AmmoManager.h"
void BigEnemyTank::SetVecEnemyTank(vector<EnemyTanks*> vecEnemyTank, int num)
{
	this->vecEnemyTanks[num] = vecEnemyTank;
}
HRESULT BigEnemyTank::Init()
{
	if (itemTank) {
		img = ImageManager::GetSingleton()->FindImage("Image/Enemy/Enemy_Item.bmp");
		itemTime = 0.0f;
		itemfraemY = 6;
	} else {
		img = ImageManager::GetSingleton()->FindImage("Image/Enemy/Enemy.bmp");
	}
	moveSpeed = 50;
	return S_OK;
}

void BigEnemyTank::Update()
{
	AutoFire();
	TankUpdate();
}

void BigEnemyTank::Render(HDC hdc)
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
			img->Render(hdc, pos.x, pos.y, elapsedCount + elapsedWay, itemTankImg(6));
		}
		else {
			img->Render(hdc, pos.x, pos.y, elapsedCount + elapsedWay, 3);
		}
	}
	else
	{
		spawnEffect->Render(hdc, pos.x, pos.y,spawnEffect->GetCurrFrameX(), 0);
	}

}

void BigEnemyTank::Release()
{
}

void BigEnemyTank::AutoFire()
{
	attackDelayTime += TimerManager::GetSingleton()->GetDeltaTime();

	if (attackDelayTime > attackDelay)
	{
		ammoMgr->EnemyFire(movedir, pos);

		attackDelay = rand() % 3 + 1;

		attackDelayTime = 0.0f;

	}
}
