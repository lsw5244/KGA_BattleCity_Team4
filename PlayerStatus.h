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

	inline void SetPlayerTank(PlayerTank& playerTank) { this->playerTank = &playerTank; }
public:
	HRESULT Init(PlayerTank& playerTank);
	void Update(PlayerTank& playerTank);
	void Render(HDC hdc);
	void Release();

	void ChangeLifeImage(int life);
};

