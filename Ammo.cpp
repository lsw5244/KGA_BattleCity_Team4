/*
		����ϱ�
		�߻��� �� Fire()�Լ��� �۵���Ű�� �߻�
		�Ѿ��� �浹�ϸ� DestroyAmmo()�Լ� �۵���Ű��
		
		FIXME
		1. �浹 �������� ���� �־��ֱ�
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

