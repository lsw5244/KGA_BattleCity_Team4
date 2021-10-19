#pragma once
#include "PlayerTank.h"

class Iamge;
class PlayerStatus : public PlayerTank
{
private:
	Image* player1LifeImage;
//	Image* player2LifeImage;
	Image* lifeNumImage;

	int player1Life, player2Life;

public:
	virtual HRESULT Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;

	void ChangeLife(int life);
};

