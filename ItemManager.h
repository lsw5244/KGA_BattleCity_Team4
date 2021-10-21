#pragma once
#include "Config.h"
#include "GameEntity.h"
#include "PlayerTank.h"
class Item;
class ItemManager : public  GameEntity
{
private:
	vector<Item*> vecItems;
	vector<Item*>::iterator it;
	int eraseCount;
protected:

public:
	void newItem(PlayerTank& playerTank);
	HRESULT Init();
	void Update();
	void Render(HDC hdc);
	void Release();
};

