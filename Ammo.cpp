#include "Ammo.h"
#include "Image.h"

HRESULT Ammo::Init()
{
	ImageManager::GetSingleton()->AddImage("Image/Bullet/Missile_Down.bmp", 3, 4, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("Image/Bullet/Missile_Left.bmp", 4, 3, true, RGB(255, 0, 255));
	img = ImageManager::GetSingleton()->AddImage("Image/Bullet/Missile_Right.bmp", 4, 3, true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("Image/Bullet/Missile_Up.bmp", 3, 4, true, RGB(255, 0, 255));

	boomEffect = ImageManager::GetSingleton()->AddImage("Image/Effect/Boom_Effect", 48, 16, 3, 1, true, RGB(255, 0, 255));

	isAlive = false;

	pos = { TILEMAPTOOL_SIZE_X / 2, TILEMAPTOOL_SIZE_Y / 2 };

	moveSpeed = 1.0f;

	return E_NOTIMPL;
}

void Ammo::Update()
{
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_SPACE))
	{
		isAlive = true;
	}

	if (isAlive == false)
	{
		return;
	}
	pos.x += moveSpeed;
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

void Ammo::Fire(MoveDir dir)
{
}

void Ammo::DestroyAmmo()
{
	//isAlive = false;
	
}

