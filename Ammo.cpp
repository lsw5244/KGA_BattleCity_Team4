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

	pos = { TILEMAPTOOL_SIZE_X / 2, TILEMAPTOOL_SIZE_Y / 2 };

	moveSpeed = 0.8f;

	return E_NOTIMPL;
}

void Ammo::Update()
{
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT))
	{
		Fire(MoveDir::Right, { TILEMAPTOOL_SIZE_X / 2, TILEMAPTOOL_SIZE_Y / 2 });
	}
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT))
	{
		Fire(MoveDir::Left, { TILEMAPTOOL_SIZE_X / 2, TILEMAPTOOL_SIZE_Y / 2 });
	}

	if (isAlive == false)
	{
		return;
	}

	switch (dir)
	{
	case Left:
		pos.x -= moveSpeed;
		break;
	case Right:
		pos.x += moveSpeed;
		break;
	case Up:
		break;
	case Down:
		break;
	}

	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_SPACE))
	{
		DestroyAmmo();
	}


	//pos.x += moveSpeed;
}

void Ammo::Render(HDC hdc)
{
	if (isAlive == false)
	{
		return;
	}

	img->Render(hdc, pos.x, pos.y);

	
}

void Ammo::Release()
{
}

void Ammo::Fire(MoveDir dir, POINTFLOAT pos)
{
	isAlive = true;

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
		break;
	case Down:
		break;
	}

	this->pos = pos;

}

void Ammo::DestroyAmmo()
{
	
	
}

