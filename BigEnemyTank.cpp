#include "BigEnemyTank.h"
HRESULT BigEnemyTank::Init()
{
	img = ImageManager::GetSingleton()->FindImage("Image/Enemy/Enemy.bmp");
	pos.x = 64+8;
	pos.y = 16;

	moveSpeed = 50;

	return S_OK;
}

void BigEnemyTank::Update()
{
	time += TimerManager::GetSingleton()->GetDeltaTime();
	if (time >= 0.3f) {
		MoveDir bufferMoveDir;
		bufferMoveDir = AutoMove(movedir, pos);
		if (bufferMoveDir != movedir) {
			movedir = bufferMoveDir;
			time = 0;
		}
	}
	switch (movedir) {
	case MoveDir::Up:
		PosReset(MoveDir::Up);
		CollisionAndMove(MoveDir::Up);
		elapsedCount++;
		elapsedCount = CurrFrame(*img, &elapsedCount, 1);
		break;
	case MoveDir::Down:
		PosReset(MoveDir::Down);
		CollisionAndMove(MoveDir::Down);
		elapsedCount++;
		elapsedCount = CurrFrame(*img, &elapsedCount, 5);
		break;
	case MoveDir::Right:
		PosReset(MoveDir::Right);
		CollisionAndMove(MoveDir::Right);
		elapsedCount++;
		elapsedCount = CurrFrame(*img, &elapsedCount, 3);
		break;
	case MoveDir::Left:
		PosReset(MoveDir::Left);
		CollisionAndMove(MoveDir::Left);
		elapsedCount++;
		elapsedCount = CurrFrame(*img, &elapsedCount, 7);
		break;
	}
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
	img->Render(hdc, pos.x, pos.y, elapsedCount, 3);

}

void BigEnemyTank::Release()
{
}
