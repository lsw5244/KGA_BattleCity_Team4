#include "BigEnemyTank.h"
HRESULT BigEnemyTank::Init()
{
	img = ImageManager::GetSingleton()->FindImage("Image/Enemy/Enemy.bmp");
	pos.x = 64+8;
	pos.y = 16;
	shape.left = pos.x - 8;
	shape.top = pos.y - 8;
	shape.right = pos.x + 8;
	shape.bottom = pos.y + 8;
	moveSpeed = 50;
	movedir = MoveDir::Down;

	return S_OK;
}

void BigEnemyTank::Update()
{
	switch (movedir) {
	case MoveDir::Up:
		PosReset(MoveDir::Up);
		CollisionAndMove(MoveDir::Up);
		break;
	case MoveDir::Down:
		PosReset(MoveDir::Down);
		CollisionAndMove(MoveDir::Down);
		break;
	case MoveDir::Right:
		PosReset(MoveDir::Right);
		CollisionAndMove(MoveDir::Right);
		break;
	case MoveDir::Left:
		PosReset(MoveDir::Left);
		CollisionAndMove(MoveDir::Left);
		break;
	}
}

void BigEnemyTank::Render(HDC hdc)
{
	img->Render(hdc, pos.x, pos.y, 0, 3);

}

void BigEnemyTank::Release()
{
}
