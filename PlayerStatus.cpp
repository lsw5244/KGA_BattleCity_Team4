#include "PlayerStatus.h"
#include "Image.h"

HRESULT PlayerStatus::Init()
{
	ImageManager::GetSingleton()->AddImage("Image/Icon/player1Life.bmp", 16, 16, true, RGB(255, 0, 255));
	player1LifeImage = ImageManager::GetSingleton()->FindImage("Image/Icon/player1Life.bmp");
	//ImageManager::GetSingleton()->AddImage("Image/Icon/player2Life.bmp", 16, 16, true, RGB(255, 0, 255));
	//player2LifeImage = ImageManager::GetSingleton()->FindImage("ImageIcon/player2Life.bmp");

	ImageManager::GetSingleton()->AddImage("Image/Text/Number.bmp", 40, 14, 5, 2, true, RGB(255, 0, 255));
	lifeNumImage = ImageManager::GetSingleton()->FindImage("Image/Text/Number.bmp");

	return S_OK;
}

void PlayerStatus::Update()
{
}

void PlayerStatus::Render(HDC hdc)
{
	player1LifeImage->Render(hdc, 240, 136);
	lifeNumImage->Render(hdc, 244, 140, lifeNumImage->GetCurrFrameX(), lifeNumImage->GetCurrFrameY());
}

void PlayerStatus::Release()
{
}

void PlayerStatus::ChangeLife(int life)
{
	lifeNumImage->SetCurrFrameX(life % 5);
	lifeNumImage->SetCurrFrameY(life / 5);
}
