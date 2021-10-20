/*
		사용하기
		사용 할 총알에 tileInfo넣어주기
		발사할 때 Fire()함수를 작동시키면 발사
		총알이 충돌하면 DestroyAmmo()함수 작동시키기

		FIXME
		1. 부수지 못하는 벽돌, 탱크랑 출돌했을 때 추가하기
*/

#include "Ammo.h"
#include "Image.h"
#include "PlayerTank.h"
HRESULT Ammo::Init()
{
	ImageManager::GetSingleton()->AddImage("Image/Bullet/Missile_Down.bmp", 3, 4, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("Image/Bullet/Missile_Left.bmp", 4, 3, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("Image/Bullet/Missile_Right.bmp", 4, 3, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("Image/Bullet/Missile_Up.bmp", 3, 4, true, RGB(255, 0, 255));

	ImageManager::GetSingleton()->AddImage("Image/Effect/Boom_Effect.bmp", 48, 16, 3, 1, true, RGB(255, 0, 255));
	boomEffect = ImageManager::GetSingleton()->FindImage("Image/Effect/Boom_Effect.bmp");
	isAlive = false;
	//dir = MoveDir::Right;
	renderBoomEffect = false;
	showCollider = false;

	sec = 0.0f;

	pos = { -10, -10 };

	moveSpeed = 100.0f;

	bodySize = 4;

	shape.left = pos.x - bodySize / 2;
	shape.right = shape.left + bodySize;
	shape.top = pos.y - bodySize / 2;
	shape.bottom = shape.top + bodySize;

	SetRect(&gameSceneRect, 16, 8, 224, 216);

	hitTile1 = nullptr;
	hitTile2 = nullptr;

	return S_OK;
}

void Ammo::Update()
{
	if (CollisionEnter(*(playerTank->GetRect()), shape) && type != TankType::Player)
	{
		cout << "플레이어 히트 !!" << endl;
	}

	AmmoHitCheck();

	shape.left = pos.x - bodySize / 2;
	shape.right = shape.left + bodySize;
	shape.top = pos.y - bodySize / 2;
	shape.bottom = shape.top + bodySize;

	if (!(CollisionEnter(gameSceneRect, shape)) && isAlive == true)
	{
		DestroyAmmo();
	}

	if (KeyManager::GetSingleton()->IsOnceKeyDown('P'))
	{
		showCollider = showCollider ? false : true;
	}

	if (isAlive == false)
	{
		return;
	}

	switch (dir)
	{
	case MoveDir::Left:
		pos.x -= moveSpeed * TimerManager::GetSingleton()->GetDeltaTime();;
		break;
	case MoveDir::Right:
		pos.x += moveSpeed * TimerManager::GetSingleton()->GetDeltaTime();;
		break;
	case MoveDir::Up:
		pos.y -= moveSpeed * TimerManager::GetSingleton()->GetDeltaTime();
		break;
	case MoveDir::Down:
		pos.y += moveSpeed * TimerManager::GetSingleton()->GetDeltaTime();;
		break;
	}
}

void Ammo::Render(HDC hdc)
{
	if (renderBoomEffect == true)
	{
		boomEffect->Render(hdc, pos.x, pos.y, boomEffect->GetCurrFrameX(), boomEffect->GetCurrFrameY());
		sec += TimerManager::GetSingleton()->GetDeltaTime();
		if (sec > 0.05f)
		{
			sec = 0.0f;
			boomEffect->SetCurrFrameX((boomEffect->GetCurrFrameX()) + 1);
			if (boomEffect->GetCurrFrameX() > 2)
			{
				renderBoomEffect = false;
				boomEffect->SetCurrFrameX(0);
				pos = { -10, -10 };
			}
		}
	}

	if (isAlive == false)
	{
		return;
	}

	img->Render(hdc, pos.x, pos.y);

	if (showCollider == true)
	{
		Rectangle(hdc, shape.left, shape.top, shape.right, shape.bottom);
	}
}

void Ammo::Release()
{
}

void Ammo::Fire(MoveDir dir, POINTFLOAT pos)
{
	isAlive = true;
	this->pos = pos;
	switch (dir)
	{
	case MoveDir::Left:
		img = ImageManager::GetSingleton()->FindImage("Image/Bullet/Missile_Left.bmp");
		this->dir = dir;
		break;
	case MoveDir::Right:
		img = ImageManager::GetSingleton()->FindImage("Image/Bullet/Missile_Right.bmp");
		this->dir = dir;
		break;
	case MoveDir::Up:
		img = ImageManager::GetSingleton()->FindImage("Image/Bullet/Missile_Up.bmp");
		this->dir = dir;
		break;
	case MoveDir::Down:
		img = ImageManager::GetSingleton()->FindImage("Image/Bullet/Missile_Down.bmp");
		this->dir = dir;
		break;
	}
}

void Ammo::DestroyAmmo()
{
	isAlive = false;

	renderBoomEffect = true;
}

void Ammo::AmmoHitCheck()
{
	for (int i = 0; i < TILE_COUNT; i++)
	{
		for (int j = 0; j < TILE_COUNT; j++)
		{
			if (CollisionEnter(tileInfo[i][j].selectRc, shape))
			{
				if (tileInfo[i][j].terrain == Terrain::Brick)
				{
					// 오른쪽, 아래쪽 확인하기
					hitTile1 = &tileInfo[i][j];

					if (CollisionEnter(tileInfo[i + 1][j].selectRc, shape) &&
						tileInfo[i + 1][j].terrain == Terrain::IronBrick || 
						(CollisionEnter(tileInfo[i][j + 1].selectRc, shape) &&
						tileInfo[i][j + 1].terrain == Terrain::IronBrick))
					{
						IronWallHitDestroyWall(hitTile1);
					}
					else if (CollisionEnter(tileInfo[i + 1][j].selectRc ,shape) &&
						tileInfo[i + 1][j].terrain == Terrain::Brick)
					{
						hitTile2 = &tileInfo[i + 1][j];
						DestroyWall(hitTile1, hitTile2);
					}
					else if (CollisionEnter(tileInfo[i][j + 1].selectRc, shape) && 
						tileInfo[i][j + 1].terrain == Terrain::Brick)
					{
						hitTile2 = &tileInfo[i][j + 1];
						DestroyWall(hitTile1, hitTile2);
					}
					else
					{
						DestroyWall(hitTile1);
					}
					return;
				}

				if (tileInfo[i][j].terrain == Terrain::IronBrick)
				{
					hitTile1 = &tileInfo[i][j];
					if (CollisionEnter(tileInfo[i + 1][j].selectRc, shape) &&
						tileInfo[i + 1][j].terrain == Terrain::Brick)
					{
						hitTile2 = &tileInfo[i + 1][j];
						IronWallHitDestroyWall(hitTile2);
					}
					else if (CollisionEnter(tileInfo[i][j + 1].selectRc, shape) &&
						tileInfo[i][j + 1].terrain == Terrain::Brick)
					{
						hitTile2 = &tileInfo[i][j + 1];
						IronWallHitDestroyWall(hitTile2);
					}
					else
					{
						DestroyAmmo();
					}
					return;

				}
			}
		}
	}
}

void Ammo::DestroyWall(int i, int j)
{
	if (isAlive == false)	return;

	DestroyAmmo();

	switch (dir)
	{
	case MoveDir::Down:
		if (tileInfo[i][j].isDes[0][0] == false && tileInfo[i][j].isDes[0][1] == false)
		{
			tileInfo[i][j].isDes[1][0] = false;
			tileInfo[i][j].isDes[1][1] = false;
		}
		else
		{
			tileInfo[i][j].isDes[0][0] = false;
			tileInfo[i][j].isDes[0][1] = false;
		}
		break;

	case MoveDir::Up:
		if (tileInfo[i][j].isDes[1][0] == false && tileInfo[i][j].isDes[1][1] == false)
		{
			tileInfo[i][j].isDes[0][0] = false;
			tileInfo[i][j].isDes[0][1] = false;
		}
		else
		{
			tileInfo[i][j].isDes[1][0] = false;
			tileInfo[i][j].isDes[1][1] = false;
		}
		break;

	case MoveDir::Left:
		if (tileInfo[i][j].isDes[0][1] == false && tileInfo[i][j].isDes[1][1] == false)
		{
			tileInfo[i][j].isDes[0][0] = false;
			tileInfo[i][j].isDes[1][0] = false;
		}
		else
		{
			tileInfo[i][j].isDes[0][1] = false;
			tileInfo[i][j].isDes[1][1] = false;
		}
		break;

	case MoveDir::Right:
		if (tileInfo[i][j].isDes[0][0] == false && tileInfo[i][j].isDes[1][0] == false)
		{
			tileInfo[i][j].isDes[0][1] = false;
			tileInfo[i][j].isDes[1][1] = false;
		}
		else
		{
			tileInfo[i][j].isDes[0][0] = false;
			tileInfo[i][j].isDes[1][0] = false;
		}
		break;
	}

	hitTile1 = nullptr;
	hitTile2 = nullptr;

}

void Ammo::DestroyWall(TILE_INFO* tileInfo)
{
	//tileInfo->isDes[0][0] = false;
	if (isAlive == false)	return;

	DestroyAmmo();

	switch (dir)
	{
	case MoveDir::Down:
		if (tileInfo->isDes[0][0] == false && tileInfo->isDes[0][1] == false)
		{
			tileInfo->isDes[1][0] = false;
			tileInfo->isDes[1][1] = false;
		}
		else
		{
			tileInfo->isDes[0][0] = false;
			tileInfo->isDes[0][1] = false;
		}
		break;

	case MoveDir::Up:
		if (tileInfo->isDes[1][0] == false && tileInfo->isDes[1][1] == false)
		{
			tileInfo->isDes[0][0] = false;
			tileInfo->isDes[0][1] = false;
		}
		else
		{
			tileInfo->isDes[1][0] = false;
			tileInfo->isDes[1][1] = false;
		}
		break;

	case MoveDir::Left:
		if (tileInfo->isDes[0][1] == false && tileInfo->isDes[1][1] == false)
		{
			tileInfo->isDes[0][0] = false;
			tileInfo->isDes[1][0] = false;
		}
		else
		{
			tileInfo->isDes[0][1] = false;
			tileInfo->isDes[1][1] = false;
		}
		break;

	case MoveDir::Right:
		if (tileInfo->isDes[0][0] == false && tileInfo->isDes[1][0] == false)
		{
			tileInfo->isDes[0][1] = false;
			tileInfo->isDes[1][1] = false;
		}
		else
		{
			tileInfo->isDes[0][0] = false;
			tileInfo->isDes[1][0] = false;
		}
		break;
	}

	hitTile1 = nullptr;
	hitTile2 = nullptr;
}

void Ammo::DestroyWall(TILE_INFO* tileInfo1, TILE_INFO* tileinfo2)
{
	if (isAlive == false)	return;

	DestroyAmmo();

	switch (dir)
	{
	case MoveDir::Down:
		if (tileInfo1->isDes[0][0] == false &&
			tileInfo1->isDes[0][1] == false &&
			tileinfo2->isDes[0][0] == false &&
			tileinfo2->isDes[0][1] == false)
		{
			tileInfo1->isDes[1][0] = false;
			tileInfo1->isDes[1][1] = false;
			tileinfo2->isDes[1][0] = false;
			tileinfo2->isDes[1][1] = false;
		}
		else
		{
			tileInfo1->isDes[0][0] = false;
			tileInfo1->isDes[0][1] = false;
			tileinfo2->isDes[0][0] = false;
			tileinfo2->isDes[0][1] = false;
		}
		break;

	case MoveDir::Up:
		if (tileInfo1->isDes[1][0] == false &&
			tileInfo1->isDes[1][1] == false &&
			tileinfo2->isDes[1][0] == false &&
			tileinfo2->isDes[1][1] == false)
		{
			tileInfo1->isDes[0][0] = false;
			tileInfo1->isDes[0][1] = false;
			tileinfo2->isDes[0][0] = false;
			tileinfo2->isDes[0][1] = false;
		}
		else
		{
			tileInfo1->isDes[1][0] = false;
			tileInfo1->isDes[1][1] = false;
			tileinfo2->isDes[1][0] = false;
			tileinfo2->isDes[1][1] = false;
		}
		break;

	case MoveDir::Left:
		if (tileInfo1->isDes[0][1] == false &&
			tileInfo1->isDes[1][1] == false &&
			tileinfo2->isDes[0][1] == false &&
			tileinfo2->isDes[1][1] == false)
		{
			tileInfo1->isDes[0][0] = false;
			tileInfo1->isDes[1][0] = false;
			tileinfo2->isDes[0][0] = false;
			tileinfo2->isDes[1][0] = false;
		}
		else
		{
			tileInfo1->isDes[0][1] = false;
			tileInfo1->isDes[1][1] = false;
			tileinfo2->isDes[0][1] = false;
			tileinfo2->isDes[1][1] = false;
		}
		break;

	case MoveDir::Right:
		if (tileInfo1->isDes[0][0] == false &&
			tileInfo1->isDes[1][0] == false &&
			tileinfo2->isDes[0][0] == false &&
			tileinfo2->isDes[1][0] == false)
		{
			tileInfo1->isDes[0][1] = false;
			tileInfo1->isDes[1][1] = false;
			tileinfo2->isDes[0][1] = false;
			tileinfo2->isDes[1][1] = false;
		}
		else
		{
			tileInfo1->isDes[0][0] = false;
			tileInfo1->isDes[1][0] = false;
			tileinfo2->isDes[0][0] = false;
			tileinfo2->isDes[1][0] = false;
		}
		break;
	}

	hitTile1 = nullptr;
	hitTile2 = nullptr;
}

void Ammo::IronWallHitDestroyWall(TILE_INFO* tileInfo)
{
	if (isAlive == false)	return;

	DestroyAmmo();

	switch (dir)
	{
	case MoveDir::Left:
		tileInfo->isDes[0][1] = false;
		tileInfo->isDes[1][1] = false;
		break;
	case MoveDir::Right:
		tileInfo->isDes[0][0] = false;
		tileInfo->isDes[1][0] = false;
		break;
	case MoveDir::Up:
		tileInfo->isDes[1][0] = false;
		tileInfo->isDes[1][1] = false;
		break;
	case MoveDir::Down:
		tileInfo->isDes[0][0] = false;
		tileInfo->isDes[0][1] = false;
		break;
	}

	hitTile1 = nullptr;
	hitTile2 = nullptr;
}

bool Ammo::CollisionEnter(RECT rc1, RECT rc2)
{
	if (rc1.left > rc2.right)	return false;
	if (rc1.right < rc2.left)	return false;
	if (rc1.top > rc2.bottom)	return false;
	if (rc1.bottom < rc2.top)	return false;

	return true;
}
