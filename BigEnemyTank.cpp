#include "BigEnemyTank.h"
HRESULT BigEnemyTank::Init()
{
	img = ImageManager::GetSingleton()->FindImage("Image/Enemy/Enemy.bmp");
	pos.y = 16;

	moveSpeed = 50;

	return S_OK;
}

void BigEnemyTank::Update()
{
	static bool check = true;
    static int count = 0;
    if (check && count < 10) {
        cout << *test << endl;
        count++;
    }
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
	img->Render(hdc, pos.x, pos.y, elapsedCount+ elapsedWay, 3);

}

void BigEnemyTank::Release()
{
}
