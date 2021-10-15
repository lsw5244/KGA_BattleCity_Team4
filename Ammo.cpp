/*
		사용하기
		발사할 때 Fire()함수를 작동시키면 발사
		총알이 충돌하면 DestroyAmmo()함수 작동시키기
		
		FIXME
		1. 충돌 했을때의 조건 넣어주기
*/

#include "Ammo.h"
#include "Image.h"

HRESULT Ammo::Init()
{
	ImageManager::GetSingleton()->AddImage("Image/Bullet/Missile_Down.bmp", 3, 4, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("Image/Bullet/Missile_Left.bmp", 4, 3, true, RGB(255, 0, 255));
	img = ImageManager::GetSingleton()->AddImage("Image/Bullet/Missile_Right.bmp", 4, 3, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("Image/Bullet/Missile_Up.bmp", 3, 4, true, RGB(255, 0, 255));

	boomEffect = ImageManager::GetSingleton()->AddImage("Image/Effect/Boom_Effect.bmp", 48, 16, 3, 1, true, RGB(255, 0, 255));

	isAlive = false;
	//dir = MoveDir::Right;
	renderBoomEffect = false;
	showCollider = false;

	sec = 0.0f;

	pos = { TILEMAPTOOL_SIZE_X / 2, TILEMAPTOOL_SIZE_Y / 2 };

	moveSpeed = 100.0f;

	bodySize = 4;

	//shape.left = pos.x - img->GetFrameWidth() / 2;
	//shape.right = shape.left + img->GetFrameWidth();
	//shape.top = pos.y - img->GetFrameHeight() / 2;
	//shape.bottom = shape.top + img->GetFrameHeight();

	shape.left = pos.x - bodySize / 2;
	shape.right = shape.left + bodySize;
	shape.top = pos.y - bodySize / 2;
	shape.bottom = shape.top + bodySize;


	return S_OK;
}

void Ammo::Update()
{
	AmmoHitCheck();
	




	shape.left = pos.x - bodySize / 2;
	shape.right = shape.left + bodySize;
	shape.top = pos.y - bodySize / 2;
	shape.bottom = shape.top + bodySize;

	//cout << "Left: " << shape.left << "\tRight : " << shape.right << "\tTop : " << shape.top << "\tBottom : " << shape.bottom << endl;

	if (KeyManager::GetSingleton()->IsOnceKeyDown('P'))
	{
		showCollider = showCollider ? false : true;
	}

	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT))
	{
		Fire(MoveDir::Right, pos);
	}
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT))
	{
		Fire(MoveDir::Left, pos);
	}
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_UP))
	{
		Fire(MoveDir::Up, pos);
	}
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_DOWN))
	{
		Fire(MoveDir::Down, pos);
	}


	if (isAlive == false)
	{
		return;
	}

	switch (dir)
	{
	case Left:
		pos.x -= moveSpeed * TimerManager::GetSingleton()->GetDeltaTime();;
		break;
	case Right:
		pos.x += moveSpeed * TimerManager::GetSingleton()->GetDeltaTime();;
		break;
	case Up:
		pos.y -= moveSpeed * TimerManager::GetSingleton()->GetDeltaTime();
		break;
	case Down:
		pos.y += moveSpeed * TimerManager::GetSingleton()->GetDeltaTime();;
		break;
	}

	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_SPACE))
	{
		DestroyAmmo();
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
			if (boomEffect->GetCurrFrameX() > 3)
			{
				renderBoomEffect = false;
				pos = { WIN_SIZE_X / 2, WIN_SIZE_Y / 2 };
				boomEffect->SetCurrFrameX(0);
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
	case Left:
		img = ImageManager::GetSingleton()->FindImage("Image/Bullet/Missile_Left.bmp");
		this->dir = dir;
		break;
	case Right:
		img = ImageManager::GetSingleton()->FindImage("Image/Bullet/Missile_Right.bmp");
		this->dir = dir;
		break;
	case Up:
		img = ImageManager::GetSingleton()->FindImage("Image/Bullet/Missile_Up.bmp");
		this->dir = dir;
		break;
	case Down:
		img = ImageManager::GetSingleton()->FindImage("Image/Bullet/Missile_Down.bmp");
		this->dir = dir;
		break;
	}

	//this->pos = pos;

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
			if (PtInRect(&tileInfo[i][j].selectRc, { (int)pos.x, (int)pos.y }))
			{
				if (tileInfo[i][j].terrain == Terrain::Brick)
				{
					DestroyWall(i, j);
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

}

