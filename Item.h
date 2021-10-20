#pragma once
#include "Config.h"
#include "GameObject.h"
#include "PlayerTank.h"
class Item : public GameObject
{
private:
	enum class ItemState { Barrier, TimeStop, Shovel, Star, Boom, Life };
	RECT* playerRect;
	ItemState itemState;
	float aliveTime;
	int itemNum;
	inline void SetPlyaerRect(PlayerTank& playerTank) { this->playerRect = playerTank.GetRect(); }

protected:
public:
	HRESULT Init();
	void Update();
	void Render(HDC hdc);
	void Release();
};

