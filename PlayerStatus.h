#pragma once
#include "PlayerTank.h"

class Iamge;
class PlayerTank;
class PlayerStatus
{
private:
	Image* player1LifeImage;
	//	Image* player2LifeImage;
	Image* lifeNumImage;

	PlayerTank* playerTank;

public:
	void SetData(PlayerTank* playerTank);
	HRESULT Init();
	void Update();
	void Render(HDC hdc);
	void Release();

	void ChangeLifeImage(int life);
};

